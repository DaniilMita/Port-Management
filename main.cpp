#include <iostream>
#include <string>
#include "HashTable.h"
#include "Heap.h"
#include "RBT.h"
#include "Nava.h"

using namespace std;

/*
 * Functie: calculeazaPunctaj
 * ------------------
 * Calculeaza scorul numeric de prioritate al unei nave pe baza caracteristicilor sale.
 * Acorda un bonus fix pentru navele militare si adauga puncte specifice in functie
 * de incarcatura transportat.
 *
 * Parametri:
 * esteMilitara - valoare booleana ce indica daca nava este militara sau nu
 * tipIncarcatura - string ce specifica categoria de marfa (Alimente, Combustibil ...)
 *
 * Returneaza:
 * un numar intreg (score) ce reprezinta ponderea totala de prioritate a navei
 */

int calculeazaPunctaj(bool esteMilitara,string tipIncarcatura){
    int score = 0;
    if(esteMilitara)
        score += 8;
    if(tipIncarcatura == "Alimente")
        score += 7;
    else if(tipIncarcatura == "Electronice")
        score += 5;
    else if(tipIncarcatura == "Combustibil")
        score += 10;
    else{
        score += 3;
    }
    return score;
}

void afisareMeniu()
{
    cout << "\n==================Meniu=================\n";
    cout << "1. Inregistare nava noua\n";
    cout << "2. Procesare nava cu prioritate maxima\n";
    cout << "3. Cauta detalii nava dupa nume\n";
    cout << "4. Afisare jurnal cronologic sosiri\n";
    cout << "5. Afisare coada prioritati\n";
    cout << "6. Iesire program\n";
    cout << "Optiunea selectata: ";
}

int main(){
    initNil();

    RBT* arboreSosiri = creareArbore();
    Heap* coadaPrioritati = creareHeap(10);
    HashTable* registru = creareTabel(13);

    int optiune;
    int contorSosire = 1;

    do {
        afisareMeniu();
        if (!(cin >> optiune))
        {
            cout << "Optiune invalida.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        switch (optiune){
            case 1:{
                    Nava nava;
                    string Militar;
                    cout << "Nume nava: ";
                    getline(cin,nava.nume);
                    cout << "Tara origine: ";
                    getline(cin,nava.taraOrigine);
                    cout << "Tara destinatie: ";
                    getline(cin,nava.taraDestinatie);
                    cout << "Tip container (Alimente/Electronice/Combustibil/Standard): ";
                    getline(cin,nava.tipContainer);
                    cout << "Este nava militara? (da/nu): ";
                    cin >> Militar;

                    nava.ordineSosire = contorSosire++;

                    bool esteMilitara = (Militar == "da");
                    nava.prioritate = calculeazaPunctaj(esteMilitara,nava.tipContainer);

                    inserare(arboreSosiri,nava);
                    inserareHeap(coadaPrioritati,nava);
                    inserareHash(registru,nava.nume,nava);

                    cout << "Nava \"" << nava.nume << "\" inregistrata cu succes! Prioritatea calculata: " << nava.prioritate << "\n";
                    break;
            }
            case 2:{
                    Nava urgenta=extragereHeap(coadaPrioritati);
                    if(urgenta.prioritate == -1){
                        cout<<"Nu exista nave in asteptare \n";
                    }
                    else{
                        cout<<"Nava urgenta: "<<urgenta.nume<<"\n";

                        stergere(arboreSosiri,urgenta.ordineSosire);
                        stergereHash(registru,urgenta.nume);
                    }
                    break;
            }
            case 3: {
                    string deCautat;
                    cout << "Introduceti numele navei cautate: ";
                    getline(cin, deCautat);
                    HashNode* gasit = cautareHash(registru, deCautat);
                    if (gasit != nullptr) {
                        cout << "Nava Gasita! Origine: " << gasit->data.taraOrigine
                             << " | Destinatie: " << gasit->data.taraDestinatie
                             << " | Prioritate Scriere: " << gasit->data.prioritate << "\n";
                    } else {
                        cout << "Nava solicitata nu se afla in perimetrul portuar.\n";
                    }
                    break;
            }
            case 4: {
                    cout << "\n--- JURNAL CRONOLOGIC SOSIRI ---\n";
                    afisareCronologie(arboreSosiri);
                    break;
            }
            case 5: {
                    cout << "\n--- STARE ACTUALA COADA PRIORITATI ---\n";
                    afisareHeap(coadaPrioritati);
                    break;
            }
            case 6: {
                    cout << "Sistem oprit.\n";
                    break;
            }
        }
    } while (optiune != 6);
    distrugeTabel(registru);
    distrugeHeap(coadaPrioritati);
    return 0;
}