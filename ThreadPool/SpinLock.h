/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-11 17:15:16
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-11 17:32:04
 */
#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H
#include <atomic>

class spinlock_mutex{
private:
    std::atomic_flag flag;
public:
    spinlock_mutex()=default;
    spinlock_mutex(const spinlock_mutex&)=delete;
    spinlock_mutex(const spinlock_mutex&&)=delete;

    void lock(){
        while(flag.test_and_set(std::memory_order_acquire));//检查atomic_flag标志
    }

    void unlock(){
        flag.clear(std::memory_order_release);
    }
};

#endif