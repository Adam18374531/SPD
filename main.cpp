#include <iostream>
#include <chrono>
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
    if(wczytywanie("schrage/SCHRAGE2.DAT", p))
        testWczytywanie(p);
    rozwiazanie rozw;

    std::cout<<"Sort r_j: "<<std::endl;
    auto start = std::chrono::steady_clock::now();
    rozw.r_rosnaco(p);
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> elapsed = stop - start;
    std::cout << "Kryterium: "<< rozw.getKryterium() << std::endl;
    std::cout << "Czas w mikrosekundach: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

    std::cout<<"\nSort q_j: "<<std::endl;
    start = std::chrono::steady_clock::now();
    rozw.q_malejaco(p);
    rozw.countCzasWykonania(p.getzadaniaWProblemie());
    stop = std::chrono::steady_clock::now();
    elapsed = stop - start;
    std::cout << "Kryterium: "<< rozw.getKryterium() << std::endl;
    std::cout << "Czas w mikrosekundach: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

    std::cout<<"\nAlgorytm wlasny: "<<std::endl;
    start = std::chrono::steady_clock::now();
    rozw.wlasnyAlgorytm(p);
    stop = std::chrono::steady_clock::now();
    elapsed = stop - start;
    rozw.show();
    std::cout << "Czas w mikrosekundach: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

    if(p.getLiczbaZadan() < 12){
	    std::cout<<"\nBrute force: "<<std::endl;
	    start = std::chrono::steady_clock::now();
	    rozw.przegladZupelny(p.getzadaniaWProblemie());
	    stop = std::chrono::steady_clock::now();
	    elapsed = stop - start;
	    rozw.show();
	    std::cout << "Czas w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;
    }

    /*
    std::cout<<"\nSchrage: "<<std::endl;
    start = std::chrono::steady_clock::now();
    rozw.rozwSchrage(p);
    stop = std::chrono::steady_clock::now();
    elapsed = stop - start;
    rozw.show();
    std::cout << "Czas w mikrosekundach: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
    */

    return 0;
}
