#include <iostream>
#include <list>
using namespace std;


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

class ElementPosilku  {
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

int main()                    //Dane o posilkach i elementach posilku
{
    
}
