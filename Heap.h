#ifndef PORTMANAGEMENT_HEAP_H
#define PORTMANAGEMENT_HEAP_H

#include "Nava.h"
#include <iostream>
using namespace std;

struct Heap{
    Nava* arr;
    int size;
    int capacity;
};

Heap* creareHeap(int capacity)
{
    Heap* heap = new Heap();
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = new Nava[capacity];
    return heap;
}

void heapifyUp(Heap* heap, int i){
    int parent = (i-1)/2;
    while(i>0 && heap->arr[parent].prioritate < heap->arr[i].prioritate){
        swap(heap->arr[i], heap->arr[parent]);
        i = parent;
        parent = (i-1)/2;
    }
}

void heapifyDown(Heap* heap,int i){
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    if(left<heap->size && heap->arr[left].prioritate > heap->arr[largest].prioritate)
        largest = left;
    if(right<heap->size && heap->arr[right].prioritate > heap->arr[largest].prioritate)
        largest = right;
    if(largest != i){
        swap(heap->arr[i], heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

void inserareHeap(Heap* heap,Nava nava){
    if(heap->size == heap->capacity){
        heap->capacity *= 2;
        Nava* temp = new Nava[heap->capacity];
        for(int i = 0; i < heap->size; i++)
            temp[i] = heap->arr[i];
        delete[] heap->arr;
        heap->arr = temp;
    }
    heap->arr[heap->size] = nava;
    heapifyUp(heap, heap->size);
    heap->size++;
}

Nava extragereHeap(Heap* heap)
{
    if(heap->size <= 0){
        return Nava("","","","",0,-1);
    }
    if(heap->size == 1){
        heap->size--;
        return heap->arr[0];
    }
    Nava radacina = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    heapifyDown(heap, 0);
    return radacina;
}

void afisareHeap(Heap* heap){
    if (heap->size == 0){
        cout << "Nu sunt nave in coada\n";
        return;
    }
    for (int i = 0; i < heap->size; i++){
        cout<<"|"<< i <<"| Nava: "<<heap->arr[i].nume <<" | Prioritate: "<<heap->arr[i].prioritate<<" | Ordine Sosire: "<<heap->arr[i].ordineSosire<<"\n";
    }
}
#endif //PORTMANAGEMENT_HEAP_H