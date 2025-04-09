#include <iostream>
#include "wczytywanie.h"


void testWczytywanie(problem &p){
    std::cout<<p.getLiczbaZadan()<<std::endl;

    for(int i = 0;i<p.getLiczbaZadan();i++ )
    {
        zadanie z = p.getZadanie(i);
        std::cout<<z.getTerminDostepnosci()<<" "<<z.getCzasWykonania()<<" "<<z.getCzasStygniecia()<<std::endl;

    }
}

int main() {
    problem p;
    if(wczytywanie("SCHRAGE2.DAT", p))
        testWczytywanie(p);

    return 0;
}
