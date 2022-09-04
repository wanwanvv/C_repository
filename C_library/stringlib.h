/*
 * @Descripttion:
 * @version:
 * @Author: wanwanvv
 * @Date: 2022-08-26 09:49:57
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-09-03 11:37:17
 */
#ifndef STRING_LIB_H
#define STRING_LIB_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
// memcpy
/**
 * @name: 
 * @msg: 
 * @param {void} *dest 
 * @param {void} *src
 * @param {size_t} n
 * @return {*}
 */
void *mempy(void *dest, const void *src, size_t n)//为了尽量使适用范围广，memecpy的参数写为void*
{
    assert((dest != nullptr) && (src != nullptr));
    unsigned char *dest1 = (unsigned char *)dest;//memcpy操作的最小单位是byte
    unsigned char *src1 = (unsigned char *)src;
    while (n--)
    {
        *dest1++ = *src1++;
    }
    return dest1;
}

// memset
void* memset(void* dest,int val,size_t n){
    assert(dest!=nullptr);
    unsigned char* dest1=(unsigned char*)dest;
    char val1=val;
    while(n--){
        *dest1++=val;
    }
    return dest1;//返回的是新指针(即最后的下一个位置)
}

// strcpy
char* strcpy(char* strDest,const char* strSrc){
    assert(strDest!=nullptr&&strSrc!=nullptr);
    char* strDest1=strDest;
    while((*strDest1++=*strSrc++)!='\0');
    return strDest;
}

// strncpy
char* strncpy(char* strDest,const char* strSrc,size_t n){
    assert(strDest!=nullptr&&strSrc!=nullptr);
    char* strDest1=strDest;
    while(n--&&(*strDest1++=*strSrc++)!='\0');
    return strDest1;
}

// strcmp
int strcmp(const char* dest,const char* src){
    assert(dest!=nullptr&&src!=nullptr);
    while(*src&&*dest&&(*src==*dest)){
        ++src;
        ++dest;
    }
    return *dest-*src;
}

// atoi
int atoi(const char* str){
    int num=0;
    if(str==nullptr) return num;
    bool flag=true;
    if(*str=='+'||*str=='-'){
        if(*str=='-') flag=false;
        ++str;
    }
    while(*str){
        num=num*10+(*str++-'0');
    }
    return flag?num:-num;
}

// itoa
/**
 * @name: 
 * @msg: 
 * @param {int} data 想要转换的整数
 * @param {char*} p 输出的目标字符串地址
 * @param {int} radix 转换的进制（2-36）
 * @return {*} 转换成功则返回该目标字符串的地址，失败则返回NULL
 */
char* itoa(int data,char* p,int radix){
    if(radix<2||radix>36) return nullptr;
    char* buff=(char*)malloc(33);
    size_t i=0,j=0;
    char ch;
    if(data<0){
        *p++='-';
        data=-data;
    }
    while(data){
        ch=data%radix;
        if(ch<10) buff[i++]='0'+ch;
        else buff[i++]='a'+(ch-10);
        data/=data;
    }
    for(j=i-1;j>=0;--j){
        *p++=buff[j];
    }
    *p='\0';
    return p;
}

// big_little_endian
uint32_t bitToLittle(uint32_t value){
    return (value&0xff000000)>>24|(value&0x00ff0000)>>8|(value&0x0000ff00)<<8|(value&0x000000ff)<<24;
}


//打印二进制
void print_b(void* p,size_t n){
    assert(p!=nullptr);
    unsigned long data=*((unsigned long*)p);
    int length=n*8;
    int cnt=0;
    while(length-->0){
        printf("%lu",(data>>length)&0x1);
        ++cnt;
        if(cnt%8==0) printf(" ");
    }
}

#endif