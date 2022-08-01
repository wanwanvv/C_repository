/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-11 08:21:12
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-25 11:10:16
 */
#ifndef THREAD_POOL
#define THREAD_POOL

#include <mutex>
#include <functional>
#include <vector>
#include <future>
#include <thread>
#include <memory>
#include <queue>
#include <condition_variable>

class ThreadPool{
public:
    explicit ThreadPool(size_t threadNumber):isStop_(false){
        for(size_t i=0;i<threadNumber;++i){
            threads_.emplace_back(
                [this](){
                    for(;;){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lk(mutex_);
                            cv_.wait(lk,[this](){return isStop_||!tasks_.empty();});
                            if(isStop_&&tasks_.empty()) break;
                            task=std::move(tasks_.front());
                            tasks_.pop();
                        }
                        task();
                    }
                }
            );
        }
    }

    ThreadPool(const ThreadPool&)=delete;
    ThreadPool(ThreadPool&&)=delete;

    ThreadPool& operator=(const ThreadPool&)=delete;
    ThreadPool& operator=(ThreadPool&&)=delete;

    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isStop_=true;
        }
        cv_.notify_all();
        for(auto& th:threads_){
            th.join();
        }
    }

    template<typename F, typename... Args>
    void submit(F&& f, Args&&... args){
        auto taskPtr=std::make_shared<std::function<decltype(f(args...))()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
        {
            std::unique_lock<std::mutex> lk(mutex_);
            if(isStop_) throw std::runtime_error("Submit on stopped threadpool!");
            tasks_.emplace([taskPtr](){(*taskPtr)();});
        }
        cv_.notify_all();
        return;
    }

    template<typename F, typename... Args>
    auto submit_return(F&& f, Args&&... args)->std::future<decltype(f(args...))>{

    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    bool isStop_;
    std::vector<std::thread>  threads_;
    std::queue<std::function<void()>> tasks_;
};

class My_thread_pool{
public:
    My_thread_pool()=default;
    explicit My_thread_pool(size_t thread_num):threads_(thread_num),isStop_(false){
        for(size_t i=0;i<thread_num;++i){
            threads_.emplace_back(
                [this](){
                    for(;;){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lk(mutex_);
                            cv_.wait(lk,[this](){return isStop_||!tasks_.empty();});
                            if(isStop_&&tasks_.empty()) break;
                            task=std::move(tasks_.front());
                            tasks_.pop();
                        }
                        task();
                    }
                }
            );
        }
    }

    ~My_thread_pool(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isStop_=true;
        }
        cv_.notify_all();
        for(auto& thread:threads_){
            thread.join();
        }
    }

    //禁止拷贝和赋值
    My_thread_pool(const My_thread_pool&)=delete;
    My_thread_pool(My_thread_pool&&)=delete;
    My_thread_pool& operator=(const My_thread_pool&)=delete;
    My_thread_pool& operator=(My_thread_pool&&)=delete;

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args)->std::future<decltype(f(args...))>{
        auto taskPtr=std::make_shared<std::packaged_task<decltype(f(args...))()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
        {
            std::unique_lock<std::mutex> lk(mutex_);
            if(isStop_) throw std::runtime_error("Submit thread on stopped threadPool!");
            tasks_.emplace([taskPtr](){(*taskPtr)();});
        }
        cv_.notify_one();
        return taskPtr->get_future();//返回future对象，调用.get()来得到真正的值
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> threads_;
    bool isStop_=true;
};

#endif
