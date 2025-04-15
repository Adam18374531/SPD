#include "SPD1.h"

rozwiazanie::rozwiazanie(){}

problem::problem(){}

void rozwiazanie::show(){
    for(int i=0;i<rozw.size();i++){
        std::cout<<rozw.at(i)<<", ";
    }
    std::cout<<std::endl;
    std::cout<<"kryterium: "<<kryterium<<std::endl;
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

void problem::removeZadanie(int ix){
    zadaniaWProblemie.erase(zadaniaWProblemie.begin() + ix);

}

//czas0: r + p, czas_end: czas0 + q
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

void problem::sort_r() {
    std::sort(zadaniaWProblemie.begin(), zadaniaWProblemie.end(), [](const zadanie& a, const zadanie& b) {
        return a.getTerminDostepnosci() < b.getTerminDostepnosci();
    });
}

void problem::sort_q() {
    std::sort(zadaniaWProblemie.begin(), zadaniaWProblemie.end(), [](const zadanie& a, const zadanie& b) {
        return a.getCzasStygniecia() > b.getCzasStygniecia();
    });
}

#include "SPD1.h"

void rozwiazanie::r_rosnaco(problem p){
    p.sort_r();
    int czas = 0;
    bool znalezione;
    int l_zadan = p.getzadaniaWProblemie().size();

    std::vector<int> kolejnosc;
    std::vector<bool> wykonane(l_zadan, false);

    while( kolejnosc.size() < l_zadan ) {
        znalezione = false;
        for (int i = 0; i < l_zadan; i++) {
            if (!wykonane[i] && czas >= p.getZadanie(i).getTerminDostepnosci() ) {
                kolejnosc.push_back(i);
                czas += p.getZadanie(i).getCzasWykonania();
                wykonane[i] = true;
                znalezione = true;
                break;
            }
        }
        if (!znalezione) {
            // jeĹ›li nie ma dostÄ™pnych zadaĹ„, zwiÄ™ksz czas
            czas++;
        }
    }
    
    setRozwiazanie(kolejnosc);
    countCzasWykonania(p.getzadaniaWProblemie());
}

void rozwiazanie::q_malejaco(problem p){
    p.sort_q();
    countCzasWykonania(p.getzadaniaWProblemie());
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

//nie dziala
void rozwiazanie::rozwSchrage(problem p){

    std::vector<int> ixs;
    ixs.reserve(p.getzadaniaWProblemie().size());

    int dodawanyIx;

    while(!p.getzadaniaWProblemie().empty()){
        dodawanyIx = findMinR_Ix(p.getzadaniaWProblemie());
        ixs.push_back( dodawanyIx );

        p.removeZadanie(dodawanyIx);
    }

    setRozwiazanie(ixs);
    countCzasWykonania(p.getzadaniaWProblemie());

}

void rozwiazanie::przegladZupelny(std::vector<zadanie> p) {
    int n = p.size();
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++)
        perm[i] = i;
    std::vector<int> optimum(n);
	
    int minimalnyCmax = INT_MAX;

    do {
        setRozwiazanie(perm);
        int cmax = countCzasWykonania(p);
	if(cmax < minimalnyCmax){
		minimalnyCmax = cmax;
		optimum = perm;
	}	
    } while (std::next_permutation(perm.begin(), perm.end()));

    setKryterium(minimalnyCmax);
    setRozwiazanie(optimum);
}

void testWczytywanie2(problem &p){
    std::cout<<p.getLiczbaZadan()<<std::endl;

    for(int i = 0;i<p.getLiczbaZadan();i++) {
        zadanie z = p.getZadanie(i);
        std::cout<<z.getTerminDostepnosci()<<" "<<z.getCzasWykonania()<<" "<<z.getCzasStygniecia()<<std::endl;
    }
    std::cout<<std::endl;
}

/*
 * Algorytm sortuje najpierw malejaco po czasie stygniecia
 * Jeżeli dostepny jest dane zadanie z najwiekszym czasem stygniecia to jest ono wykonywane
 * W przeciwnym razie jest brany nastepny element
 */
void rozwiazanie::wlasnyAlgorytm(problem p) {
    p.sort_q();
    int czas = 0;
    bool znalezione;
    int l_zadan = p.getzadaniaWProblemie().size();

    std::vector<int> kolejnosc;
    std::vector<bool> wykonane(l_zadan, false);

    while( kolejnosc.size() < l_zadan ) {
        znalezione = false;
        for (int i = 0; i < l_zadan; i++) {
            if (!wykonane[i] && czas >= p.getZadanie(i).getTerminDostepnosci() ) {
                kolejnosc.push_back(i);
                czas += p.getZadanie(i).getCzasWykonania();
                wykonane[i] = true;
                znalezione = true;
                break;
            }
        }
        if (!znalezione) {
            // jeśli nie ma dostępnych zadań, zwiększ czas
            czas++;
        }
    }
    
    setRozwiazanie(kolejnosc);
    countCzasWykonania(p.getzadaniaWProblemie());

}
