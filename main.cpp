#include <iostream>
#include <vector>
#include <fstream>
#include "graf.h"
#include <iomanip>
#include "DisjunktniSkupListe.h"
using namespace std;

int main() {

    //Graf g("./data/wi29.txt");
    //Graf g("./data/dj38.txt");
    Graf g("./data/zi929.txt");
    //Graf g("./data/lu980.txt");
    //Graf g("./data/mu1979.txt");
    //Graf g("./data/nu3496.txt");
    //Graf g("./data/ca4663.txt");
    //Graf g("./data/tz6117.txt");
    //Graf g("./data/eg7146.txt");
    //Graf g("./data/ym7663.txt");


    cout<<"Broj gradova: "<<g.brojGradova()<<endl<<endl;

    cout<<"Spori algoritam"<<endl;
    cout<<"Duzina puta: "<<g.TSP_sporo()<<endl<<endl;

    cout<<"Brzi algoritam (liste) "<<endl;
    cout<<"Duzina puta: "<<g.TSP_brzoListe()<<endl<<endl;

    cout<<"Brzi algoritam (stablo) "<<endl;
    cout<<"Duzina puta: "<<g.TSP_brzoStablo()<<endl<<endl;

}
