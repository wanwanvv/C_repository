/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-10 08:59:50
 * @LastEditors: sueRimn
 * @LastEditTime: 2022-08-12 08:56:34
 */
#ifndef ALTERNATIVE_PRINT_H
#define ALTERNATIVE_PRINT_H

#include <mutex>
#include <atomic>
#include <condition_variable>

#include <iostream>
#include <semaphore.h>
#include <thread>
#include <vector>

class AlternativePrint_cv{
public:
    AlternativePrint_cv(int num):n(num),flag(true){
    }

    void foo(){
        std::unique_lock<std::mutex> lk(mutex_);
        {
            for(int i=0;i<n;++i){
                cv_.wait(lk,[this](){return flag;});
                std::cout<<"foo";
                flag=false;
                cv_.notify_one();
            }
        }
    }

    void bar(){
        std::unique_lock<std::mutex> lk(mutex_);
        {
            for(int i=0;i<n;++i){
                cv_.wait(lk,[this](){return !flag;});
                std::cout<<"bar ";
                flag=true;
                cv_.notify_one();
            }
        }
    }
private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int n;
    bool flag;
};

class AlternativePrint_sem{
public:
    AlternativePrint_sem(int num):n(num){
        sem_init(&sem_foo,0,1);
        sem_init(&sem_bar,0,0);
    }

    ~AlternativePrint_sem(){
        sem_destroy(&sem_foo);
        sem_destroy(&sem_bar);
    }

    void foo(){
        for(int i=0;i<n;++i){
            sem_wait(&sem_foo);
            std::cout<<"foo";
            sem_post(&sem_bar);
        }
        
    }

    void bar(){
        for(int i=0;i<n;++i){
            sem_wait(&sem_bar);
            std::cout<<"bar ";
            sem_post(&sem_foo);
        }
        
    }
private:
    int n;
    sem_t sem_foo;
    sem_t sem_bar;
};

class AlternativePrint_atomic{
public:

    AlternativePrint_atomic(int num):n(num),flag(ATOMIC_FLAG_INIT){

    }

    void foo(){
        for(int i=0;i<n;++i){
            while(flag.test_and_set(std::memory_order_acquire)){
                std::this_thread::yield();
            }
            std::cout<<"foo";
            flag.clear(std::memory_order_release);
        }
    }

    void bar(){
        for(int i=0;i<n;++i){
            while(flag.test_and_set(std::memory_order_acquire)){

            }
            std::cout<<"bar ";
            flag.clear(std::memory_order_release);
        }
    }

private:
    int n;
    std::atomic_flag flag;
};

#endif