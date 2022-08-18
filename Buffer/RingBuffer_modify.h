/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-03 21:03:06
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-08-18 09:12:05
 */
#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>
#include <cstring>
#include <mutex>
#include <assert.h>
#include <mutex>
#include "../STL/SpinLock.h"

class RingBuffer{
public:
    RingBuffer()= default;
    explicit RingBuffer(int size) {
        size_=size;
        if(!is_power_of_two(size_)) size_=roundup_power_of_two(size_);
        buffer_=(uint8_t*)malloc(sizeof(uint8_t)*size_);
        if(!buffer_){
            std::cerr<<"Allocate memory faled!"<<std::endl;
            exit(1);
        }
        std::memset(buffer_,0,size_);
    }

    ~RingBuffer(){
        SpinLock lock(flag_);
        {
            if(buffer_){
                free(buffer_);
                buffer_=0;
            }
        }
    }

    uint32_t write(char* buf, uint32_t siz){
        if(siz>remain_length()) return 0;
        // #ifdef USE_MB
        //     smp_mb();
        // #endif
        SpinLock lock(flag_);
        {
            uint32_t i=std::min(siz,size_-(writePos_&(size_-1)));
            std::memcpy(buffer_+(writePos_&(size_-1)),buf,i);
            std::memcpy(buffer_,buf+i,siz-i);//当siz-i<0时memcpy不工作
            writePos_+=siz;
        }
        return siz;
    }

    uint32_t read(char* buf, uint32_t siz){
        if(is_empty()) return 0;
        // #ifdef USE_MB
        //     smp_mb();
        // #endif
        SpinLock lock(flag_);
        {
            siz=std::min(siz,rd_length());
            uint32_t i=std::min(siz,size_-(readPos_&(size_-1)));
            std::memcpy(buf,buffer_+(readPos_&(size_-1)),i);
            std::memcpy(buf+i,buffer_,siz-i);
            readPos_+=siz;
        }
        return siz;
    }


    void printContent() const{
        printf("printContent: size_=%d readPos_=%d, writePos_=%d\n",size_,readPos_,writePos_);
        for(uint32_t i=0;i<size_;++i){
            printf("%c",*(buffer_+i));
        }
        printf("\n");
    }


private:
    std::atomic_flag flag_{ATOMIC_FLAG_INIT};
    uint8_t* buffer_{nullptr};
    uint32_t readPos_{0};
    uint32_t writePos_{0};
    uint32_t size_{0};

    bool is_empty() const{
        return size_==writePos_-readPos_;
    }

    bool is_full() const{
        return readPos_==writePos_;
    }

    bool is_power_of_two(uint32_t siz){
        if(siz<2) return false;
        return (siz&(siz-1))==0;
    }

    uint32_t roundup_power_of_two(uint32_t siz){
        uint32_t i=0;
        while(siz){
            ++i;
            siz>>=1;
        }
        return 1U<<i;
    }

    uint32_t rd_length(){
        return writePos_-readPos_;
    }

    uint32_t remain_length(){
        return size_-rd_length();
    }

};

#endif
