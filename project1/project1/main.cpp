
//  Project 1

#include <iostream>
#include <fstream>
    
    using namespace std;

    float nowawartosc(int glosy, int mandaty); // generowanie nowej wartosci po uzyskaniu mandatu
    void wyzerowaniemandatow(int T[ ],int N); // wyzerowanie mandatów dla każdej partii

    int main(int argc, const char * argv[])
    {
        int mandaty[100];
        int glosy[100];
        float calcTab[100];
        float maks;
        int iloscpartii = 0;
        int iloscmandatow;
        int miejscemax = 0;
        const int MAX = 100;  // maksymalna ilosc partii
        
        ifstream plikwejscia;
        plikwejscia.open("test.txt",ios::in);
        if( plikwejscia.good())
        {
            
            plikwejscia >> iloscmandatow; // pobieramy z pliku ilosc mandatow
            
            // pobieranie z pliku ilosc glosow na kazda partie
            for(int i = 0; i < MAX && !plikwejscia.eof(); i++)
            {
                plikwejscia >> glosy[i];
                iloscpartii ++;
            }
            
            if( plikwejscia.fail())
            {
                cout << "Zle zapisane dane w pliku tekstowym " << endl;
                cout << "Sprawdz czy: " << endl;
                cout << "- Kazdy parametr jest liczba naturalna" << endl;
                cout << "- Wartosci sa oddzielone spacjami" << endl;
                cout << "- Na koncu nie ma znaku bialego" << endl;
                cout << "- Dane sa podane tylko w pierwszej linii" << endl;
            }
            plikwejscia.close();
        }else{
            
            // pobranie wartosci z konsoli gdy nie ma mozliwosci pobrania z pliku
            cout << "Podaj liczbe partii (max. 100)" << endl;
            cin >> iloscpartii;
            
            cout << "Podaj liczbe mandatow" << endl;
            cin >> iloscmandatow;
            
            for (int i = 0; i < iloscpartii; i++)
            {
                cout << "Podaj liczbe glosow na partie " << i+1 << endl;
                cin >> glosy[i];
            }
            if(!cin)
            {
                cout << "wpisales bledne dane";
            }
            
        }

        wyzerowaniemandatow( mandaty, iloscpartii);
        
        // podzial mandatów metodą d'Hondta
        
        for (int i = 0; i < iloscpartii; i++)
        {
            calcTab[i] = glosy[i];
        }
        for (int i = 0 ; i < iloscmandatow; i++)
        {
            // szukanie najwiekszej wartosci
            maks = -1;
            for (int j = 0 ; j< iloscpartii; j++)
            {
                if (maks < calcTab[j])
                {
                    maks = calcTab[j];
                    miejscemax = j;
                }
            }
            
            // partia z najwieksza wartoscia dostaje mandat
            mandaty[miejscemax]++;
            calcTab[miejscemax] = nowawartosc(glosy[miejscemax], mandaty[miejscemax]);
        }
        
        
        fstream plikwyjscia;
        plikwyjscia.open("wynik.txt",ios::in);
        if( plikwyjscia.good())
        {
            plikwyjscia.close();
            plikwyjscia.open("wynik.txt",ios::out);
            for (int i = 0; i < iloscpartii; i++)
            {
                plikwyjscia << mandaty[i] << endl;
            }
            
        } else {
            plikwyjscia.close();
            // wyswietlanie wynikow
            for (int i = 0; i < iloscpartii; i++)
            {
                cout << mandaty[i] << endl;
            }
        }
        
        return 0;
    }

// ciala funkcji zadeklarowanych na poczatku programu

float nowawartosc(int glosy, int mandaty)
{
    return (glosy) / (mandaty + 1);
};

void wyzerowaniemandatow(int T[ ],int N)
{
    for (int i = 0; i < N; i++)
        T[i] = 0;
};


