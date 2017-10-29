#include <iostream>

using namespace std;

float nowawartosc(int glosy, int mandaty)
{
    return (glosy) / (mandaty + 1);
}

int main()
{
    int mandaty[100];
    int glosy[100];
    float calcTab[100];
    float maks;
    int iloscpartii;
    int iloscmandatow;
    int miejscemax;

    //get all data
    cout << "Podaj liczbe partii (max. 100)" << endl;
    cin >> iloscpartii;

    cout << "Podaj liczbe mandatow" << endl;
    cin >> iloscmandatow;

    for (int i = 0; i < iloscpartii; i++)
    {
        cout << "Podaj liczbe glosow na partie " << i+1 << endl;
        cin >> glosy[i];
    }

    // wyzerowanie mandat—w dla kaýdej partii
    for (int i = 0; i < iloscpartii; i++)
    {
        mandaty[i] = 0;
    }

    // podzia¸ mandat—w metodˆ d'Hondta

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

    // wyswietlanie wynikow
    for (int i = 0; i < iloscpartii; i++)
    {
        cout << "Partia " << i + 1  << " ma " << mandaty[i] << " mandatow" << endl;
    }

    return 0;
}
