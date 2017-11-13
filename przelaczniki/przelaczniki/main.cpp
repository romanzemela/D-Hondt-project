//
//  main.cpp
//  przelaczniki
//
//  Created by Mateusz Piwowarski on 13.11.2017.
//  Copyright © 2017 Penta Co. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

bool odczytajargumenty(int ile , char ** argumenty , string & szInput , string & szOutput);

int main(int ile, char ** argumenty)
{
    string nazwa_pliku_wejscia;
    string nazwa_pliku_wyjsca;
    
    cout << odczytajargumenty(ile, argumenty, nazwa_pliku_wejscia, nazwa_pliku_wyjsca) << endl;
    cout << nazwa_pliku_wyjsca << endl;
    cout << nazwa_pliku_wejscia << endl;
    
    return 0;
}
bool odczytajargumenty(int ile , char ** argumenty , string & szInput , string & szOutput)
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
