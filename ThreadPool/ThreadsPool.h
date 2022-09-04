/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-08-23 09:12:38
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-08-23 09:36:49
 */
#ifndef THREADS_POOL
#define THREADS_POOL

#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <vector>
#include <condition_variable>
#include <future>
#include <memory>

class ThreadsPool{
public:
    ThreadsPool(int threads_num):isStop_(false){
        for(int i=0;i<threads_num;++i){
            threads_.emplace_back(
                [this](){
                    for(;;){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lk(mutex_);
                            cv_.wait(lk,[this](){return isStop_||!tasks_.empty();});
                            if(isStop_&&tasks_.empty()) return;
                            task=std::move(tasks_.front());
                            tasks_.pop();
                        }
                        task();
                    }
                }
            );
        }
    }

    ~ThreadsPool(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isStop_=true;
        }
        cv_.notify_all();
        for(auto& thread:threads_){
            thread.join();
        }
        
    }

    ThreadsPool(const ThreadsPool& threadsPool)=delete;
    ThreadsPool(ThreadsPool&& threadsPool)=delete;
    ThreadsPool& operator=(const ThreadsPool& threadsPool)=delete;
    ThreadsPool& operator=(ThreadsPool&& threadsPool)=delete;

    template<typename F,typename...Args>
    auto submit(F&& f,Args&&...args)->std::future<decltype(f(args...))>{
        auto taskPtr=std::make_shared<std::packaged_task<decltype(f(args...))()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
        {
            std::unique_lock<std::mutex> lk(mutex_);
            tasks_.emplace([taskPtr](){(*taskPtr)();});
        }
        cv_.notify_one();
        return taskPtr->get_future();
    }

private:
    std::vector<std::thread> threads_;
    bool isStop_{true};
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
};

#endif