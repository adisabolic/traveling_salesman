#ifndef DISJUNKTNI_SKUP_STABLO_H
#define DISJUNKTNI_SKUP_STABLO_H

#include <vector>
using namespace std;

/*
Svaki skup je jedno stablo, spajanje se vrsi tako sto se stablo manje visine zalijepi na korijen drugog stabla. Za trazenje
kojem stablu neki element pripada cuva se vektor roditelji koji za svaki element cuva njegovog roditelja u stablu. Potraga
ide kroz roditelje dok se ne dodje do korijena stabla te se on i vraca. Cuva se i vektor visine kako bi se znalo
koje stablo je manje (ono nije uvijek tacno, jer se uniranjem dva stabla usput mijenjaju i roditelj u drugom stablu
zbog brze pretrage, a tada se ne mijenja visina stabla, jer ne moze u konstantnom vremenu da se to uradi. Zbog toga je
moguce da se nekad zalijepi vece na manje stablo).
*/

class DisjunktniSkupStablo {
    int n;
    vector<int> roditelji,visine;

public:
    DisjunktniSkupStablo(int);
    int Nadji(int);
    void Unija(int, int);
};

#endif // DISJUNKTNI_SKUP_STABLO_H

