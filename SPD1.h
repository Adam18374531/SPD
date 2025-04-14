#ifndef SPD1_H
#define SPD1_H

#include <vector>
#include <algorithm>
#include <queue> 
#include <iostream>
#include <climits>


class zadanie{
private:
    //p - czas wykonania
    //r - termin dostepnosci
    //q - czas stygniecia
    int p,r,q;

public:
    zadanie(int wyk, int termin, int stygniecie) : p(wyk), r(termin), q(stygniecie) {}
    const int getCzasStygniecia()const{return q;};
    const int getTerminDostepnosci()const{return r;};
    const int getCzasWykonania()const{return p;};

    //operator porównania
    bool operator==(const zadanie &z) const {
        return (p == z.p) && (r == z.r) && (q == z.q);
    }
};



class problem{
private:
    std::vector<zadanie> zadaniaWProblemie; //zbior zadan w problemie
    int poczatkowaliczbaZadan;
public:
    problem();
    const int getLiczbaZadan() const { return zadaniaWProblemie.size(); };
    const bool isValid() const { return zadaniaWProblemie.empty(); };//czy vector niepusty
    void addZadanie(zadanie j) { zadaniaWProblemie.push_back(j); };
    const int getIx(zadanie j);
    const zadanie getZadanie(int ix);
    void removeZadanie( int ix);
    const std::vector<zadanie> getzadaniaWProblemie() const {return zadaniaWProblemie;};
    void setPoczatkowaLiczbaZadan(int lZadan){poczatkowaliczbaZadan = lZadan;};
    const int getPoczatkowaLiczbaZadan(){ return poczatkowaliczbaZadan; };
    void sort_r();                  //Sortowanie rosnace po r
    void sort_q();                  //Sortowanie rosnace po q
//    rozwiazanie rozwiaz();


};
class rozwiazanie{
private:
    std::vector<int> rozw; //kolejnosc indeksow zadan w problemie
    int kryterium; //max czas wykonywania+stygniecia dotychczas znaleziony

public:
    rozwiazanie();
    const bool isValid() { return rozw.empty(); }; //czy vector niepusty
    std::vector<int> getRozwiazanie() {return rozw; };
    const int getKryterium() {return kryterium;};
    void setRozwiazanie(std::vector<int> r) { rozw = r; };
    void addIxZadania(int ix) { rozw.push_back(ix); };
    void setKryterium(int czas) { kryterium = czas;};
    void addToKryterium(int czas){kryterium += czas;}
    bool isLongerThanKryterium(int czas) { return czas>getKryterium();};
    int countKryterium(std::vector<zadanie> p);
    int countCzasWykonania(std::vector<zadanie> p);
    void przegladZupelny(std::vector<zadanie> p);
    void wlasnyAlgorytm(problem p);
    void show();
    void rozwSchrage(problem p);
};
#endif