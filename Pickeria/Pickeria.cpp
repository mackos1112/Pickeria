
#include <list>
using namespace std;





class Rezerwacja {

//#include <iostream>
#include <string>

using namespace std;

class Zamowienie	//placeholder zeby mi kompilator dzialal
{
public:
	Zamowienie();
	~Zamowienie();

private:

};

Zamowienie::Zamowienie()
{
}

Zamowienie::~Zamowienie()
{
}
class Platnosc	//parametry przeniesione z diagramu
{
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
class Gotowka
{
public:
	Gotowka() {

	}
	~Gotowka();
	
private:
	float otrzymanaGotowka;
};
class Karta
{
public:
	Karta() {

	}
	~Karta();
	void autoryzacja();
private:
	string nazwaKarty;
	string typKarty;
	string nazwaBanku;
	int dataWaznosci;	//mozna potem zmienic na typ date
};


class Skladnik {

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

class ElementPosilku  {
private:
    Skladnik** skladnik;  // pojedynczy skladnik
    int ilosc;


        int i = ++ostatniaRezerwacja;
        tablicaRezerwacji[i] = Rezerwacja();        //dac konstruktor wieloparametrowy

    }

    void anulujRezerwacjeStolika(int numer){


    }


    static void wyswietlWolneStoliki(int data, int godzina) {

class Posilek {
private:
    list<Skladnik> listaSkladnikow;   //elementow posilku lista
    double cena;


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

int Stolik::iloscStolikow = 0;

int main()                    //Dane o posilkach i elementach posilku
{
    
}
