/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-29 11:27:37
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-29 11:59:16
 */
#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>

template<typename T>
class Unique_ptr{
public:
    Unique_ptr(T* ptr):ptr_(ptr){}
    ~Unique_ptr(){
        del_();
    }

    //定义移动构造而不显示声明拷贝构造, 表示资源只能被移动不能被拷贝
    Unique_ptr(Unique_ptr&& unique_ptr):ptr_(unique_ptr.ptr_){
        unique_ptr.ptr_=nullptr;
    }

    //赋值运算符传值, 因为拷贝构造已经被禁用了,所以赋值运算符只能传右值
    Unique_ptr& operator=(Unique_ptr unique_ptr){
        Unique_ptr(unique_ptr).swap_(unique_ptr);
        return *this;
    }

    // 先释放资源(如果持有), 再持有资源
    void reset(T* ptr){
        del_();
        ptr_=ptr;
    }

    // 获取资源，调用方应该只使用不释放，否则会两次delete资源
    T* get()const noexcept{
        return ptr_;
    }

    T* operator->()const noexcept{
        return ptr_;
    }

    T& operator *(const noexcept)const noexcept{
        return *ptr_;
    }

    //提供一个本类型到bool的隐式转换，不允许使用参数
    operator bool()const noexcept{
        return m_ptr;
    }

private:
    T* ptr_;

    void del_(){
        if(ptr_){
            delete ptr_;
            ptr_=nullptr;
        }
    }

    void swap_(Unique_ptr& unique_ptr){
        using std::swap;
        swap(ptr_,unique_ptr.ptr);
    }
};

#endif