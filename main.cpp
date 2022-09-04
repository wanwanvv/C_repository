/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-06 11:09:34
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-08-26 09:26:40
 */
/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-04 09:10:04
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-15 11:32:16
 */
#include <iostream>
#include "Avl_tree/AvlTree.h"
#include "Class/testClass.h"
#include "Br_tree/BrTree.h"
#include "ThreadPool/ThreadPool.h"
#include "ThreadPool/My_thread.h"
#include "ThreadPool/ProducerConsumer.h"
#include "STL/HashTable.h"
#include "STL/MyString.h"

using namespace std;

void testMyString()
{
    MyString s1("wmm");
    MyString s2(s1);
    MyString s3;
    s3 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << (s1 > s2) << endl;
    cout << (s1 == s2) << endl;
    //cin >> s3;
    //cout << "输入后s3：" << s3 << endl;
    s2.push_back('c');
    //s2.pop_back();
    s2.erase(0, 1);
    cout << s2 << endl;
    MyString s4("hello world");
    s4.erase(0, 3);
    s4 += "cyq";
    cout << s4 << endl;
    s4.insert(2, "wmm");
    cout << s4 << endl;
    cout << s4.find("world") << endl;
    MyString::iterator it = s4.begin();
    while (it != s4.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}

void TestRotateR()
{
    AVLTree<int,int> t;
    t.insert(make_pair(5, 1));
    t.insert(make_pair(4, 1));
    t.insert(make_pair(3, 1));
    t.insert(make_pair(2, 1));
    t.insert(make_pair(1, 1));
    t.insert(make_pair(0, 1));
    t.in_traverse();
    cout << t.is_balance() << endl;
}
void TestRotateL()
{
    AVLTree<int,int> t;
    t.insert(make_pair(0, 1));
    t.insert(make_pair(1, 1));
    t.insert(make_pair(2, 1));
    t.insert(make_pair(3, 1));
    t.insert(make_pair(4, 1));
    t.insert(make_pair(5, 1));
    t.in_traverse();
    cout << t.is_balance() << endl;
}
void Testbf()
{
    AVLTree<int,int> t;
    t.insert(make_pair(5, 1));
    t.insert(make_pair(7, 1));
    t.insert(make_pair(3, 1));
    t.insert(make_pair(4, 1));
    t.insert(make_pair(2, 1));
    t.insert(make_pair(8, 1));
    t.insert(make_pair(9, 1));
    t.insert(make_pair(6, 1));
    t.insert(make_pair(1, 1));
    t.insert(make_pair(11, 1));
    t.in_traverse();
    cout << t.is_balance() << endl;
}
void TestRL()
{
    AVLTree<int,int> t;
    t.insert(make_pair(60, 1));
    t.insert(make_pair(50, 1));
    t.insert(make_pair(90, 1));
    t.insert(make_pair(100, 1));
    t.insert(make_pair(80, 1));
    t.insert(make_pair(70, 1));
    t.in_traverse();
    cout << t.is_balance() << endl;
}
void TestLR()
{
    std::cout<<"********************TestLR***************"<<std::endl;
    AVLTree<int,int> t;
    t.insert(make_pair(90, 1));
    t.insert(make_pair(100, 1));
    t.insert(make_pair(60, 1));
    t.insert(make_pair(50, 1));
    t.insert(make_pair(70, 1));
    t.insert(make_pair(80, 1));
    t.in_traverse();
    cout << t.is_balance() << endl;
}

void TestBRTree()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	BRTree<int, int> t;
	int n = 1000000;
	srand(time(0));
	for (int i = 0; i < n; ++i)
	{
		int e = rand();
		t.insert(make_pair(e, e));
	}

	//t.InOrder();
	cout << t.isBRTree() << endl;
}
void test_BRTree()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	BRTree<int, int> t;
	for (auto e : a)
	{
		t.insert(make_pair(e, e));

	}
	cout << t.isBRTree() << endl;
}

void thread_func(int i, const string& str){
    cout<<"Thread i="<<i<<" str="<<str<<endl;
    return;
}

void test_threadpool(int threadNum, int taskNum){
    ThreadPool threadPool(threadNum);
    for(int i=0;i<taskNum;++i){
        threadPool.submit(thread_func,i,string(10,i+'0'));
    }
}

void test_sigleProducerCOnsumer(){
    cout<<"test_sigleProducerCOnsumer.........................."<<endl;
    SingleProducerConsumer sPC(10,20,30);
    sPC.run();
    
}

void test_hashTable(){
    cout<<"test_hashTable.........................."<<endl;
    HashTable ht;
    const char* key[]={"a","b","c","d","e","f"};
    const char* value[]={"value1","value2","value3","value4","value5","value6"};
    for(int i=0;i<6;++i){
        ht.insert(key[i],value[i]);
    }
    ht.display();
    return;
}

int main(){
    // test_threadpool(10,20);
    // TestRotateR();
    // Testbf();
    // TestRotateL();
    // TestRL();
    // TestLR();
    // cout<<"**************default constructor**************"<<endl;
    // TestClass testClass1;
    // cout<<"**************(n,c) constructor**************"<<endl;
    // TestClass testClass2(10,'a');
    // cout<<"**************(const string& str) constructor**************"<<endl;
    // TestClass testClass3("wanwanvv");
    // string s="hezhuo";
    // TestClass testClass4(s);
    // cout<<"**************copy1 constructor**************"<<endl;
    // MyClass myClass1=string("wanwanvv");
    // cout<<myClass1.getStr()<<endl;
    // cout<<"**************copy2 constructor**************"<<endl;
    // MyClass myClass2=MyClass(string("wanwanvv"));
    // cout<<myClass2.getStr()<<endl;
    // cout<<"**************copy3 constructor**************"<<endl;
    // MyClass myClass3(myClass2);
    // cout<<myClass3.getStr()<<endl;
    // cout<<"**************operator=**************"<<endl;
    // MyClass myClass4;
    // myClass4=myClass3;
    // for(int i=0;i<3;++i){
    //     std::cout<<"--------------------------"<<i<<"--------------------------"<<std::endl;
    //     TestClass* p=TestClass::getInstance();
    //     std::cout<<p<<std::endl;
    // }

    // My_thread my_thread;
    // my_thread.run();
    // char ch;
    // while((ch=getchar())!='q'){
    //     switch (ch)
    //     {
    //         case 'p':
    //             my_thread.pause();
    //             break;
            
    //         case 's':
    //             my_thread.stop();
            
    //         case 'r':
    //             my_thread.resume();
                
    //         default:
    //             break;
    //     }
    // }
    //**************************test SingleProducerCOPnsumer**************
    // test_sigleProducerCOnsumer();
    //**************************test hashTable**************
    test_hashTable();
    return 0;
}