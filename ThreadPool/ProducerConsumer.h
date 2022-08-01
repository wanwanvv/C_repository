/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-17 16:00:22
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-25 11:38:15
 */
#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <unistd.h>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <vector>
#include <iostream>

class SingleProducerConsumer{
public:
    SingleProducerConsumer(int bufferSize, int consumerSize, int producerSize):
    bufferSize_(bufferSize),itemBuffer_(bufferSize),consumerSize_(consumerSize),producerSize_(producerSize),readPos_(0),writePos_(0){}
    
    ~SingleProducerConsumer()=default;

    void run();//测试运行
    void produceItem(int item);
    int consumeItem();
    void produceTask();//生产者
    void consumeTask();//消费者

private:
    std::condition_variable producerCv_;
    std::condition_variable consumerCv_;
    std::mutex mutex_;
    std::vector<std::thread> threads_;
    
    std::vector<int> itemBuffer_;
    size_t readPos_;
    size_t writePos_;
    const int bufferSize_;
    static int cnt_;
    int consumerSize_;
    int producerSize_;

};

#endif