/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-08-16 11:23:24
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-08-16 12:08:46
 */
#ifndef SINGLETON_H
#define SINGLETON_H
#include<mutex>
#include<iostream>

class Singleton_hungry{
public:
    static Singleton_hungry* get_instance(){
        static Singleton_hungry singleton_hungry;
        return &singleton_hungry;
    }
private:
    Singleton_hungry(){}
    ~Singleton_hungry(){}
};

class Singleton_lazy{
private:
    Singleton_lazy(){}
    ~Singleton_lazy(){}
    static std::mutex mutex_;
    static Singleton_lazy* instance;

public:
    static Singleton_lazy* get_instance(){
        if(!instance){
            std::unique_lock<std::mutex> lk(mutex_);
            {
                if(!instance){
                    instance=new  Singleton_lazy();
                }
            }
        }
        return instance;
    }
};

class Singleton_lazy1{
private:
    Singleton_lazy1(){}
    ~Singleton_lazy1(){}
    static Singleton_lazy1* instance;
    static std::once_flag flag;

    void once_init(){
        instance=new(std::nothrow) Singleton_lazy1();//分配失败，是返回NULL;
        if(!instance){
            throw std::exception();
        }
    }

public:
    static Singleton_lazy1* get_instance(){
        if(!instance){
            try{
                std::call_once(flag,once_init); //void call_once (once_flag& flag, Fn&& fn, Args&&... args);
            }catch(...){
                std::cout << "CreateInstance error\n";
            }
        }
        return instance;
    }
};

#endif