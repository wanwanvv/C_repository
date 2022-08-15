/*
 * @Descripttion: 
 * @version: 
 * @Author: wanjingyi
 * @Date: 2022-08-06 20:22:21
 * @LastEditors: sueRimn
 * @LastEditTime: 2022-08-06 20:54:58
 */
#ifndef BIT_MAP_H
#define BIT_MAP_H
#define INT_BITS sizeof(int)
#define  SHIFT 5
#define MASK 0X1f

class BitMap{
public:
    BitMap()=default;
    BitMap(unsigned int max_num):maxNum_(max_num){
        bitmap_=new int[maxNum_/INT_BITS+1];
    }

    void set(unsigned int i){
        if(i>maxNum_) return;
        bitmap_[i>>SHIFT]|=1<<(i&MASK);
    }

    bool test(unsigned int i){
        return bitmap_[i>>SHIFT]&(1<<(i&MASK));
    }

    void clear(unsigned int i){
        bitmap_[i>>SHIFT]&=(~(1<<(i&MASK)));
    }

private:
    unsigned  int maxNum_{0};
    int* bitmap_{nullptr};
};

#endif // !BIT_MAP_H