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

/*
 * Functie: creareHeap
 * ------------------
 * Aloca memorie si initializeaza o noua structura de tip Max-Heap.
 * Configureaza capacitatea maxima, seteaza dimensiunea initiala la 0
 * si aloca dinamic vectorul intern pentru stocarea obiectelor de tip Nava.
 *
 * Parametri:
 * capacity - valoarea intreaga ce reprezinta numarul maxim de nave
 * pe care le poate stoca heap-ul simultan
 *
 * Returneaza:
 * pointer catre structura Heap nou creata si initializata
 */

Heap* creareHeap(int capacity)
{
    Heap* heap = new Heap();
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = new Nava[capacity];
    return heap;
}

/*
 * Functie: heapifyUp
 * ------------------
 * Restabileste proprietatea de Max-Heap dupa inserarea unui element nou.
 * Compara succesiv nava curenta cu parintele sau si le interschimba pozitiile
 * daca prioritatea navei curente este mai mare decat cea a parintelui.
 *
 * Parametri:
 * heap - pointer catre structura de tip Heap ce contine vectorul de nave
 * i - indexul elementului nou adaugat care trebuie rearanjat in sus
 *
 * Returneaza:
 * nimic (void)
 */

void heapifyUp(Heap* heap, int i){
    int parent = (i-1)/2;
    while(i>0 && heap->arr[parent].prioritate < heap->arr[i].prioritate){
        swap(heap->arr[i], heap->arr[parent]);
        i = parent;
        parent = (i-1)/2;
    }
}

/*
 * Functie: heapifyDown
 * ------------------
 * Restabileste proprietatea de Max-Heap dupa extragerea elementului radacina.
 * Compara succesiv nava curenta cu descendentii sai (stang si drept) si o
 * coboara in structura prin interschimbare cu descendentul care are prioritatea maxima.
 *
 * Parametri:
 * heap - pointer catre structura de tip Heap ce contine vectorul de nave
 * i - indexul elementului de la care porneste rearanjarea in jos
 *
 * Returneaza:
 * nimic (void)
 */

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

/*
 * Functie: inserareHeap
 * ------------------
 * Adauga o nava noua in Max-Heap. Daca structura a atins capacitatea maxima,
 * dubleaza automat spatiul disponibil prin realocare dinamica de memorie,
 * dupa care insereaza elementul la final si il propaga in sus prin heapifyUp.
 *
 * Parametri:
 * heap - pointer catre structura de tip Heap in care se face inserarea
 * nava - obiectul de tip Nava care urmeaza sa fie adaugat in coada
 *
 * Returneaza:
 * nimic (void)
 */

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

/*
 * Functie: extragereHeap
 * ------------------
 * Extrage si returneaza nava cu prioritatea maxima (aflata in radacina heap-ului).
 * Inlocuieste radacina cu ultimul element din vector, scade dimensiunea heap-ului
 * si rearanjeaza structura in jos prin heapifyDown pentru a mentine proprietatea de Max-Heap.
 *
 * Parametri:
 * heap - pointer catre structura de tip Heap din care se extrage nava
 *
 * Returneaza:
 * obiectul de tip Nava extras din varful heap-ului, sau o nava fictiva (goala)
 * cu prioritatea -1 in cazul in care heap-ul este deja gol
 */

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

/*
 * Functie: afisareHeap
 * ------------------
 * Afiseaza la consola toate navele prezente in coada de prioritati.
 * Parcurge liniar vectorul intern al heap-ului si printeaza indexul structural,
 * numele navei, nivelul de prioritate si ordinea sa cronologica de sosire.
 *
 * Parametri:
 * heap - pointer catre structura de tip Heap ale carei elemente vor fi afisate
 *
 * Returneaza:
 * nimic (void)
 */

void afisareHeap(Heap* heap){
    if (heap->size == 0){
        cout << "Nu sunt nave in coada\n";
        return;
    }
    for (int i = 0; i < heap->size; i++){
        cout<<"|"<< i <<"| Nava: "<<heap->arr[i].nume <<" | Prioritate: "<<heap->arr[i].prioritate<<" | Ordine Sosire: "<<heap->arr[i].ordineSosire<<"\n";
    }
}

/*
 * Functie: distrugeHeap
 * ------------------
 * Elibereaza memoria alocata dinamic pentru structura Heap.
 * Sterge vectorul intern de nave si apoi elibereaza pointerul structurii principale.
 */
void distrugeHeap(Heap* heap) {
    if (heap == nullptr) return;

    delete[] heap->arr;
    delete heap;
}
#endif //PORTMANAGEMENT_HEAP_H