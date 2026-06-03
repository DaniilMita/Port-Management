#ifndef PORTMANAGEMENT_RBT_H
#define PORTMANAGEMENT_RBT_H

#include "Nava.h"
#include <iostream>

using namespace std;

typedef enum { RED, BLACK } Color;

typedef struct Nod {
    Nava data;
    Color color;
    struct Nod* left;
    struct Nod* right;
    struct Nod* parent;
} Nod;

typedef struct RBT {
    Nod* root;
} RBT;

inline Nod* NIL = nullptr;

void initNil(){
    if (NIL==nullptr){
    NIL = new Nod();
    NIL->color = BLACK;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
    }
}

/*
 * Functie: creareNod
 * ------------------
 * Creeaza si initializeaza un nod nou pentru arborele Red-Black.
 *
 * Parametri:
 * v - valoarea intreaga care va fi stocata in nod
 *
 * Returneaza:
 * pointer catre nodul nou creat
 */

 Nod* creareNod(Nava v)
{
    Nod* n = new Nod();
    n->data = v;
    n->color = RED;
    n->left = NIL;
    n->right = NIL;
    n->parent = NIL;
    return n;
}

/*
 * Functie: creareArbore
 * ---------------------
 * Creeaza si initializeaza un arbore Red-Black gol.
 *
 * Parametri:
 * nu are
 *
 * Returneaza:
 * pointer catre structura arborelui Red-Black
 */

 RBT* creareArbore()
{
    RBT* t = new RBT();
    t->root = NIL;
    return t;
}

/*
 * Functie: rotatieStanga
 * ----------------------
 * Executa o rotatie la stanga in jurul nodului x.
 * Rotatia este folosita pentru mentinerea proprietatilor arborelui Red-Black.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * x - nodul in jurul caruia se face rotatia
 *
 * Returneaza:
 * nimic (void)
 */

void rotatieStanga(RBT* t, Nod* x)
{
    Nod* y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        t->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/*
 * Functie: rotatieDreapta
 * -----------------------
 * Executa o rotatie la dreapta in jurul nodului y.
 * Rotatia este folosita pentru mentinerea proprietatilor arborelui Red-Black.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * y - nodul in jurul caruia se face rotatia
 *
 * Returneaza:
 * nimic (void)
 */

void rotatieDreapta(RBT* t, Nod* y)
 {

     Nod* x = y->left;
     y->left = x->right;

     if (x->right != NIL)
         x->right->parent = y;

     x->parent = y->parent;

     if (y->parent == NIL)
         t->root = x;
     else if (y == y->parent->left)
         y->parent->left = x;
     else
         y->parent->right = x;

     x->right = y;
     y->parent = x;
 }

/*
 * Functie: minim
 * --------------
 * Determina nodul cu valoarea minima din subarborele
 * care are radacina in nodul x.
 *
 * Parametri:
 * x - radacina subarborelui analizat
 *
 * Returneaza:
 * pointer catre nodul cu valoarea minima
 */

 Nod* minim(Nod* x)
{
    while (x->left != NIL)
        x = x->left;
    return x;
}

/*
 * Functie: succesor
 * -----------------
 * Determina succesorul unui nod in arborele Red-Black.
 * Succesorul este nodul cu cea mai mica valoare mai mare
 * decat valoarea nodului curent.
 *
 * Parametri:
 * x - nodul pentru care se cauta succesorul
 *
 * Returneaza:
 * pointer catre nodul succesor
 */

Nod* succesor(Nod* x)
{
    if (x->right != NIL)
        return minim(x->right);

    Nod* y = x->parent;

    while (y != NIL && x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 * Functie: insertFixup
 * --------------------
 * Repara proprietatile arborelui Red-Black dupa inserarea
 * unui nod nou.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * z - nodul nou inserat care poate incalca proprietatile arborelui
 *
 * Returneaza:
 * nimic (void)
 */

 void insertFixup(RBT* t, Nod* z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Nod* y = z->parent->parent->right;

            if (y->color == RED)
            {
                // COMPLETAT: Cazul 1 (Unchiul y este Rosu)
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotatieStanga(t, z);
                }

                // COMPLETAT: Cazul 3 (Unchiul y este Negru, z e fiu stang)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotatieDreapta(t, z->parent->parent);
            }
        }
        else
        {
            Nod* y = z->parent->parent->left;

            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                // COMPLETAT: Cazul 2 si 3 simetrice
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotatieDreapta(t, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotatieStanga(t, z->parent->parent);
            }
        }
    }

    t->root->color = BLACK; // COMPLETAT: Radacina trebuie sa ramana neagra
}

/*
 * Functie: inserare
 * -----------------
 * Insereaza o valoare noua in arborele Red-Black si
 * apeleaza procedura de reechilibrare.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * val - valoarea care va fi inserata in arbore
 *
 * Returneaza:
 * nimic (void)
 */

 void inserare(RBT* t, Nava val)
{
    Nod* z = creareNod(val);

    Nod* y = NIL;
    Nod* x = t->root;

    while (x != NIL)
    {
        y = x;

        if (z->data.ordineSosire < x->data.ordineSosire)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        t->root = z;
    else if (z->data.ordineSosire < y->data.ordineSosire)
        y->left = z;
    else
        y->right = z;



    insertFixup(t, z);
}

/*
 * Functie: transplant
 * -------------------
 * Inlocuieste subarborele cu radacina u cu subarborele v.
 * Este utilizata in algoritmul de stergere.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * u - nodul care va fi inlocuit
 * v - nodul care il va inlocui pe u
 *
 * Returneaza:
 * nimic (void)
 */

 void transplant(RBT* t, Nod* u, Nod* v)
{
    if (u->parent == NIL)
        t->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

/*
 * Functie: deleteFixup
 * --------------------
 * Repara proprietatile arborelui Red-Black dupa
 * stergerea unui nod.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * x - nodul de la care incepe procesul de reechilibrare
 *
 * Returneaza:
 * nimic (void)
 */

 void deleteFixup(RBT* t, Nod* x)
{
    while (x != t->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Nod* w = x->parent->right;

            if (w->color == RED)
            {
                // COMPLETAT: Cazul 1
                w->color = BLACK;
                x->parent->color = RED;
                rotatieStanga(t, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotatieDreapta(t, w);
                    w = x->parent->right;
                }

                // COMPLETAT: Cazul 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotatieStanga(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            // COMPLETAT: Cazurile simetrice cand x este fiu drept
            Nod* w = x->parent->left;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotatieDreapta(t, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotatieStanga(t, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotatieDreapta(t, x->parent);
                x = t->root;
            }
        }
    }

    x->color = BLACK;
}

/*
 * Functie: stergere
 * -----------------
 * Sterge un nod din arborele Red-Black pe baza valorii date.
 * Daca valoarea nu exista, se afiseaza un mesaj.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 * val - valoarea nodului care trebuie sters
 *
 * Returneaza:
 * nimic (void)
 */

 void stergere(RBT* t, int val)
{
    Nod* z = t->root;

    while (z != NIL && z->data.ordineSosire != val)
    {
        if (val < z->data.ordineSosire)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NIL)
    {
        printf("Nava solicitata nu exista in registrul istoric.\n");
        return;
    }

    if (z->color == RED && z->left == NIL && z->right == NIL)
    {
        transplant(t, z, NIL);
        delete z;
        return;
    }

    Nod* y = z;
    Nod* x;
    Color yOriginal = y->color;

    if (z->left == NIL)
    {
       x = z->right;
       transplant(t, z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        transplant(t, z, z->left);
    }
    else
    {
        y = minim(z->right);
        yOriginal = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginal == BLACK)
        deleteFixup(t, x);

    delete z;
}

/*
 * Functie: parcurgereInOrder
 * -------------------
 * Parcurge arborele Red-Black inordine si afiseaza
 *
 * fiecare nod impreuna cu culoarea sa.
 *
 * Parametri:
 * t - pointer catre arborele Red-Black
 *
 * Returneaza:
 * nimic (void)
 */

void parcurgereInOrder(Nod* nod){
     if (nod==NIL) return;
     parcurgereInOrder(nod->left);

     printf("Nume: %s || Origine: %s pleaca %s  || Prioritate %d || Sosire %d || %s\n",
     nod->data.nume.c_str(),
     nod->data.taraOrigine.c_str(),
     nod->data.taraDestinatie.c_str(),
     nod->data.prioritate,
     nod->data.ordineSosire,
     nod->color==RED?"R":"B");

     parcurgereInOrder(nod->right);
}

/*
 * Functie: afisareCronologie
 * -------------------
 * Actioneaza ca punct de intrare public pentru afisarea istoricului.
 * Verifica daca arborele este gol
 * iar in caz contrar initiaza parcurgerea recursiva In-Order.
 *
 * Parametri:
 * t - pointer catre structura principala a arborelui Red-Black
 *
 * Returneaza:
 * nimic (void)
 */

void afisareCronologie(RBT* t){
    if (t->root == NIL){
        cout << "Registrul cronologic este gol\n";
        return;
    }
    parcurgereInOrder(t->root);
}
 #endif //PORTMANAGEMENT_RBT_H