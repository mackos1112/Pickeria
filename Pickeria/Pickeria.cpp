#include <iostream>
#include <list>
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
