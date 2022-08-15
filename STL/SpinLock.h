/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-07 10:20:25
 * @LastEditors: sueRimn
 * @LastEditTime: 2022-08-07 10:24:45
 */
#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include <atomic>

class SpinLock{
public:
    SpinLock(std::atomic_flag& flag):flag_(flag){
        while(flag_.test_and_set(std::memory_order_acquire)){}
    }
    ~SpinLock(){
        flag_.clear(std::memory_order_release);
    }
private:
    std::atomic_flag& flag_;
};

#endif