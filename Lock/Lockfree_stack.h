/*
 * @Descripttion: CAS算法(Compare and swap/乐观锁) 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-17 16:00:41
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-09-03 20:54:02
 */

#ifndef LOCK_FREE_H
#define LOCK_FREE_H

#include <iostream>
#include <atomic>

//输入一个pAddr的地址，在函数内部判断其的值是否与期望值nExpected相等
//如果相等那么就将pAddr的值改为nNew并同时返回true；否则就返回false，什么都不做
bool my_compare_and_swap(int* pAddr, int nExpected, int nNew){
    if(*pAddr==nExpected){
        *pAddr=nNew;
        return true;
    }else{
        return false;
    }
}

template<typename T>
struct Node
{
    T data;
    Node* next;
    Node(int d):data(d),next(nullptr){}
};

//memory_order,从弱到强
/**
 * memory_order_relaxed： 不对执行的顺序作任何保证
 * memory_order_consume：后面依赖此原子变量的访存指令勿重排至此条指令之前
 * memory_order_acquire：后面访存指令勿重排至此条指令之前
 * memory_order_release：前面的访存指令勿排到此条指令之后。当此条指令的结果被同步到其他核的cache中时，保证前面的指令也已经被同步
 * memory_order_acq_rel：acquare + release
 * memory_order_seq_cst：acq_rel + 所有使用seq_cst的指令有严格的全序关系
 */

template<typename T>
class Lockfree_stack{
public:
    void push(const T& data){
        Node<T>* new_node=new Node<T>(data);
        new_node->next=head.load(std::memory_order_relaxed);
        while(!std::atomic_compare_exchange_weak_explicit(
            &head,
            &new_head->next,
            new_node,
            std::memory_order_release,
            std::memory_order_relaxed
        ));
    }

    void pop(){
        Node<T>* old_head=head.load();
        while(!old_head&&!std::atomic_compare_exchange_weak(&head,&old_head,old_head->next));
        if(old_head!=nullptr) delete old_head;
    }

    bool isEmpty(){
        return head.load()==nullptr;
    }

    T top(){
        return head.load()->data
    }
private:
    std::atomic<Node<T>*> head;
};


#endif