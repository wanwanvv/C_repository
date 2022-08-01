#include "./ProducerConsumer.h"

int SingleProducerConsumer::cnt_=0;

void SingleProducerConsumer::produceItem(int item){
    {
        std::unique_lock<std::mutex> lk(mutex_);
        while((writePos_+1)%bufferSize_==readPos_){
            producerCv_.wait(lk);
        }
        itemBuffer_[writePos_]=item;
        writePos_=(++writePos_)%bufferSize_;
    }
    consumerCv_.notify_all();
}

int SingleProducerConsumer::consumeItem(){
    int data=-1;
    {
        std::unique_lock<std::mutex> lk(mutex_);
        while(readPos_==writePos_){
            consumerCv_.wait(lk);
        }
        data=itemBuffer_[readPos_];
        readPos_=(++readPos_)%bufferSize_;
    }
    producerCv_.notify_all();
    return data;
}

void SingleProducerConsumer::produceTask(){
    for(int i=0;i<producerSize_;++i){
         std::cout << "Produce the " << i << "^th item..." << std::endl;
    }
}

void SingleProducerConsumer::consumeTask(){
    while(1){
        sleep(1);
        int item=consumeItem();
        std::cout << "Consume the " << item << "^th item" << std::endl;
        if(++cnt_==consumerSize_) break;
    }
}

void SingleProducerConsumer::run(){
    std::thread producer(&SingleProducerConsumer::produceTask,this);
    std::thread consumer(&SingleProducerConsumer::consumeTask,this);
    producer.join();
    consumer.join();
}