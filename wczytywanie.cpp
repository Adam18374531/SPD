#include "wczytywanie.h"
#include "SPD1.h"

bool wczytywanie(const std::string & nazwaPliku, problem &prob)
{

    std::ifstream plik(nazwaPliku);


    if(!plik) {
        std::cout << "Nieprawidlowy plik" << std::endl;
        std::cout << "Aktualny katalog: " << system("cd") << std::endl;
        return 0;
    }
    int lZadan;
    plik >> lZadan;
    prob.setPoczatkowaLiczbaZadan(lZadan);


    int r,p,q;
    for(int i = 0; i<prob.getPoczatkowaLiczbaZadan();i++)
    {
        if(plik >> r >>p >>q) {
            zadanie zad(p,r,q);
            prob.addZadanie(zad);
        }

    }

    plik.close();
    return 1;

}
