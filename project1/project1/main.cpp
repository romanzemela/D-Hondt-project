//  Created by Mateusz Piwowarski on 13.11.2017.
//  Copyright © 2017 Penta Co. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//funkcje:

float nowa_wartosc(unsigned int glosy, unsigned int mandaty)
{
    return (glosy) / (mandaty + 1);
};

void wyzerowanie_mandatow(unsigned int mandaty[ ], unsigned int iloscpartii)
{
    for (int i = 0; i < iloscpartii; i++)
        mandaty[i] = 0;
};

void wartosci_z_konsoli(unsigned int &iloscpartii, unsigned int &iloscmandatow, unsigned int glosy[ ])
{
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

bool odczytaj_argumenty(int ile , char ** argumenty , string & szInput , string & szOutput)
{
    const string ETYKIETAINPUT ("-i");
    const string ETYKIETAOUTPUT ("-o");
    const int FLAGAINPUT = 1;
    const int FLAGAOUTPUT = FLAGAINPUT << 1;
    const int POPRAWNYWYNIK = FLAGAINPUT | FLAGAOUTPUT;
    int wynik = 0;
    
    for(int i = 1; i < ile - 1; i++)
    {
        string arg (argumenty[i]);
        if (arg == ETYKIETAINPUT)
        {
            szInput = argumenty[i + 1];
            wynik |= FLAGAINPUT;
            
        }
        if (arg == ETYKIETAOUTPUT)
        {
            szOutput = argumenty [i + 1];
            wynik |= FLAGAOUTPUT;
            
        }
    }
    
    if( wynik == POPRAWNYWYNIK)
        return true;
    else
        return false;
}

void wyswietl_wyniki(unsigned int iloscpartii,unsigned int mandaty[ ])
{
    for (int i = 0; i < iloscpartii; i++)
        cout << mandaty[i] << endl;
}

// main:

int main(int ile, char ** argumenty)
{
    const int MAX = 100;  // maksymalna ilosc partii
    unsigned int mandaty[MAX];
    unsigned int glosy[MAX];
    double baza_glosow[MAX];
    double maks;
    unsigned int iloscpartii = 0;
    unsigned int iloscmandatow;
    unsigned int miejscemax = 0;

    string nazwa_pliku_wejscia;
    string nazwa_pliku_wyjsca;
    
    odczytaj_argumenty(ile, argumenty, nazwa_pliku_wejscia, nazwa_pliku_wyjsca);
    
    ifstream plikwejscia;
    plikwejscia.open("../dat/" + nazwa_pliku_wejscia + ".txt", ios::in);
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
            cout << " Zle zapisane dane w pliku tekstowym " << endl;
        
        plikwejscia.close();
    }
    else
    {
        cout << " Nie podano lub nie znaleziono pliku wejsciowego" << endl;
        wartosci_z_konsoli(iloscpartii, iloscmandatow, glosy);
    }
    wyzerowanie_mandatow( mandaty, iloscpartii);
    
    // podzial mandatów metodą d'Hondta
    
    for (int i = 0; i < iloscpartii; i++)
        baza_glosow[i] = glosy[i];
    
    for (int i = 0 ; i < iloscmandatow; i++)
    {
        // szukanie najwiekszej wartosci
        maks = -1;
        for (int j = 0 ; j< iloscpartii; j++)
            if (maks < baza_glosow[j])
            {
                maks = baza_glosow[j];
                miejscemax = j;
            }
        
        // partia z najwieksza wartoscia dostaje mandat
        mandaty[miejscemax]++;
        baza_glosow[miejscemax] = nowa_wartosc(glosy[miejscemax], mandaty[miejscemax]);
    }
    
    
    fstream plikwyjscia;
    plikwyjscia.open("../dat/" + nazwa_pliku_wyjsca + ".txt",ios::in);
    if( plikwyjscia.good())
    {
        plikwyjscia.close();
        plikwyjscia.open("../dat/" + nazwa_pliku_wyjsca + ".txt",ios::out);
        for (int i = 0; i < iloscpartii; i++)
        {
            plikwyjscia << mandaty[i] << endl;
        }
        
    } else {
        plikwyjscia.close();
        // wyswietlanie wynikow
        wyswietl_wyniki(iloscpartii, mandaty);
    }
    
    return 0;
}
