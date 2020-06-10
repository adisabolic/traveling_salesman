#include "lista.h"
#include <iostream>
using namespace std;

Lista::Lista(): n(0), rep(nullptr), glava(nullptr){}

Lista::Lista(int n, int vrijednost): n(0), glava(nullptr), rep(nullptr) {

    for(int i=0;i<n;i++)
        dodajNaKraj(vrijednost);

}

Lista::~Lista() {

    while(glava->sljedeci != nullptr)
        obrisiIzaCvora(glava);
    obrisiIzaCvora(nullptr);

}

int Lista::duzina() {

    return n;

}

Cvor* Lista::pocetak() {

    return glava;

}

Cvor* Lista::kraj() {

    return rep;

}

void Lista::dodajNaPocetak(int element) {

    Cvor *novi = new Cvor(element, nullptr);
    glava = novi;
    if(n == 0)
        rep = novi;
    n++;

}

void Lista::dodajNaKraj(int element) {

    if(glava == nullptr) {
        dodajNaPocetak(element);
        return;
    }
    rep->sljedeci = new Cvor(element, nullptr);
    rep = rep->sljedeci;
    n++;

}

void Lista::obrisiIzaCvora(Cvor *cvor) {
    if(cvor == nullptr) { //brisanje sa pocetka
        if(n == 0)
            return;
        if(n == 1)
            rep = nullptr;
        Cvor *novi_glava = glava->sljedeci;
        delete glava;
        glava = novi_glava;
        n--;
        return;
    }
    if(cvor->sljedeci == nullptr)
        return;

    if(cvor->sljedeci == rep)
        rep = cvor;
    Cvor *za_brisanje = cvor->sljedeci;
    cvor->sljedeci = za_brisanje->sljedeci;
    delete za_brisanje;
    n--;

}

void Lista::ispisi() {
    for(auto it = glava ; it != nullptr ; it = it->sljedeci)
        cout<<it->element<<" ";
    cout<<endl;
}
