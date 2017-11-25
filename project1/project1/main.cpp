//  Created by Mateusz Piwowarski on 13.11.2017.
//  Copyright © 2017 Penta Co. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Pomoc()
{
    cout << endl << " WYZNACZANIE ILOŚCI MANDATÓW UZYSKANYCH W WYBORACH PARLAMENTARNYCH ( METODA D'HONDT)" << endl << " Jeżeli chcemy wykorzystać dane z pliku:" << endl << endl << " Pierwsza wartoscią wymaganą jest ilość mandatów." << endl << " Następne wartości są głosami na poszczególne partie. " << endl << " Wszystkie wartosci powinny byc oddzielone spacją." << endl << " Wszystkie wartosci powinny byc liczbami naturalnymi." << endl << " Ilosc partii nie powinna przekraczać 100." << endl << " Jeżeli chcemy wykorzystać dane z wejścia standardowego:" << endl << endl << " Wartosci podawane powinny byc liczbami naturalnymi.";
}

void Poprawnosc_danych(bool & poprawne_dane)
{
    if(!cin)
    {
        cout << endl << " Wpisales bledne dane" << endl;
        poprawne_dane = false;
    }
}

void Wyzerowanie_mandatow(unsigned int mandaty[ ], unsigned int iloscpartii)
{
    for (int i = 0; i < iloscpartii; i++)
        mandaty[i] = 0;
}

void Odczytaj_argumenty(int ile , char ** argumenty , string & szInput , string & szOutput)
{
    const string ETYKIETAINPUT ("-i");
    const string ETYKIETAOUTPUT ("-o");
    const string ETYKIETAHELP ("-h");
    
    for(int i = 1; i < ile - 1; i++)
    {
        string arg (argumenty[i]);
        
        if (arg == ETYKIETAINPUT)
            szInput = argumenty[i + 1];
        
        if (arg == ETYKIETAOUTPUT)
            szOutput = argumenty [i + 1];
        if (arg == ETYKIETAHELP)
            Pomoc();
    }
    
}



bool Wartosci_z_konsoli(unsigned int &iloscpartii, unsigned int &iloscmandatow, unsigned int glosy[ ])
{
    bool poprawne_dane = true;
    
    cout << " Podaj liczbe partii (max. 100)" << endl;
    cin >> iloscpartii;
    
    Poprawnosc_danych(poprawne_dane);
    
    if(poprawne_dane)
    {
        cout << " Podaj liczbe mandatow" << endl;
        cin >> iloscmandatow;
        Poprawnosc_danych(poprawne_dane);
    }
    
    
    for (int i = 0; i < iloscpartii; i++)
    {
        if(poprawne_dane)
        {
            cout << " Podaj liczbe glosow na partie " << i+1 << endl;
            cin >> glosy[i];
            Poprawnosc_danych(poprawne_dane);
        }
    }
    return poprawne_dane;
}

bool Pobieranie_danych(string wejscie, unsigned int &iloscpartii, int MAX, unsigned int glosy[ ], unsigned int &iloscmandatow)
{
    bool poprawne_dane = true;
    ifstream plikwejscia;
    plikwejscia.open("../dat/" + wejscie + ".txt", ios::in);
    if( plikwejscia.good())
    {
        plikwejscia >> iloscmandatow;
        
        // pobieranie z pliku ilosc glosow na kazda partie
        for(int i = 0; i < MAX && !plikwejscia.eof(); i++)
        {
            plikwejscia >> glosy[i];
            iloscpartii ++;
        }
        
        if( plikwejscia.fail())
        {
            poprawne_dane = false;
            cout << " Zle zapisane dane w pliku tekstowym " << endl;
        }
        plikwejscia.close();
    }
    else
    {
        cout << endl << " Nie podano lub nie znaleziono pliku wejsciowego" << endl;
        if(!Wartosci_z_konsoli(iloscpartii, iloscmandatow, glosy))
            poprawne_dane = false;
    }
    return poprawne_dane;
}

float Nowa_wartosc(unsigned int glosy, unsigned int mandaty)
{
    return (glosy) / (mandaty + 1);
}


void Wyswietl_wyniki(unsigned int iloscpartii,unsigned int mandaty[ ])
{
    for (int i = 0; i < iloscpartii; i++)
        cout << mandaty[i] << endl;
}

void Wynik(string wyjscie, unsigned int iloscpartii, unsigned int mandaty[ ])
{
    fstream plikwyjscia;
    plikwyjscia.open("../dat/" + wyjscie + ".txt",ios::in);
    if( plikwyjscia.good())
    {
        plikwyjscia.close();
        plikwyjscia.open("../dat/" + wyjscie + ".txt",ios::out);
        for (int i = 0; i < iloscpartii; i++)
        {
            plikwyjscia << mandaty[i] << endl;
        }
        
    } else {
        plikwyjscia.close();
        Wyswietl_wyniki(iloscpartii, mandaty);
    }
    
}

int main(int ile, char ** argumenty)
{
    // deklaracja zmiennych:
    const int MAX = 100;  // maksymalna ilosc partii
    unsigned int mandaty[MAX];
    unsigned int glosy[MAX];
    unsigned int iloscpartii = 0;
    unsigned int iloscmandatow;

    string nazwa_pliku_wejscia;
    string nazwa_pliku_wyjsca;
    
    Odczytaj_argumenty(ile, argumenty, nazwa_pliku_wejscia, nazwa_pliku_wyjsca);
    if(Pobieranie_danych(nazwa_pliku_wejscia, iloscpartii, MAX, glosy, iloscmandatow))
    {
        Wyzerowanie_mandatow( mandaty, iloscpartii);
    
        // podzial mandatów metodą d'Hondta
        double baza_glosow[MAX];
        int miejscemax = 0;
        for (int i = 0; i < iloscpartii; i++)
            baza_glosow[i] = glosy[i];
    
        for (int i = 0 ; i < iloscmandatow; i++)
        {
            // szukanie najwiekszej wartosci
            double maks = baza_glosow[0];
            for (int j = 0 ; j< iloscpartii; j++)
                if (maks <= baza_glosow[j])
                {
                    maks = baza_glosow[j];
                    miejscemax = j;
                }
        
            // partia z najwieksza wartoscia dostaje mandat
            mandaty[miejscemax]++;
            baza_glosow[miejscemax] = Nowa_wartosc(glosy[miejscemax], mandaty[miejscemax]);
        }
    
        Wynik(nazwa_pliku_wyjsca, iloscpartii, mandaty);
        }
    return 0;
}
