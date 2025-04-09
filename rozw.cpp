#include "SPD1.h"

rozwiazanie::rozwiazanie(){}

problem::problem() {

}

const int problem::getIx(zadanie j){
    for(int i=0; i<getLiczbaZadan();i++){
        if(j==zadaniaWProblemie[i]) return i;
    }
    return -1;
}

const zadanie problem::getZadanie(int ix) {
    if(ix<zadaniaWProblemie.size())
        return zadaniaWProblemie.at(ix);

    else /*error*/;
}

void problem::removeZadanie(std::vector<zadanie> &p, int ix){
    p.erase(p.begin() + ix);
}

rozwiazanie problem::rozwiaz() {
    /* 
    kolejka priorytetowa
    zrob kopiec rozwiazan: permutacji liczb od 0 do getLiczbaZadan()
     * posortuj po kryterium
     * zwroc rozwiazanie o max kryterium (glowe kopca?)
     * */
}

/*Algorytm Schrage bez przerwan*/

int findMinR_Ix(std::vector<zadanie> p){
    int minRIx = 0;
    for(int i=1; i<p.size();i++){
        if(p.at( i ).getTerminDostepnosci() < p.at( minRIx ).getTerminDostepnosci())
            minRIx = i;
            //dla tych samych r wez wieksze q
        else if(p.at( i ).getTerminDostepnosci() == p.at( minRIx ).getTerminDostepnosci()){
            if(p.at( i ).getCzasStygniecia() > p.at( minRIx ).getCzasStygniecia())
                minRIx = i;
        }
    }
    return minRIx;
}

//czas0: r + p, czas_end: czas0 + q
int rozwiazanie::countCzasWykonania(std::vector<zadanie> p){
    int czas0 = 0;
    int czas_end=0;
    int ix_badanego_zadania;
    zadanie badane_zad;
    for(int i=0;i<p.size();i++){
        ix_badanego_zadania = getRozwiazanie().at(i);
        badane_zad = p.at( ix_badanego_zadania );
        //update r if smaller
        if(czas0 < badane_zad.getTerminDostepnosci())
            czas0 = badane_zad.getTerminDostepnosci();

        //add p value
        czas0 += badane_zad.getCzasWykonania();
        
        //update q if smaller
        if(czas_end < czas0 + badane_zad.getCzasStygniecia())
            czas_end = czas0 + badane_zad.getCzasStygniecia();
    }
    setKryterium(czas_end);
    return czas_end;
}

rozwiazanie problem::rozwSchrage(){
    std::vector<zadanie> p = getProblem();
    std::vector<int> ixs;
    ixs.reserve(p.size());
    
    int dodawanyIx;
    
    while(!p.empty()){
        dodawanyIx = findMinR_Ix(p);
        ixs.push_back( dodawanyIx );
        removeZadanie(p, dodawanyIx);
    }
    
    rozwiazanie r_schrage;
    r_schrage.setRozwiazanie(ixs);
    r_schrage.countCzasWykonania(getProblem());
    return r_schrage;
}
