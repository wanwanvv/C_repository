/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-08 09:36:21
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-14 11:48:33
 */
#include "testClass.h"
void TestClass::test(){
    std::cout<<"Test"<<std::endl;
}

TestClass* TestClass::getInstance(){
    static TestClass testClass;
    return &testClass;
}