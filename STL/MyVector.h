/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-08 09:10:30
 * @LastEditors: sueRimn
 * @LastEditTime: 2022-08-08 11:48:24
 */
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <string.h>
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

template<typename T>
class MyVector{
public:
    MyVector(){}
    MyVector(size_t n){
        if(n>0){
            finish=start=allocate(n);
            end_of_range=finish+n;
        }
    }

    ~MyVector(){
        clear();
    }

    MyVector(const MyVector<T>& myVector){
        size_t cap=myVector.capacity();
        start=allocate(cap);
        std::memcpy(start,myVector.start,sizeof(T)*cap);
    }

    MyVector& operator=(const MyVector<T>& myVector){
        if(&myVector==this) return *this;
        size_t cap=myVector.capacity();
        size_t siz=myVector.size();
        if(cap==0){
            if(start) deallocate(start);
            start=nullptr;
            finish=nullptr;
            end_of_range=nullptr;
            return *this;
        }
        if(capacity()<cap){
            if(start) deallocate(start);
            start=allocate(cap);
        }
        std::memcpy(begin(),myVector.begin(),sizeof(T)*siz);
        finish=begin()+siz;
        end_of_range=begin()+cap;
        return *this;
    }

    void clear(){
        if(start){
            deallocate(start);
            start=nullptr;
            finish=nullptr;
            end_of_range=nullptr;
        }
    }

    void push_back(const T& t){
        //还有备用空间
        if(finish!=end_of_range){
            *finish=t;
            ++finish;
        }else {
            size_t old_size=size();
            size_t len=old_size==0?1:2*old_size;
            T* new_start=allocate(len);
            //复制原来的元素到新空间
            std::memcpy(new_start,start,sizeof(T)*(old_size));
            T* new_finish=new_start+old_size;
            *(new_finish++)=t;
            //析构并释放原空间
            deallocate(start);
            //更新迭代器
            start=new_start;
            finish=new_finish;
            end_of_range=start+len;
        }
    }

    void pop_back(){
        assert(size()>0);
        --finish;
    }

    T& operator[](size_t i){
        assert(i>=0&&i<size());
        return *(begin()+i);
    }

    size_t capacity() const{
        return size_t(end_of_range-begin());
    }

    size_t size() const{
        return size_t(end()-begin());
    }

    bool empty() const{
        return begin()==end();
    }

    int& back() const{
        return *(end()-1);
    }

    int& front() const{
        return *begin();
    }

    T* begin() const{
        return start;
    }

    T* end() const{
        return finish;
    }

    T* allocate(size_t n){
        T* buf=(T*)malloc(sizeof(T)*n);
        return buf;
    }

    void deallocate(T* p){
        if(p){
            free(p);
            p=nullptr;
        }
    }

private:
    T* start{nullptr};
    T* finish{nullptr};
    T* end_of_range{nullptr};
};

#endif