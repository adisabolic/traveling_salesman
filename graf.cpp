#include "graf.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <ctime>
#include <chrono>
#include "DisjunktniSkupStablo.h"
#include "DisjunktniSkupListe.h"
using namespace std;

/* Racuna Euklidsku udaljenost izmedju dva grada sa datim koordinatama.
*/

long long int EuklidskaUdaljenost(pair<double, double> T1, pair<double, double> T2) {

    return round(sqrt((T1.first - T2.first)*(T1.first - T2.first) + (T1.second - T2.second)*(T1.second - T2.second)));
}

/* Jedini konstruktor za klasu graf, prima putanju do tekstualnog fajla sa podacima, a zatim ih ucitava, racuna udaljenosti
   izmedju svaka dva cvora, te spasava te udaljenosti u matricu susjedstva grafa.
*/

Graf::Graf(string fajl) {

    ifstream fin(fajl);
    int n;
    fin>>n;
    this->n = n;

    matrica_susjedstva = vector<vector<long long int>>(n, vector<long long int>(n));

    vector<pair<double, double>> koordinate(n);
    int redniBrojCvora;

    for(int i = 0 ; i < n ; i++) {
        fin>>redniBrojCvora;
        fin>>koordinate[i].first>>koordinate[i].second;
    }

    fin.close();

    for(int i = 0 ; i < n ; i++)
        for(int j = i + 1 ; j < n ; j++)
            matrica_susjedstva[i][j] = matrica_susjedstva[j][i] = EuklidskaUdaljenost(koordinate[i], koordinate[j]);

}

/* Funkcija prima vektor listi puta kojeg neki algoritam pronadje i racuna ukupnu duzinu puta
   Pri tome je v[i] lista grana koje poticu iz cvora i na tom putu. Funkcija se koristi u sva 3 algoritma.
*/

long long int Graf::izracunajDuzinuPuta(vector<list<int>> &put) {

    long long int duzina(0);

    for(int i = 0; i < put.size() ; i++)
        for(auto it = put[i].begin() ; it != put[i].end() ; it++)
                if(i < *it)
                    duzina += matrica_susjedstva[i][*it];
    return duzina;
}

/* Pravi heap svih grana u grafu, koji je potreban za svaki od 3 algoritma. Napravljena je klasa komparatorGrana kako bi
   na vrhu heap-a bila grana najmanje tezine.
*/

void Graf::napraviHeapGrana (priority_queue<Grana, vector<Grana>, komparatorGrana> &grane) {

    for(int i = 0 ; i < n ; i++)
        for(int j = i + 1 ; j < n ; j++)
            grane.push(Grana(i, j, matrica_susjedstva[i][j]));

}

/* Za dati put (iste strukture kao u funkciji izracunajDuzinuPuta) provjerava da li postoji ciklus, koristeci BFS.
*/

bool Graf::imaLiCiklus (vector<list<int>> &put, int pocetni) {

    vector<int> ko_ga_je_otkrio(n,-1); //-1 nisu otkriveni, -2 za pocetni
    queue<int> red;

    red.push(pocetni);
    ko_ga_je_otkrio[pocetni] = -2;

    while(!red.empty()) {
        int trenutni = red.front();
        red.pop();
        for(auto it = put[trenutni].begin(); it != put[trenutni].end(); it++)
            if(ko_ga_je_otkrio[*it] == -1) {
                red.push(*it);
                ko_ga_je_otkrio[*it] = trenutni;
            }
            else if(ko_ga_je_otkrio[trenutni] != *it)
                return true;
    }

    return false;
}

/* Najsporija implementacija trazenog algoritma, radi na nacin da se prvo napravi heap grana, radi lakseg dohvatanja najmanje grane. Ta grana
   se dodaje na trenutni put. Ako neki od cvorova sa te grane dosad nije bio posjecen, sigurno ne nastaje ciklus,
   pa se ta grana sigurno dodaje (bez ove provjere prije provjere da li je nastao ciklus, algoritam je puno sporiji.
   Zatim se provjerava da li je nastao ciklus, ili je neki od stepena krajnjih cvorova te grane
   postao veci od 2, u kojem se slucaju data grana brise sa trenutnog puta. Ova procedura se ponavlja n-1 puta. Na kraju se
   jos prodje kroz put da bi se nasli krajnji cvorovi puta koji se zatim i spoje. Na kraju se vraca ukupna duzina puta
   koristeci funkciju izracunajDuzinuPuta.
*/

long long int Graf::TSP_sporo() {

    clock_t vrijemePocetak((clock()));

    vector<list<int>> put(n);
    vector<bool> posjecen(n, false);
    priority_queue<Grana, vector<Grana>, komparatorGrana> grane;
    napraviHeapGrana(grane);

    int brojDodatihGrana(0);

    while(brojDodatihGrana != n - 1) {
        Grana najmanja = grane.top();
        grane.pop();

        put[najmanja.pocetni].push_back(najmanja.krajnji);
        put[najmanja.krajnji].push_back(najmanja.pocetni);

        if((put[najmanja.pocetni].size() > 2 || put[najmanja.krajnji].size() > 2) ||
            ((posjecen[najmanja.pocetni] && posjecen[najmanja.krajnji]) && imaLiCiklus(put, najmanja.pocetni))) {
            put[najmanja.pocetni].erase(--put[najmanja.pocetni].end());
            put[najmanja.krajnji].erase(--put[najmanja.krajnji].end());
        }
        else {
            posjecen[najmanja.pocetni] = posjecen[najmanja.krajnji] = true;
            brojDodatihGrana++;
        }

    }

    int prvi(-1), zadnji(-1);

    for(int i = 0 ; i < n ; i++)
        if(put[i].size() < 2){
            if(prvi == -1)
                prvi = i;
            else {
                zadnji = i;
                break;
            }
        }

    put[prvi].push_back(zadnji);
    put[zadnji].push_back(prvi);

    long long int duzinaPuta(izracunajDuzinuPuta(put));

    clock_t vrijemeKraj((clock()));
    cout<<"Algoritam je zavrsio za "<<double(vrijemeKraj - vrijemePocetak)/CLOCKS_PER_SEC<<" sekundi."<<endl;

    return duzinaPuta;

}

/* Jedina razlika u odnosu na spori algoritam je sto se koriste disjunktni skupovi (implementirani na ideji listi)
   za provjeru da li dodavanje grane pravi ciklus (ako se krajnji cvorovi te grane nalaze u istom skupu nastaje ciklus,
   u suprotnom ne nastaje). Takodjer, grana se ne dodaje na put prije ove provjere, pa nema potrebe za njenim eventualnim brisanjem.
*/

long long int Graf::TSP_brzoListe() {

    clock_t vrijemePocetak((clock()));

    vector<list<int>> put(n);
    priority_queue<Grana, vector<Grana>, komparatorGrana> grane;
    napraviHeapGrana(grane);
    DisjunktniSkupListe liste(n);

    int brojDodatihGrana(0);

    while(brojDodatihGrana != n - 1) {
        Grana najmanja = grane.top();
        grane.pop();
        if(liste.Nadji(najmanja.pocetni) != liste.Nadji(najmanja.krajnji)
           && put[najmanja.pocetni].size() < 2 && put[najmanja.krajnji].size() < 2) {
            put[najmanja.pocetni].push_back(najmanja.krajnji);
            put[najmanja.krajnji].push_back(najmanja.pocetni);
            liste.Unija(najmanja.pocetni, najmanja.krajnji);
            brojDodatihGrana++;
        }
    }

    int prvi(-1), zadnji(-1);

    for(int i = 0 ; i < n ; i++)
        if(put[i].size() < 2){
            if(prvi == -1)
                prvi = i;
            else{
                zadnji = i;
                break;
            }
        }

    put[prvi].push_back(zadnji);
    put[zadnji].push_back(prvi);

    long long int duzinaPuta(izracunajDuzinuPuta(put));

    clock_t vrijemeKraj((clock()));
    cout<<"Algoritam je zavrsio za "<<double(vrijemeKraj - vrijemePocetak)/CLOCKS_PER_SEC<<" sekundi."<<endl;

    return duzinaPuta;
}

/* Jedina razlika u odnosu na spori algoritam je sto se koriste disjunktni skupovi (implementirani na ideji stabala)
   za provjeru da li dodavanje grane pravi ciklus (ako se krajnji cvorovi te grane nalaze u istom skupu nastaje ciklus,
   u suprotnom ne nastaje). Takodjer, grana se ne dodaje na put prije ove provjere, pa nema potrebe za njenim eventualnim brisanjem.
*/

long long int Graf::TSP_brzoStablo() {

    clock_t vrijemePocetak((clock()));

    vector<list<int>> put(n);
    priority_queue<Grana, vector<Grana>, komparatorGrana> grane;
    napraviHeapGrana(grane);
    DisjunktniSkupStablo stabla(n);

    int brojDodatihGrana(0);

    while(brojDodatihGrana != n - 1) {
        Grana najmanja = grane.top();
        grane.pop();
        if(stabla.Nadji(najmanja.pocetni) != stabla.Nadji(najmanja.krajnji)
           && put[najmanja.pocetni].size() < 2 && put[najmanja.krajnji].size() < 2) {

            put[najmanja.pocetni].push_back(najmanja.krajnji);
            put[najmanja.krajnji].push_back(najmanja.pocetni);
            stabla.Unija(najmanja.pocetni, najmanja.krajnji);
            brojDodatihGrana++;
        }
    }

    int prvi(-1), zadnji(-1);

    for(int i = 0 ; i < n ; i++)
        if(put[i].size() < 2){
            if(prvi == -1)
                prvi = i;
            else {
                zadnji = i;
                break;
            }
        }

    put[prvi].push_back(zadnji);
    put[zadnji].push_back(prvi);

    long long int duzinaPuta(izracunajDuzinuPuta(put));

    clock_t vrijemeKraj((clock()));
    cout<<"Algoritam je zavrsio za "<<double(vrijemeKraj - vrijemePocetak)/CLOCKS_PER_SEC<<" sekundi."<<endl;

    return duzinaPuta;

}



