#ifndef PORTMANAGEMENT_HASHTABLE_H
#define PORTMANAGEMENT_HASHTABLE_H

#include "Nava.h"
#include <iostream>

using namespace std;

typedef struct HashNode{
    string key;
    Nava data;
    HashNode* next;
} HashNode;

typedef struct HashTable{
    HashNode** table;
    int size;
} HashTable;

int hashFunction(string key,int size){
    unsigned long hash=5381;
    for (char c : key){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

HashTable* creareTabel(int size)
{
    HashTable* table = new HashTable();
    table->size = size;
    table->table = new HashNode*[size];
    for (int i = 0; i < size; i++)
        table->table[i] = nullptr;
    return table;
}

void inserareHash(HashTable* table,string key,Nava nava){
    int index = hashFunction(nava.nume,table->size);
    HashNode* node = new HashNode();
    node->key = key;
    node->data = nava;
    node->next = nullptr;

    if(table->table[index] == nullptr){
        table->table[index] = node;
    }
    else{
        node->next = table->table[index];
        table->table[index] = node;
    }
}

HashNode* cautareHash(HashTable* table,string key){
    int index = hashFunction(key,table->size);
    HashNode* temp = table->table[index];
    while(temp != nullptr){
        if(temp->key == key)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void stergereHash(HashTable* table,string key)
{
    int index = hashFunction(key,table->size);
    HashNode* temp = table->table[index];
    HashNode* prev = nullptr;
    while(temp != nullptr){
        if(temp->key == key){
            if(prev == nullptr)
                table->table[index] = temp->next;
            else
                prev->next = temp->next;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

#endif //PORTMANAGEMENT_HASHTABLE_H