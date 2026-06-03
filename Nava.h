#ifndef PORTMANAGEMENT_NAVA_H
#define PORTMANAGEMENT_NAVA_H

#include <string>
using namespace std;

struct Nava{
    string nume;
    string taraOrigine;
    string taraDestinatie;
    string tipContainer;
    int prioritate;
    int ordineSosire;

    Nava(string n="", string t="", string trO="", string dest="",int ord=0, int pr=-1,) {
        nume = n;
        tipContainer = t;
        taraOrigine = trO;
        taraDestinatie = dest;
        ordineSosire = ord;
        prioritate = pr;
    }
};



#endif //PORTMANAGEMENT_NAVA_H