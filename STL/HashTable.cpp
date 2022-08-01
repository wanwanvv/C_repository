#include "./HashTable.h"

HashTable::HashTable(){
    for(int i=0;i<hashSize_;++i) hashNodes_[i]=nullptr;
}

HashTable::~HashTable(){
    for(int i=0;i<hashSize_;++i){
        Node* cur=hashNodes_[i];
        while(cur){
            Node* tmp=cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            cur=tmp;
        }
    }
}

char* HashTable::init_(const char* str){
    int len=strlen(str)+1;
    char* ns=(char*)malloc(len*sizeof(char));
    strcpy(ns,str);
    return !ns?nullptr:ns;
}

size_t HashTable::hashFunction_(const char* key){
    size_t hash=0;
    while(*key){
        hash+=(hash>>5)+(*key++);
    }
    return hash%hashSize_;
}

Node* HashTable::lookUp_(const char* key){
    size_t index=hashFunction_(key);
    Node* cur=hashNodes_[index];
    while(cur){
        if(strcmp(cur->key,key)) return cur;
        cur=cur->next;
    }
    return cur;
}

bool HashTable::insert(const char* key,const char* value){
    size_t index;
    Node* node;
    if(!lookUp_(key)){
        index=hashFunction_(key);
        node=(Node*)malloc(sizeof(Node));
        if(!node) return false;
        node->key=init_(key);
        if(!node->key) return false;
        node->next=hashNodes_[index];
        hashNodes_[index]=node;
    }else{
        free(node->value);
    }
    node->value=init_(value);
    return true;
}

void HashTable::display(){
    for(int i=0;i<hashSize_;++i){
        Node*  cur=hashNodes_[i];
        if(!cur){
            printf("[]\n");
        }else{
            printf("[");
            while(cur){
                printf("(%s,%s)",cur->key,cur->value);
                cur=cur->next;
            }
            printf("]\n");
        }
    }
}