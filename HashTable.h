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

/*
 * Functie: hashFunction
 * ------------------
 * Calculeaza un index numeric pe baza unui string folosind algoritmul DJB2.
 * Converteste numele navei intr-o valoare numerica si aplica operatia modulo
 * (compresie)
 * pentru a incadra rezultatul in limitele tabelei.
 *
 * Parametri:
 * key - string-ul (numele navei) care va fi transformat in hash
 * size - dimensiunea maxima a tabelei Hash
 *
 * Returneaza:
 * un numar intreg reprezentand indexul unde va fi stocata nava
 */

int hashFunction(string key,int size){
    unsigned long hash=5381;
    for (char c : key){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

/*
 * Functie: creareTabel
 * ------------------
 * Creeaza si initializeaza o tabela Hash noua in memorie.
 * Aloca spatiu pentru structura principala, seteaza capacitatea
 * si initializeaza toate sloturile din vector cu nullptr.
 *
 * Parametri:
 * size - dimensiunea pe care o va avea tabela
 *
 * Returneaza:
 * pointer catre tabela Hash nou creata si initializata
 */

HashTable* creareTabel(int size){
    HashTable* table = new HashTable();
    table->size = size;
    table->table = new HashNode*[size];
    for (int i = 0; i < size; i++)
        table->table[i] = nullptr;
    return table;
}

/*
 * Functie: inserareHash
 * ------------------
 * Insereaza o nava noua in tabela Hash pe baza numelui sau.
 * Calculeaza indexul prin functia de dispersie si adauga nodul in tabel;
 * in caz de coliziune, noul nod este inserat la inceputul listei .
 *
 * Parametri:
 * table - pointer catre tabela Hash in care se face inserarea
 * key - string-ul ce reprezinta cheia de identificare a nodului
 * nava - structura cu datele complete ale navei care trebuie salvata
 *
 * Returneaza:
 * nimic (void)
 */

void inserareHash(HashTable* table,string key,Nava nava){
    int i = hashFunction(nava.nume,table->size);
    HashNode* node = new HashNode();
    node->key = key;
    node->data = nava;
    node->next = nullptr;

    if(table->table[i] == nullptr){
        table->table[i] = node;
    }
    else{
        node->next = table->table[i];
        table->table[i] = node;
    }
}

/*
 * Functie: cautareHash
 * ------------------
 * Cauta o nava in tabela Hash pe baza numelui primit ca cheie.
 * Calculeaza indexul unic prin functia de dispersie si parcurge
 * liniar lista inlantuita din acel slot pana gaseste potrivirea.
 *
 * Parametri:
 * table - pointer catre tabela Hash in care se efectueaza cautarea
 * key - string-ul ce reprezinta numele navei cautate
 *
 * Returneaza:
 * pointer catre nodul HashNode gasit, sau nullptr daca nava nu exista
 */

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

/*
 * Functie: stergereHash
 * ------------------
 * Elimina o nava din tabela Hash pe baza numelui primit ca cheie.
 * Identifica slotul prin functia de dispersie, parcurge lista inlantuita
 * mentinand un pointer catre nodul precedent si elibereaza memoria nodului sters.
 *
 * Parametri:
 * table - pointer catre tabela Hash din care se va sterge nava
 * key - string-ul ce reprezinta numele navei care trebuie eliminate
 *
 * Returneaza:
 * nimic (void)
 */

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

/*
 * Functie: distrugeTabel
 * ------------------
 * Elibereaza toata memoria alocata dinamic pentru tabela Hash.
 * Parcurge fiecare slot, sterge nodurile din listele inlantuite (Chaining)
 * si la final sterge vectorul principal de pointeri si structura tabelei.
 */
void distrugeTabel(HashTable* table) {
    if (table == nullptr) return;

    for (int i = 0; i < table->size; i++) {
        HashNode* current = table->table[i];
        while (current != nullptr) {
            HashNode* deSters = current;
            current = current->next;
            delete deSters;
        }
    }

    delete[] table->table;
    delete table;
}

#endif //PORTMANAGEMENT_HASHTABLE_H