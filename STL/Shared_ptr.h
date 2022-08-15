/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-03 21:03:06
 * @LastEditors: sueRimn
 * @LastEditTime: 2022-08-08 09:10:18
 */
#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <utility>

class Ref_count{
public:
    long use_count(){
        return count_;
    }

    void inc_count(){
        ++count_;
    }

    long dec_count(){
        return --count_;
    }

private:
    long count_{1};
};

template<typename T>
class Shared_ptr{
public:
    constexpr Shared_ptr() noexcept=default;
    //staticconstexpr Shared_ptr(nullptr_t) noexcept : Shared_ptr() {}

    explicit Shared_ptr(T* ptr):ptr_(ptr){
        if(ptr_!=nullptr){
            rep_=new Ref_count();
        }
    }

    ~Shared_ptr(){
        if(ptr_!=nullptr&&rep_->dec_count()==0){
            delete ptr_;
            delete rep_;
        }
    }

    /**
    template<typename U>
    Shared_ptr(const Shared_ptr<U>& other){

    }
    **/

    Shared_ptr(const Shared_ptr& shared_ptr):ptr_(shared_ptr.ptr_),rep_(shared_ptr.rep_){
        if(ptr_!=nullptr){
            rep_+=shared_ptr->inc_count();
        }
    }

    Shared_ptr(Shared_ptr&& shared_ptr):ptr_(shared_ptr.ptr_),rep_(shared_ptr.rep_){
        shared_ptr.ptr_=nullptr;
        shared_ptr.rep_=nullptr;
    }

    Shared_ptr& operator=(const Shared_ptr& shared_ptr){
        if(ptr_!=shared_ptr){
            if((ptr_!=nullptr)&&(rep_->dec_count()==0)){
                delete ptr_;
                delete rep_;
            }
            ptr_=shared_ptr.ptr_;
            rep_=shared_ptr.rep_;
            rep_->inc_count();
        }
        return *this;
    }

    Shared_ptr& operator=(Shared_ptr&& shared_ptr){
        if(ptr_!=shared_ptr){
            if((ptr_!=nullptr)&&(rep_->dec_count()==0)){
                delete ptr_;
                delete rep_;
            }
            ptr_=shared_ptr.ptr_;
            rep_=shared_ptr.rep_;
            shared_ptr.ptr_=nullptr;
            shared_ptr.rep_=nullptr;
        }
        return *this;
    }

    T* operator->() const{
        return ptr_;
    }

    T& operator*() const{
        return *ptr_;
    }

    explicit operator bool(){
        return static_cast<bool> (ptr_);
    }

    long use_count() const{
        return ptr_==nullptr?0:rep_->use_count();
    }

    bool unique() const{
        return rep_->use_count()==1;
    }

    void reset(){
        if(ptr_!=nullptr&&rep_->dec_count()==0){
            delete ptr_;
            delete rep_;
            ptr_=nullptr;
            rep_=nullptr;
        }
    }

private:
    Ref_count* rep_{nullptr};
    T* ptr_{nullptr};
};

template<typename T, typename...Args>
Shared_ptr<T> make_shared(Args&&...args){

    
    return Shared_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif