/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-25 09:39:10
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-25 11:04:12
 */
/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-25 09:39:10
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-25 09:39:16
 */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char* key;
    char* value;
    Node* next;
};

class HashTable{
public:

    HashTable();
    ~HashTable();
    
    //接口函数
    const char* get(const char* key);//得到key对应的value
    bool insert(const char* key, const char* value);//插入键值对，成功返回true，失败返回false
    void display();//打印出值

    //禁止拷贝
    HashTable(const HashTable&)=delete;
    HashTable(HashTable&&)=delete;
    HashTable& operator =(const HashTable&)=delete;
    HashTable& operator =(HashTable&&)=delete;

private:
    const static int hashSize_=10;
    Node* hashNodes_[hashSize_];

    char* init_(const char* str);//给每个节点分配空间
    size_t hashFunction_(const char* key);//根据key值得到hash值
    Node* lookUp_(const char* key);//找到key对应的Node
};


#endif