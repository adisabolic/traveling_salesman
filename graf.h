#ifndef GRAF_H
#define GRAF_H
#include <vector>
#include <string>
#include <list>
#include <queue>
using namespace std;

struct Grana {
    int pocetni, krajnji;
    double tezina;
    Grana(int p, int k, double t):pocetni{p},krajnji{k},tezina{t} {}
    friend bool operator<(Grana e1, Grana e2) { return e1.tezina < e2.tezina; }
};

class komparatorGrana {
public:
    int operator() (const Grana& p1, const Grana& p2) {
        return p1.tezina > p2.tezina;
    }
};

class Graf{
    int n;
    vector<vector<long long int>> matrica_susjedstva;

public:
    Graf(string);
    int brojGradova() { return n; }


    //************* POMOCNE FUNKCIJE ZA ALGORITME *************************
    long long int izracunajDuzinuPuta(vector<list<int>>&);
    void napraviHeapGrana (priority_queue<Grana, vector<Grana>, komparatorGrana>&);
    bool imaLiCiklus (vector<list<int>>&, int);


    //************* TSP ALGORITMI *****************************************
    long long int TSP_sporo();
    long long int TSP_brzoListe();
    long long int TSP_brzoStablo();

};


#endif // GRAF_H

