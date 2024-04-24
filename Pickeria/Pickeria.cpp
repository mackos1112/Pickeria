#include <iostream>
#include <list>
using namespace std;




class Rezerwacja {
private:
    int numerRezerwacji;

    string imieKlienta;
    string nazwiskoKlienta;
    string numerTelefonu;
    int iloscOsob;          //czy potrzebne?

    int dataRezerwacji;
    int godzinaRezerwacji;
    int czasRezerwacji;     //jzk dlugo zajety
public:
    Rezerwacja(string imie, string nazwisko, string telefon, int osoby, int czas, int data, int godzina) {
        //generowanie numeru rezerwacji - albo data i godzina, albo inkrementacja poprzedniej rezerwacji
        imieKlienta = imie;
        nazwiskoKlienta = nazwisko;
        numerTelefonu = telefon;
        iloscOsob = osoby;

        dataRezerwacji = data;
        godzinaRezerwacji = godzina;
        czasRezerwacji = czas;
    }

    Rezerwacja() {

    }

    string getImie() {
        return imieKlienta;
    }

    string getNazwisko() {
        return nazwiskoKlienta;
    }

    string getNumer() {
        return numerTelefonu;
    }

};

class Stolik {
private:
    int numerStolika;
    int liczbaMiejsc;
    Rezerwacja tablicaRezerwacji[100];  //ile maksymalnie rezerwacji moze byc?
    int ostatniaRezerwacja = 0;             //numer elemntu tablicy pod ktorym jest ostatnia rezerwacja
    


    static int iloscStolikow;
public:

    Stolik(int miejsca) {
        iloscStolikow++;
        numerStolika = iloscStolikow;
        liczbaMiejsc = miejsca;

    }
    

    bool zarezerwujStolik() {
        //wprowadzenie danych rezerwacji

        int i = ++ostatniaRezerwacja;
        tablicaRezerwacji[i] = Rezerwacja();        //dac konstruktor wieloparametrowy

    }

    void anulujRezerwacjeStolika(int numer){


    }

    static void wyswietlWolneStoliki(int data, int godzina) {

    }


};

int Stolik::iloscStolikow = 0;

int main()
{
    
}
