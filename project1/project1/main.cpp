//  Created by Mateusz Piwowarski on 13.11.2017.
//  Copyright © 2017 Penta Co. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Pomoc()
{
    cout
    << endl << " WYZNACZANIE ILOSCI MANDATOW UZYSKANYCH W WYBORACH PARLAMENTARNYCH ( METODA D'HONDT)" << endl
    << endl << " Jezeli chcemy wykorzystac dane z pliku:" << endl
    << endl << "- Pierwsza wartoscia wymagana jest ilosc mandatow."
    << endl << "- Nastepne wartosci są glosami na poszczegolne partie. "
    << endl << "- Wszystkie wartosci powinny byc oddzielone spacja."
    << endl << "- Wszystkie wartosci powinny byc liczbami naturalnymi."
    << endl << "- Ilosc partii nie powinna przekraczac 100." << endl
    << endl << " Jezeli chcemy wykorzystac dane z wejscia standardowego:" << endl
    << endl << "- Wartosci podawane powinny byc liczbami naturalnymi."
    << endl << "- Ilosc partii nie powinna przekraczać 100." << endl;
}

void Poprawnosc_danych(bool & poprawne_dane,unsigned int & iloscpartii)
{
    if(!cin || iloscpartii > 100)
    {
        cout << endl << " Wpisales bledne dane." << endl;
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
    
    for(int i = 1; i < ile; i++)
    {
        string arg (argumenty[i]);
        
        if (arg == ETYKIETAHELP)
            Pomoc();
        
        if (arg == ETYKIETAINPUT)
            szInput = argumenty[i + 1];
        
        if (arg == ETYKIETAOUTPUT)
            szOutput = argumenty [i + 1];
        
    }
    
}



bool Wartosci_z_konsoli(unsigned int &iloscpartii, unsigned int &iloscmandatow, unsigned int glosy[ ])
{
    bool poprawne_dane = true;
    
    cout << " Podaj liczbe partii (max. 100)." << endl;
    cin >> iloscpartii;
    
    Poprawnosc_danych(poprawne_dane, iloscpartii);
    
    if(poprawne_dane)
    {
        cout << " Podaj liczbe mandatow." << endl;
        cin >> iloscmandatow;
        Poprawnosc_danych(poprawne_dane, iloscpartii);
    }
    
    
    for (int i = 0; i < iloscpartii; i++)
    {
        if(poprawne_dane)
        {
            cout << " Podaj liczbe glosow na partie." << i+1 << endl;
            cin >> glosy[i];
            Poprawnosc_danych(poprawne_dane, iloscpartii);
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
            cout << " Zle zapisane dane w pliku tekstowym." << endl;
        }
        plikwejscia.close();
    }
    else
    {
        cout << endl << " Nie podano lub nie znaleziono pliku wejsciowego." << endl;
        if(!Wartosci_z_konsoli(iloscpartii, iloscmandatow, glosy))
            poprawne_dane = false;
    }
    return poprawne_dane;
}

double Nowa_wartosc(unsigned int glosy, unsigned int mandaty)
{
    return (glosy) / (mandaty + 1);
}


void Wynik_konsola(unsigned int iloscpartii,unsigned int mandaty[ ])
{
    cout << " Podzial mandatow:" << endl;
    for (int i = 0; i < iloscpartii; i++)
        cout << "partia" << i + 1 << ": " << mandaty[i] << endl;
}

void Wynik(string wyjscie, unsigned int iloscpartii, unsigned int mandaty[ ])
{
    fstream plikwyjscia;
    if(wyjscie.empty())
        Wynik_konsola(iloscpartii, mandaty);
    else
    {
        plikwyjscia.open("../dat/" + wyjscie + ".txt",ios::out);
        for (int i = 0; i < iloscpartii; i++)
        {
            plikwyjscia << mandaty[i] << endl;
        }
        plikwyjscia.close();
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
            double maks = -1;
            for (int j = 0 ; j< iloscpartii; j++)
                if (maks < baza_glosow[j])
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
