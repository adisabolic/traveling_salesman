#include "DisjunktniSkupListe.h"
#include <iostream>
using namespace std;

DisjunktniSkupListe::DisjunktniSkupListe(int n):n(n) {

    pripadnost.resize(n);
    for(int i=0;i<n;i++) {
        pripadnost[i] = new Lista(1, i);
    }
}

Lista* DisjunktniSkupListe::Nadji(int v) {

    return pripadnost[v];

}

void DisjunktniSkupListe::Unija(int v1, int v2) {

    Lista* skup1 = Nadji(v1);
    Lista* skup2 = Nadji(v2);
    if(skup1 != skup2) {
        if(skup1->n < skup2->n)
            SpojiListe(skup2, skup1);
        else
            SpojiListe(skup1, skup2);
    }
}

//Spaja l2 na l1
void DisjunktniSkupListe::SpojiListe(Lista* l1, Lista* l2) {

    l1->n += l2->n;
    l1->rep->sljedeci = l2->glava;
    l1->rep = l2->rep;
    for(auto i = l2->glava ; i != nullptr ; i = i->sljedeci)
        pripadnost[i->element] = l1;
    delete l2->glava;
    delete l2->rep;
}


