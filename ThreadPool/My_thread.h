/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-20 14:28:30
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-20 16:10:30
 */
#ifndef MY_THREAD_H
#define MY_THREAD_H
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <functional>
#include <memory>

class My_thread{
public:
    My_thread():isStop_(false),isPause_(false),thread_(nullptr),num_(0){

    }

    ~My_thread(){
        stop();
    }

    //禁止拷贝和赋值
    My_thread& operator=(const My_thread&)=delete;
    My_thread& operator=(My_thread&&)=delete;
    My_thread(const My_thread&)=delete;
    My_thread(My_thread&&)=delete;

    //接口函数
    void run(){
        thread_=std::make_shared<std::thread>(
            [&](){
                for(;;){
                    {
                        std::unique_lock<std::mutex> lk(mutex_);
                        cv_.wait(lk,[this](){return isStop_||!isPause_;});
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        std::cout<<"current process ="<<num_++<<std::endl;
                        if(isStop_) return;
                    }
                }
            }
        );
    }

    void pause(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isPause_=true;
        }
        cv_.notify_one();
    }

    void resume(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isPause_=false;
        }
        cv_.notify_one();
    }

    void stop(){
        {
            std::unique_lock<std::mutex> lk(mutex_);
            isStop_=true;
            isPause_=false;
        }
        cv_.notify_one();
        if(thread_->joinable()) thread_->join();
    }
    
private:
    //线程状态
    volatile std::atomic_bool isStop_;
    volatile std::atomic_bool isPause_;
    std::atomic<int> num_;

    //线程
    std::shared_ptr<std::thread> thread_;

    //同步与互斥
    std::mutex mutex_;
    std::condition_variable cv_;
};

#endif