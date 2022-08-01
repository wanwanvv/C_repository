/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-06 16:10:35
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-17 10:55:32
 */
#ifndef MY_CLASS_H
#define MY_CLASS_H
#include <string>
#include <iostream>

class MyClass
{
private:
    std::string _str;
public:
    std::string getStr(){
        return _str;
    }
    MyClass(){
        std::cout<<"MyClass: Default constructor!"<<std::endl;
    }

    MyClass(const MyClass& myClass){
        std::cout<<"MyClass: Copy constructor!"<<std::endl;
        _str=myClass._str;
    }

    MyClass(int n, char c):_str(n,c){
        std::cout<<"MyClass: (n, c) constructor!"<<std::endl;
    }

    MyClass(const std::string& s):_str(s){
        std::cout<<"MyClass: (const string& s) constructor!"<<std::endl;
    }

    void operator=(const MyClass& myClass){
        std::cout<<"MyClass: operator =!"<<std::endl;
        _str=myClass._str;
        std::cout<<"parameter valu="<<myClass._str<<std::endl;
    }
};

#endif