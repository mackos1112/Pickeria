#include <iostream>
#include <list>
#include <string>

using namespace std;

class Skladnik {
private:
    string nazwaSkladnika;
    string jednostka;
    double cenaJednostkowa;
    static int id;
public:
    string getNazwaSkladnika() {
        return nazwaSkladnika;
    }

    string getJednostka() {
        return jednostka;
    }

    double getCenaJednostkowa() {
        return cenaJednostkowa;
    }

    int getID() {
        return id;
    }

    void setNazwaSkladnika(string nazwa) {
        this->nazwaSkladnika = nazwa;
    }

    void setJednostka(string jednostka) {
        this->jednostka = jednostka;
    }

    void setCenaJednostkowa(double cena) {
        this->cenaJednostkowa = cena;
    }

    Skladnik(string nazwa, string jednostkaZ, double cena) {

        nazwaSkladnika = nazwa;
        jednostka = jednostkaZ;
        cenaJednostkowa = cena;

        id++;

    }

    ~Skladnik() {

    }

};

class ElementPosilku {
private:
    Skladnik** skladnik;  // pojedynczy skladnik
    int ilosc;
public:

    void setIlosc(int number) {
        this->ilosc = number;
    }

    int getIlosc() {
        return ilosc;
    }

    ElementPosilku(int size) : ilosc(size) {
        skladnik = new Skladnik * [size];
    }


    ~ElementPosilku() {
        delete[] skladnik;
    }
};

class Posilek {
private:
    list<Skladnik> listaSkladnikow;   //elementow posilku lista
    double cena;

public:
    double getCena() {
        return cena;
    }

    void setCena(double cenaZ) {
        this->cena = cenaZ;
    }                            //Konstruktor i destruktor
};

class ElementZamowienia {
private:
    Posilek posilek;
    int ilosc;                    //Konstruktor i destruktor
};

int Skladnik::id = 0;



class Zamowienie{	//placeholder zeby mi kompilator dziala
public:
    Zamowienie() {

    }
    ~Zamowienie() {

    }

private:

};

class Platnosc{	//parametry przeniesione z diagramu
private:
    int statusPlatnosci;	//mysle zeby statusy zrobic 0-9, obmnysle i napisze potem
    float napiwek;
    Zamowienie zamowienie;
    int numerPlatnosci;

public:
    int zaplac() {
        return 1;
    }
    void anulujPlatnosc() {
        statusPlatnosci = 9;
    }
};

class Gotowka{
private:
    float otrzymanaGotowka;

public:
    Gotowka() {

    }
    ~Gotowka() {

    }

};

class Karta{
private:
    string nazwaKarty;
    string typKarty;
    string nazwaBanku;
    int dataWaznosci;	//mozna potem zmienic na typ date

public:
    Karta() {

    }
    ~Karta() {

    }
    void autoryzacja() {

    }

};



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

    void anulujRezerwacjeStolika(int numer) {


    }

    static void wyswietlWolneStoliki(int data, int godzina) {

    }


};

int Stolik::iloscStolikow = 0;




int main() {
	return 0;
}
