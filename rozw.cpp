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

void problem::removeZadanie( int ix){
    zadaniaWProblemie.erase(zadaniaWProblemie.begin() + ix);

}

//rozwiazanie problem::rozwiaz() {
//    /*
//    kolejka priorytetowa
//    zrob kopiec rozwiazan: permutacji liczb od 0 do getLiczbaZadan()
//     * posortuj po kryterium
//     * zwroc rozwiazanie o max kryterium (glowe kopca?)
//     * */
//}

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
//    zadanie badane_zad;
    for(int i=0;i<p.size();i++){
        ix_badanego_zadania = getRozwiazanie().at(i);
        zadanie badane_zad = p.at( ix_badanego_zadania );
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


//nie dziala
void rozwiazanie::rozwSchrage(problem p){

    std::vector<int> ixs;
    ixs.reserve(p.getProblem().size());

    int dodawanyIx;

    while(!p.getProblem().empty()){
        dodawanyIx = findMinR_Ix(p.getProblem());
        ixs.push_back( dodawanyIx );
        p.removeZadanie(dodawanyIx);
    }


    setRozwiazanie(ixs);
    setKryterium(countCzasWykonania(p.getProblem()));

}

void rozwiazanie::przegladZupelny(std::vector<zadanie> p) {
    int n = p.size();
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    int minimalnyCmax = INT_MAX;

    bool done = false;
    do {
        setRozwiazanie(perm);
        int cmax = countCzasWykonania(p);
        minimalnyCmax = std::min(minimalnyCmax, cmax);
        if(minimalnyCmax==9 and !done) {
            for (int k = 0; k < perm.size(); k++)
                std::cout << perm.at(k) << std::endl;
            done = true;
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    setKryterium(minimalnyCmax);
}



void testWczytywanie2(problem &p){
    std::cout<<p.getLiczbaZadan()<<std::endl;

    for(int i = 0;i<p.getLiczbaZadan();i++ )
    {
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
    testWczytywanie2(p);
    int czas = 0;
    int i =0;
    bool znalezione=false;
//    int minimalnyCzas = 0;
    std::vector<int> kolejnosc;
    std::vector<bool> wykonane(p.getProblem().size(), false);
//    std::cout<<"rozmiar: "<<kolejnosc.size()<<std::endl;
    while(! (kolejnosc.size()>=p.getProblem().size())) {
        i = 0;
        znalezione = false;
        for (int i = 0; i < p.getProblem().size(); i++) {
            if (!wykonane[i] && p.getZadanie(i).getTerminDostepnosci() <= czas) {
                kolejnosc.push_back(i);
                czas += p.getZadanie(i).getCzasWykonania();
                wykonane[i] = true;
                znalezione = true;
                std::cout << "Dodano zadanie: " << i << ", czas: " << czas << std::endl;
                break;
            }
        }
        if (!znalezione) {
            // jeśli nie ma dostępnych zadań, zwiększ czas
            czas++;
        }
    }
    std::cout<<std::endl;
    for(int a = 0; a<kolejnosc.size();a++)
        std::cout<<kolejnosc.at(a)<<std::endl;
    setRozwiazanie(kolejnosc);
    setKryterium(countCzasWykonania(p.getProblem()));

}
