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

 Nod* minim(Nod* x)
{
    while (x->left != NIL)
        x = x->left;
    return x;
}

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

 void insertFixup(RBT* t, Nod* z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Nod* y = z->parent->parent->right;

            if (y->color == RED)
            {

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

    t->root->color = BLACK;
}

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

 void deleteFixup(RBT* t, Nod* x)
{
    while (x != t->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Nod* w = x->parent->right;

            if (w->color == RED)
            {
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

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotatieStanga(t, x->parent);
                x = t->root;
            }
        }
        else
        {
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

void afisareCronologie(RBT* t){
    if (t->root == NIL){
        cout << "Registrul cronologic este gol\n";
        return;
    }
    parcurgereInOrder(t->root);
}
 #endif //PORTMANAGEMENT_RBT_H