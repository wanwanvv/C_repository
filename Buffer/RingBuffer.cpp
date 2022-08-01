/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-23 10:38:03
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-23 11:41:16
 */
#include "./RingBuffer.h"

RingBuffer::RingBuffer(int initBufferSize):buffer_(initBufferSize),capacity_(initBufferSize),readPos_(0),writePos_(0){

}

char* RingBuffer::BeginPtr_(){
    return &(*buffer_.begin());
}

const char* RingBuffer::BeginPtr_() const{
    return &(*buffer_.begin());
}

void RingBuffer::updateReadPtr_(size_t len){
    assert(len<=capacity_);
    readPos_=(readPos_+len)%capacity_;
}

void RingBuffer::updateWritePtr_(size_t len){
    assert(len<=capacity_);
    writePos_=(writePos_+len)%capacity_;
}

ssize_t RingBuffer::write(const char* str,size_t len){
    len=std::min(len,capacity_);
    if(strlen(str)<len) return -1;
    if(len<=capacity_-writePos_){
        std::memcpy(BeginPtr_()+writePos_,str,len);
    }else{
        std::memcpy(BeginPtr_()+writePos_,str,capacity_-writePos_);
        std::memcpy(BeginPtr_(),str+(capacity_-writePos_),len-(capacity_-writePos_));
    }
    updateWritePtr_(len);
    return len;
}
   ssize_t RingBuffer::read(char* str, size_t len){
       len=len%capacity_;
       if(writePos_>=readPos_){
           //情况一：写索引>=读索引
            len=std::min(len,writePos_-readPos_);
            memcpy(str,BeginPtr_()+readPos_,len);
       }else{
           if(len<=capacity_-readPos_){
               //情况二
               memcpy(str,BeginPtr_()+readPos_,len);
           }else{
               //情况三
               memcpy(str,BeginPtr_()+readPos_,len);
               memcpy(str,BeginPtr_(),len-(capacity_-readPos_));
           }
       }
       updateReadPtr_(len);
       return len;
   }