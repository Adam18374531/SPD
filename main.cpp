#include <iostream>
#include "wczytywanie.h"


void testWczytywanie(problem &p){
    std::cout<<p.getLiczbaZadan()<<std::endl;

    for(int i = 0;i<p.getLiczbaZadan();i++ )
    {
        zadanie z = p.getZadanie(i);
        std::cout<<z.getTerminDostepnosci()<<" "<<z.getCzasWykonania()<<" "<<z.getCzasStygniecia()<<std::endl;

    }
    std::cout<<std::endl;
}

int main() {
    problem p;
    if(wczytywanie("SCHRAGE2.DAT", p))
        testWczytywanie(p);
    rozwiazanie rozw;

//    p.removeZadanie(0);
//    rozw.wlasnyAlgorytm(p);
//    std::cout<<"Rozwiazanie Cmax: "<<rozw.getKryterium()<<std::endl;
//
//    rozw.przegladZupelny(p.getProblem());
    rozw.rozwSchrage(p);
//    rozw.countCzasWykonania(p.getProblem());
//    p.sort_r();
//    p.sort_q();
//    testWczytywanie(p);
    std::cout<<"Rozwiazanie Cmax: "<<rozw.getKryterium()<<std::endl;
    return 0;
}
