#ifndef LISTA_H
#define LISTA_H

struct Cvor {
    int element;
    Cvor *sljedeci;
    Cvor(int element, Cvor * sljedeci):element(element),sljedeci(sljedeci){}
};

class Lista {

    private:

    Cvor *rep;
    Cvor *glava;
    int n;

    public:

    friend class DisjunktniSkupListe;
    Lista();
    Lista(int n, int vrijednost);
    ~Lista();

    int duzina();
    Cvor* pocetak();
    Cvor* kraj();
    void dodajNaKraj(int element);
    void dodajNaPocetak(int element);
    void obrisiIzaCvora(Cvor *cvor);

    void ispisi();
};

#endif // LISTA_H
