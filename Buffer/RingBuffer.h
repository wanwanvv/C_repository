/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-23 10:36:34
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-23 11:42:19
 */
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>
#include <atomic>
#include <sys/types.h> //ssize_t
#include <assert.h>
#include <cstring> //memcpy

class RingBuffer{
public:
    RingBuffer(int initBufferSize=1024);
    ~RingBuffer();

    ssize_t write(const char* str,size_t len);
    ssize_t read(char* str, size_t len);

private:
    char* BeginPtr_();
    const char* BeginPtr_() const;

    void updateReadPtr_(size_t len);
    void updateWritePtr_(size_t len);

    std::vector<char> buffer_;
    std::atomic<size_t> readPos_;
    std::atomic<size_t> writePos_;
    size_t capacity_;
};

#endif