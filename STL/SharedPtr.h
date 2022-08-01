#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>

namespace stl{
    template<typename T>
    class Shared_ptr{
        public:
            //直接构造函数
            constexpr Shared_ptr() noexcept=default;
            constexpr Shared_ptr(nullptr_t) noexcept:Shared_ptr(){}//委托构造函数
            explicit Shared_ptr(T* p):ptr_(p){
                if(ptr_) ++count_;
            }
            //析构函数
            ~Shared_ptr(){
                if(ptr_&&count_==0){
                    delete ptr_;
                }
            }
            //拷贝构造函数
            Shared_ptr(const Shared_ptr& shared_ptr):ptr_(shared_ptr.ptr_),count_(shared_ptr.count_){
                if(ptr_) ++count_; 
            }
            //移动构造函数
            Shared_ptr(Shared_ptr&& shared_ptr):ptr_(shared_ptr.ptr_),count_(shared_ptr.count_){
               //进入允许析构状态
               shared_ptr.ptr_=nullptr;
               shared_ptr.count_=0;
            }

            //拷贝赋值运算符
            Shared_ptr& operator=(const Shared_ptr& shared_ptr){
                if(ptr_!=shared_ptr.ptr_){
                    if(ptr_&&count_==0){
                        delete ptr_;
                    }
                    ptr_=shared_ptr.ptr_;
                    count_=shared_ptr.count_;
                    ++count_;
                }
                return *this;
            }

            //移动赋值运算符
            Shared_ptr& operator=(Shared_ptr&& shared_ptr){
                if(ptr_!=shared_ptr.ptr_){
                    if(ptr_&&count_==0){
                        delete ptr_;
                    }
                    ptr_=shared_ptr.ptr_;
                    count_=shared_ptr.count_;
                    shared_ptr.ptr_=nullptr;
                    shared_ptr.count_=0;
                }
                return *this;
            }

            //重载运算符*
            T& operator *() const noexcept{
                return *ptr_;
            }

            //重载运算符->
            T* operator->() const noexcept{
                return ptr_;
            }

            //重载运算符bool
            operator bool() const noexcept{
                return static_cast<bool>(ptr_);
            }

            //接口
            int use_count(){
                return ptr_==nullptr?0:count_;
            }

            bool unique(){
                return count_==1;
            }

            void reset() noexcept{
                if(ptr_&&count_==0){
                    delete ptr_;
                }
                ptr_=nullptr;
                count_=0;
            }
            
            void reset(nullptr_t){
                reset();
            }

            void reset(const Shared_ptr& shared_ptr){
                if(ptr_&&count_==0){
                    delete ptr_;
                }
                ptr_=shared_ptr.ptr_;
                count_=shared_ptr.count_;
            }

            T* get() const noexcept{
                return ptr_;
            }

        private:
            //变量
            T* ptr_=nullptr;
            int count_=0;
    };
};



#endif
