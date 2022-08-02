#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>
#include <memory>

//使用引用计数，
class ref_count{
public:
    int use_count() const noexcept {return count_;}
    void inc_ref() noexcept {++count_;}
    int dec_ref() noexcept {return --count_;}

private:
    int count_{1};
};

namespace stl{
    template<typename T>
    class Shared_ptr{
        public:
            //直接构造函数
            constexpr Shared_ptr() noexcept=default;
            constexpr Shared_ptr(nullptr_t) noexcept:Shared_ptr(){}//委托构造函数
            explicit Shared_ptr(T* p):ptr_(p){
                if(ptr_){
                    rep_=new ref_count();//每次创建类的对象时，初始化指针并将引用计数置为1
                }
            }

            //析构函数
            //减少引用计数（如果为0，则删除对象）
            ~Shared_ptr(){
                if(ptr_&&rep_->dec_ref()==0){
                    delete ptr_;
                    delete rep_;
                }
            }

            //拷贝构造函数
            //当对象作为另一对象的副本而创建时，引用计数加1
            Shared_ptr(const Shared_ptr& shared_ptr):ptr_(shared_ptr.ptr_),rep_(shared_ptr.rep_){
                if(ptr_){
                    rep_->inc_ref();
                }
            }

            //移动构造函数
            Shared_ptr(Shared_ptr&& shared_ptr):ptr_(shared_ptr.ptr_),rep_(shared_ptr.rep_){
               //进入允许析构状态
               shared_ptr.ptr_=nullptr;
               shared_ptr.rep_=nullptr;
            }

            //拷贝赋值运算符
            //赋值操作减少左操作数所指对象的引用计数（如果引用计数减至0，则删除对象），并增加右操作数所指对象的引用计数
            Shared_ptr& operator=(const Shared_ptr& shared_ptr){
                if(this!=&shared_ptr){
                    if(ptr_&&rep_->dec_ref()==0){
                        delete ptr_;
                        delete rep_;
                    }
                    ptr_=shared_ptr.ptr_;
                    rep_=shared_ptr.rep_;
                    rep_->inc_ref();
                }
                return *this;
            }

            //移动赋值运算符
            Shared_ptr& operator=(Shared_ptr&& shared_ptr){
                if(ptr_!=shared_ptr.ptr_){
                    if(ptr_&&rep_->dec_ref()==0){
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

            //重载运算符*
            T& operator *() const noexcept{
                return *ptr_;
            }

            //重载运算符->
            T* operator->() const noexcept{
                return ptr_;
            }

            //重载运算符bool
            explicit operator bool() const noexcept{
                return static_cast<bool>(ptr_);
            }

            //接口
            int use_count(){
                return ptr_==nullptr?0:rep_->use_count();
            }

            bool unique(){
                return rep_->use_count()==1;
            }

            void reset() noexcept{
                if(ptr_&&rep_->dec_ref()==0){
                        delete ptr_;
                        delete rep_;
                }
                ptr_=nullptr;
                rep_=nullptr;
            }
            
            void reset(nullptr_t){
                reset();
            }

            void reset(const Shared_ptr& shared_ptr){
                if(ptr_&&rep_->dec_ref()==0){
                        delete ptr_;
                        delete rep_;
                }
                ptr_=shared_ptr.ptr_;
                rep_=shared_ptr.rep_;
                rep_->inc_ref();
            }

            T* get() const noexcept{
                return ptr_;
            }

        private:
            //变量
            T* ptr_=nullptr;
            ref_count *rep_{nullptr};
            //std::atomic<ref_count*> rep_{nullptr};
    };
};

template<typename T, typename... Args>
auto make_Shared(Args&&... args){
    return Shared_ptr<T>{new T(std::forward(args)...)};
}

#endif
