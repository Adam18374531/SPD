#include <iostream>
#include "wczytywanie.h"


void testWczytywanie(problem &p){
    std::cout<<p.getLiczbaZadan()<<std::endl;

    for(int i = 0;i<p.getLiczbaZadan();i++ )
    {
        zadanie z = p.getZadanie(i);
        std::cout<<"zad "<<i<<": "<<z.getTerminDostepnosci()<<" "<<z.getCzasWykonania()<<" "<<z.getCzasStygniecia()<<std::endl;

    }
    std::cout<<std::endl;
}

int main() {
    problem p;
    if(wczytywanie("schrage/SCHRAGE1.DAT", p))
        testWczytywanie(p);
    rozwiazanie rozw_wl, rozw_bf;

    rozw_wl.wlasnyAlgorytm(p);
    std::cout<<"Algorytm wlasny: "<<std::endl;
    rozw_wl.show();

    rozw_bf.przegladZupelny(p.getzadaniaWProblemie());
    std::cout<<"\nBrute force: "<<std::endl;
    rozw_bf.show();

    /*rozw_sch.rozwSchrage(p);
    std::cout<<"\nSchrage: "<<std::endl;
    r_sch.show();
    */

    return 0;
}
