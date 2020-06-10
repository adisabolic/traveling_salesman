#include "DisjunktniSkupStablo.h"

using namespace std;

DisjunktniSkupStablo::DisjunktniSkupStablo(int n):n(n) {

    roditelji.resize(n);
    visine.resize(n);
    for(int i=0;i<n;i++) {
        roditelji[i] = i;
        visine[i] = 0;
    }
}

int DisjunktniSkupStablo::Nadji(int v) {

    if(v != roditelji[v])
       roditelji[v] = Nadji(roditelji[v]);
    return roditelji[v];
}

void DisjunktniSkupStablo::Unija(int v1, int v2) {

    int skup1 = Nadji(v1), skup2 = Nadji(v2);
    if(skup1 != skup2) {
        if(visine[skup1] < visine[skup2])
            roditelji[skup1] = skup2;
        else roditelji[skup2] = skup1;
        if(visine[skup1] == visine[skup2])
            visine[skup1]++;

    }
}


