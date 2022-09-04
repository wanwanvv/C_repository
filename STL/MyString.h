/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-08-24 16:07:21
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-09-03 21:29:26
 */
#ifndef MY_STRING_H
#define MY_STRING_H
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <assert.h>
class MyString{
public:
    //直接构造函数
    MyString(const char* str=""):_size(strlen(str)),_capacity(_size){
        _str=new char[_capacity+1];
        strcpy(_str,str);//直到遇到'\0'停止拷贝(包括\0)
    }

    //拷贝构造函数，通过复用的方式完成深拷贝
    MyString(const MyString& s){
        MyString myStr(s._str);
        _str=nullptr;//
        swap(myStr);
    }

    //移动构造函数
    MyString(MyString&& s){
        _str=nullptr;
        swap(s);
    }
    
    //析构函数
    ~MyString(){
        reset();
    }

    //赋值运算符
    MyString& operator=(const MyString& s){
        if(this!=&s){
            reset();
            _size=s._size;
            _capacity=s._capacity;
            _str=new char[_capacity+1];
            strcpy(_str,s._str);
        }
        return *this;
    }

    //移动赋值运算符
    MyString& operator=(MyString&&  s){
        if(this!=&s){
            reset();
            _size=s._size;
            _capacity=s._capacity;
            _str=new char[_capacity+1];
            strcpy(_str,s._str);
            s._str=nullptr;
        }
        return *this;
    }

    //[]运算符
    char& operator[](size_t pos){
        assert(pos<_size);
        return _str[pos];
    }
    const char& operator[](size_t pos) const{
        assert(pos<_size);
        return _str[pos];
    }

    //开辟空间
    void reserve(size_t n){
        if(n>_capacity){
            char* str_tmp=new char[n+1];
            if(_str!=nullptr){
                strcpy(str_tmp,_str);
                delete[] _str;
            }
            _str=str_tmp;
            _capacity=n;
        }
    }

    //resize函数
    void resize(size_t n,char ch='\0'){
        if(n<=_size){
            _str[_size]='\0';
            _size=n;
        }else{
            if(_capacity<n){
                reserve(n);
            }
            memset(_str+_size,ch,n-_size);
            _size=n;
            _str[_size]='\0';
        }
    }

    //push_back函数
    void push_back(char ch)
    {
        if(_size==_capacity){
            reserve(_capacity==0?4:_capacity*2);//注意_capacity==0的情况，这时候需要特殊处理，否则0*2还是0，_capacity还是没变。
        }
        _str[_size++]=ch;
        _str[_size]='\0';
    }

    //pop_back
    void pop_back(){
        assert(_size>0);
        _str[--_size]='\0';
    }

    //append
    void append(const char* str){
        size_t len=strlen(str);
        if(len+_size>_capacity){
            reserve(len+_size);//扩容
        }
        strcpy(_str+_size,str);
        _size+=len;
    }

    //find,正向查找
    size_t find(const char* s, size_t pos=0){
        const char* ptr=strstr(_str+pos,s);//查找子串
        if(ptr==nullptr) return npos;
        else return ptr-_str;
    }

    //插入字符
    MyString& insert(size_t pos,char c){
        assert(pos<=_size);//可以在最后一个位置插入
        if(_size==_capacity) reserve(_capacity==0?4:_capacity*2);
        for(size_t end=_size;end>pos;--end) _str[end]=_str[end-1];
        _str[pos]=c;
        _str[_size++]='\0';
        return *this;
    }

    //插入字符串
    MyString& insert(size_t pos,const char* s){
        assert(pos<=_size);
        size_t len=strlen(s);
        if(_size+len>_capacity) reserve(_capacity+len);
        for(size_t end=_size-1;end>=pos;--end) _str[end+len]=_str[end];
        strncpy(_str+pos,s,len);//不复制\0
        _size+=len;
        _str[_size]='\0';
        return *this;
    }

    //clear，清楚当前对象中的字符串
    void clear(){
        _size=0;//直接把对象中字符串的有效字符个数给成0就好了
        _str[_size]='\0';//0位置处赋值成'\0',后面的不用处理就好了
    }

    //erase
    MyString& erase(size_t pos,size_t n){
        assert(pos<_size);
        if(pos+n>=_size){
            _size=pos;
            _str[_size]='\0';
        }else{
            strcpy(_str+pos,_str+pos+n);
            _size-=n;
        }
        return *this;
    }

    //释放空间
    void reset(){
        if(_str){
            delete []_str;
            _str=nullptr;
            _size=_capacity=0;
        }   
    }

    //交换函数
    void swap(MyString& s){
        std::swap(_str,s._str);
        std::swap(_capacity,s._capacity);
        std::swap(_size,s._size);
    }

    //接口调用函数
    const char* c_str() const{
        return _str;
    }

    size_t size() const{
        return _size;
    }

    size_t capacity() const{
        return _capacity;
    }

private:
    char* _str;//_str指向在堆上开辟好空间的地址
    size_t _size;//记录当前字符串中有效字符的个数(不包含'\0')
    size_t _capacity; //_str指向的空间的大小(不包含'\0')
    const static size_t npos=-1; 
};

//以下运算符重载可以写成友元函数
//算术和关系运算符通常定义为非成员函数
bool operator<(const MyString& s1,const MyString& s2){
    return strcmp(s1.c_str(),s2.c_str())<0;
}

bool operator==(const MyString& s1,const MyString& s2){
    return strcmp(s1.c_str(),s2.c_str())==0;
}

bool operator<=(const MyString& s1,const MyString& s2){
    return s1<s2||s1==s2;
}

bool operator>(const MyString& s1,const MyString& s2){
    return strcmp(s1.c_str(),s2.c_str())>0;
}

bool operator>=(const MyString& s1,const MyString& s2){
    return s1>s2||s1==s2;
}

bool operator!=(const MyString& s1,const MyString& s2){
    return !(s1==s2);
}

std::ostream& operator<<(std::ostream& out,const MyString& s){
    for(size_t i=0;i<s.size();++i) out<<s[i];
    return out;
}

std::istream& operator>>(std::istream& in,MyString& s){
    s.clear();
    char ch=in.get();
    while(ch!=' '&&ch!='\n'){
        s.push_back(ch);
        ch=in.get();
    }
    return in;
}

#endif