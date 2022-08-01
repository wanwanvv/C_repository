/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-06 17:12:12
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-17 10:57:40
 */
#ifndef TEST_CLASS_H
#define TEST_CLASS_H
#include "myClass.h"

class TestClass{
private:
    MyClass _myClass;
    
public:
    void test();
    TestClass(){
        std::cout<<"TestClass: Default constructor!"<<std::endl;
    }

    TestClass(int n, char c):_myClass(n,c){
        std::cout<<"TestClass: (n, c) constructor!"<<std::endl;
    }

    TestClass(std::string s):_myClass(s){
        std::cout<<"TestClass: (const string& s) constructor!"<<std::endl;
    }

    //拷贝构造函数
    static TestClass* getInstance();
};

#endif