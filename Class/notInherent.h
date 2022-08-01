/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-19 11:39:49
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-19 11:58:35
 */
# ifndef NOT_INHERENT_H
#define NOT_INHERENT_H

#include <iostream>

template<typename T>
class Base{
private:
    friend T;//私有的友元函数
    //私有的构造函数
    Base(){
        std::cout<<"This is  Base()">>std::endl;
    }

    ~Base(){
        std::cout<<"This is  ~Base()"<<std::endl;
    }

};

//class A无法被继承，
class A:virtual public Base<A>{//虚继承
public:
    A(){
        std::cout<<"This is  A()"<<std::endl;
    }
};

#endif