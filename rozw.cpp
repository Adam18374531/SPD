#include "SPD1.h"

rozwiazanie::rozwiazanie(){}

void rozwiazanie::show(){
	for(int i=0;i<rozw.size();i++){
		std::cout<<rozw.at(i)<<", ";
	}
	std::cout<<std::endl;
	std::cout<<"kryterium: "<<kryterium<<std::endl;
}

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

    else /*error*/
	return zadaniaWProblemie.at(ix);
}

void problem::removeZadanie(std::vector<zadanie> &p, int ix){
    p.erase(p.begin() + ix);
}

rozwiazanie problem::rozwiaz() {
    rozwiazanie r;
    /* 
    kolejka priorytetowa
    zrob kopiec rozwiazan: permutacji liczb od 0 do getLiczbaZadan()
     * posortuj po kryterium
     * zwroc rozwiazanie o max kryterium (glowe kopca?)
     * */
     return r;
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

//t_na_maszynie: r + p, t_end: t_na_maszynie + q
int rozwiazanie::countCzasWykonania(std::vector<zadanie> p){
    int t_na_maszynie = 0, t_end = 0;
    int ix_badanego_zadania;
    for(int i=0;i<p.size();i++){
        ix_badanego_zadania = getRozwiazanie().at(i);
	zadanie badane_zad = p.at( ix_badanego_zadania );

        //check if there is wait time till r
        if(t_na_maszynie < badane_zad.getTerminDostepnosci())
            t_na_maszynie = badane_zad.getTerminDostepnosci();

        //add p value
        t_na_maszynie += badane_zad.getCzasWykonania();
        
        //update q if new is longer
        if(t_end < t_na_maszynie + badane_zad.getCzasStygniecia())
            t_end = t_na_maszynie + badane_zad.getCzasStygniecia();
    }
    setKryterium(t_end);
    return t_end;
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
