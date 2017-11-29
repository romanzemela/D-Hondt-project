#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
 Pomoc:
 Funkcja wyswietlajaca instrukcje programu.
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Pomoc()
{
    cout
    << endl << " WYZNACZANIE ILOSCI MANDATOW UZYSKANYCH W WYBORACH PARLAMENTARNYCH ( METODA D'HONDT)" << endl
    << endl << " Jezeli chcemy wykorzystac dane z pliku:" << endl
    << endl << "- Pierwsza wartoscia wymagana jest ilosc mandatow."
    << endl << "- Nastepne wartosci są glosami na poszczegolne partie. "
    << endl << "- Wszystkie wartosci powinny byc oddzielone."
    << endl << "- Wszystkie wartosci powinny byc liczbami naturalnymi."
    << endl << "- Ilosc partii nie powinna przekraczac 100." << endl
    << endl << " Jezeli chcemy wykorzystac dane z wejscia standardowego:" << endl
    << endl << "- Wartosci podawane powinny byc liczbami naturalnymi."
    << endl << "- Ilosc partii nie powinna przekraczać 100." << endl;
}

/*
 Poprawnosc_danych:
 Funkcja sprawdzająca czy dane, ktore podaje uzytkownik są poprawne.
 Jezeli uzytkownik wprowadzil niepoprawne dane funkcja wyswietla komunikat " Wpisales bledne dane" oraz uruchamia funckje Pomoc() wyswietlajaca intrukcje programu.
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 poprawne_dane −− wartosc w ktorej bedzie zapisany wynik poprawnosci danych (True / False)
 iloscpartii -- ilosc partii bioraca udzial w wyborach parlamentarnych. Zostje sprawdzana czy jej liczba nie przekracza 100)
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Poprawnosc_danych(bool & poprawne_dane,const unsigned int iloscpartii)
{
    if(!cin || iloscpartii > 100)
    {
        cout << endl << " Wpisales bledne dane." << endl;
        poprawne_dane = false;
        Pomoc();
    }
}

/*
 Wyzerowanie_mandatow:
 Funkcja ustawiajaca wartosci tablicy mandatów dla kazdej partii na 0
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 mandaty -- tablica mandatow ktora zostanie wyzerowana
 iloscpartii -- ilosc partii bioracych udzial w wyborach parlamentarnych
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wyzerowanie_mandatow(unsigned int mandaty[ ], unsigned int iloscpartii)
{
    for (int i = 0; i < iloscpartii; i++)
        mandaty[i] = 0;
}

/*
 Odczytaj_argumenty:
Funkcja odczytujaca parametry wywolania programu. Sa one podane w postaci przelacznikow.
nazwa pliku wejsciowego (-i input)
nazwa pliku wyjsciowego (-o output)
wyswielenie pomocy (-h)
Przelaczniki moga byc podane w dowolnej kolejnosci .
------------------
parametry funkcji :
−−−−−−−−−−−−−−−−−−
ile −− liczba parametrow przy uruchomieniu programu
argumenty −− tablica wskaznikow na lancuchy uzytych przy uruchomienieu programu
szInput −− parametr wyjsciowy , do ktorego zostanie zapisana odczytana nazwa pliku
wejsciowego
szOutput −− parameter wyjsciowy , do ktorego zostanie zapisana odczytana nazwa pliku
wyjsciowego
------------------
autor : Mateusz Piwowarski
2017−11−27
*/

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

/*
 Wartosci_z_konsoli:
 Funkcja przypisuje dane ktore podaje uzytkownik z standardowego wejscia. Pobiera liczbe partii bioracych udzial w wyborach, liczbe wszystkich mandatow ktore zostana rozdane w wyborach oraz ilosc glosow oddanych na poszczegolne partie.
 Po pobraniu kazdej wartości uruchamia funkcje Poprawnosc_danych sprawdzajaca czy podane przez uzytkownika wartosci sa popranwe.
 poprawne_dane -- wartosc ktora przechowuje informacje czy dane podane przez uzytkownika sa poprawne.
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 glosy -- tablica w ktorej beda przechowywane liczby oddanych glosow na poszczegolne partie
 iloscpartii -- liczba partii ktora bedzie, ktora bedzie podana przez uzytkownika
 iloscmandatow -- liczba mandatow, ktora bedzie podana przez uzytkownika
 ------------------
 wartosc zwracana:
 ------------------
 true -- wartosci ktore podal uzytkownik sa poprawne
 false -- wartosci ktore podal uzytkownik sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

bool Wartosci_z_konsoli(unsigned int glosy[ ], unsigned int &iloscpartii, unsigned int &iloscmandatow)
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

/*
 Pobieranie_danych:
 Funkcja przypisuje dane z pliku lub z standardowego wejscia.
 Tworzy strumień ifstream (plikwejscia) do pliku tekstowego o nazwie wejscie ktora znajduje sie w katalogu zewnetrznym dat
 Funkcja wyswietla komunikat jezeli plik wejscia nie zostal podany w wierszu linii polecen lub pliku nie znaleziono
 Funkcja wyswietla komunikat jezeli dane w pliku wejscia sa niepoprawne
 plikwejscia -- strumien ifstream na plik tekstowy wejscie ktore znajduje sie w katalogu zewnetrzym dat
 poprawne_dane -- wartosc ktora przechowuje informacje czy dane w pliku lub dane podane przez uzytkownika sa poprawne
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 wejscie -- nazwa pliku z ktorego pobieramy dane
 MAX -- maksymalna ilosc partii
 glosy -- tablica glosow przechowujaca liczbe oddanych glosow na partie
 iloscpartii -- ilosc partii bioracych udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 ------------------
 wartosc zwracana:
 ------------------
 true -- wartosci w pliku lub ktore podal uzytkownik sa poprawne
 false -- wartosci w pliku lub ktore podal uzytkownik sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

bool Pobieranie_danych(string wejscie,const int MAX, unsigned int glosy[ ], unsigned int &iloscpartii, unsigned int &iloscmandatow)
{
    bool poprawne_dane = true;
    ifstream plikwejscia( "../dat/" + wejscie + ".txt");
    if( plikwejscia)
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
            Pomoc();
        }
        plikwejscia.close();
    }
    else
    {
        cout << endl << " Nie podano lub nie znaleziono pliku wejsciowego." << endl;
        if(!Wartosci_z_konsoli(glosy, iloscpartii, iloscmandatow))
            poprawne_dane = false;
    }
    return poprawne_dane;
}
/*
 Nowa_wartosc:
 Funkcja zwraca nowa ilosc glosow po otrzymaniu mandatu przez partie: ( ilosc glosow otrzymanych w glosowaniu / ilosc uzyskanych mandatow w danym momencie + 1)
 Wartosc zwracana jest brana pod uwage przy przydzielaniu kolejnego mandatu
 Funckja zostaje wywolywana po otrzymaniu mandatu przez partie
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 glosy -- ilosc glosow oddanych na partie
 mandaty -- ilosc mandatow uzyskanych przez partie
 ------------------
 wartosc zwracana:
 ------------------
 ilosc glosow po otrzymaniu mandatu przez partie
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

double Nowa_wartosc(unsigned int glosy, unsigned int mandaty)
{
    return (glosy) / (mandaty + 1);
}

/*
 Podzial_mandatow:
 Funkcja ktora przydziela mandaty partiom bioracych udzial w wyborach parlamentarnych
 baza_glosow -- tablica ktora na poczatku funkcji przechowuje poczatkowy stan glosow na poszczegolne partie. Wraz z kazdym przyznaniem mandatu wartosci baza_glosow ulegaja zmianie. Po przyznaniu mandatu dla partii, dana partia otrzymuje nowa wartosc glosow poprzez funkcje Nowa_wartosc
 maks -- zmienna w ktorej przechowujemy wartosc najwiekszej ilosci glosow z wszystkich partii
 miejscemax -- zmienna ktora przechowuje informacje w ktorym miejscu tablicy baza_glosow znajduje sie najwieksza ilosc glosow
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 MAX -- maksymalna ilosc partii bioracych udzial w wyborach parlamentarnych
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych
 glosy -- tablica glosow oddanych na partie bioracych udzial w wyborach parlamentarnych
 iloscpartii -- ilosc partii ktore biora udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Podzial_mandatow(const int MAX, unsigned int mandaty [ ], unsigned int glosy [ ], unsigned int iloscpartii, unsigned int iloscmandatow)
{
    double baza_glosow[MAX];
    int miejscemax = 0;
    // kopia tablicy glosow
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
}

/*
 Wynik_konsola:
 Funkcja wyswietlajace wynik przypisania mandatow na standardowe wyjscie:
 // partia (kolejno numer partii): ilosc mandatow //
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych
 iloscpartii -- ilosc partii ktore biora udzial w wyborach parlamentarnych
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wynik_konsola(unsigned int mandaty[ ], unsigned int iloscpartii)
{
    cout << " Podzial mandatow:" << endl;
    for (int i = 0; i < iloscpartii; i++)
        cout << " partia " << i + 1 << ": " << mandaty[i] << endl;
}

/*
 Wynik:
 Funkcja wyswietlajace wynik przypisania mandatow do pliku lub na standardowe wyjscie
 Jezeli string wyjscie jest pusty zostaje uruchomiona funkcja Wynik_konsola ktora wyswietli wynik wyborow na standardowe wyjscie.
 Jezeli string wyjscie zawiera nazwe pliku w ktorym chcemy zapisac wynik wyborow funkcja tworzy strumien ofstream plikwyjscia pliku tekstowego wyjscie w katalogu zewnetrznym dat
 W pliku tekstowym zostaje zapisany wynik wyborow: // partia (kolejno numer partii): ilosc mandatow //
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 wyjscie -- nazwa pliku do ktorego zostanie zapisany wynik
 iloscpartii -- ilosc partii ktore biora udzial w wyborach parlamentarnych
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych

 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wynik(string wyjscie, unsigned int iloscpartii, unsigned int mandaty[ ])
{
    
    if(wyjscie.empty())
        Wynik_konsola( mandaty, iloscpartii);
    else
    {
        ofstream plikwyjscia("../dat/" + wyjscie + ".txt");
        if(plikwyjscia)
        {
            plikwyjscia << " Podzial mandatow:" << endl;
            for (int i = 0; i < iloscpartii; i++)
            {
                plikwyjscia << " partia " << i + 1 << ": " << mandaty[i] << endl;
            }
            plikwyjscia.close();
        }
    }
    
}

int main(int ile, char ** argumenty)
{
    const int MAX = 100;  // maksymalna ilosc partii ktora moze wziac udzial w wyborach parlamentarnych
    unsigned int mandaty[MAX]; // tablica ktora przechowuje ilosc mandatow otrzymanych przez poszczegolne partie
    unsigned int glosy[MAX]; // tablica ktora przechowuje ilosc glosow oddanych na poszczegolne partie
    unsigned int iloscpartii; // ilosc partii ktora bierze udzial w wyborach
    unsigned int iloscmandatow; // ilosc mandatow do podzialu w wyborach

    string nazwa_pliku_wejscia; // nazwa pliku z ktorego beda pobierane dane
    string nazwa_pliku_wyjsca; // nazwa pliku w ktorym beda zapisywane wyniki wyborow
    
    Odczytaj_argumenty(ile, argumenty, nazwa_pliku_wejscia, nazwa_pliku_wyjsca);
    
    if(Pobieranie_danych(nazwa_pliku_wejscia, MAX, glosy, iloscpartii, iloscmandatow))
    {
        Wyzerowanie_mandatow( mandaty, iloscpartii);
        Podzial_mandatow(MAX, mandaty, glosy, iloscpartii, iloscmandatow);
        Wynik(nazwa_pliku_wyjsca, iloscpartii, mandaty);
    }
    return 0;
}
