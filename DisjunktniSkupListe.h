#ifndef DISJUNKTNI_SKUP_LISTE_H
#define DISJUNKTNI_SKUP_LISTE_H

#include <vector>
#include "lista.h"
using namespace std;

/*
Svaki skup je jedna lista, spajanje se vrsi tako sto se lista manje duzine zalijepi na kraj druge liste. Za trazenje
kojoj listi neki element pripada cuva se vektor pokazivaca na liste koji za svaki element cuva pokazivac na njegovu list.
Za spajanje dvaju listi koristi se funkcija SpojiListe koja radi u vremenu O(m) gdje je m duzina manje liste. Ona promijeni
sve vrijednosti koje treba kako bi se dvije liste spojile u jednu.
Klasa lista sadrzi samo neophodne elemente (i jos neke ne toliko neophodne) za ispravnu funkcionalnost
klase DisjunktniSkupListe (sadrzi glavu i rep koji pokazuju na prvi i zadnji element liste, jedan konstruktor,
mogucnost dodavanja cvorova na pocetak i kraj, destruktor, funkciju za ispis liste...)
Ova klasa je implementirana na nacin opisan u knjizi "Introduction to Algorithms".
*/

class DisjunktniSkupListe {
    public:
    int n;
    vector<Lista*> pripadnost;

public:
    DisjunktniSkupListe(int);
    Lista* Nadji(int);
    void Unija(int, int);
    void SpojiListe(Lista* l1, Lista* l2);
};

#endif // DISJUNKTNI_SKUP_LISTE_H

