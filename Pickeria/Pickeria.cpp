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



class Zamowienie {	//placeholder zeby mi kompilator dziala
public:
    Zamowienie() {

    }
    ~Zamowienie() {

    }

private:

};

class Platnosc {	//parametry przeniesione z diagramu
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

class Gotowka {
private:
    float otrzymanaGotowka;

public:
    Gotowka() {

    }
    ~Gotowka() {

    }

};

class Karta {
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
    string numerRezerwacji;

    string imieKlienta;
    string nazwiskoKlienta;
    string numerTelefonu;
    int iloscOsob;

    int dataRezerwacji;             //wstepnie dla uproszczenia data rezerwacji to dzien miesiaca
    int godzinaRezerwacji;          //rezerwujemy tylko na pelne godziny(bez minut)
    int czasRezerwacji;             //czas rezerwacji minimum 1h, calkowite godziny
public:
    Rezerwacja(string imie, string nazwisko, string telefon, int osoby, int czas, int data, int godzina) {
        //generowanie numeru rezerwacji - albo data i godzina, albo inkrementacja poprzedniej rezerwacji
        numerRezerwacji = imie.substr(0, 1) + nazwisko.substr(0, 1) + to_string(data) + "0" + to_string(godzina) + "o" + to_string(osoby);

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

    string getRezerwacja() {
        return numerRezerwacji;
    }

    bool czyKoliduje(int data, int godzina) {          //funckja pomocnicza abym nie musial pisac rozbudowanych warunkow
        if (data != dataRezerwacji) return false;        //sprawdza czy podana data i godzina nie zachacza o jakas rezerwacje
        else {                                          //uwzglednia czas rezerwacji
            if (godzina >= godzinaRezerwacji && godzina <= (godzinaRezerwacji + czasRezerwacji)) return false;
            else return true;                          //zwraca true gdy podane godziny koliduja z ta rezerwacja
        }
    }

};



class Stolik {
private:
    int numerStolika;
    int liczbaMiejsc;

    int ostatniaRezerwacja = 0;             //numer elemntu tablicy pod ktorym jest ostatnia rezerwacja
    static int iloscStolikow;
    
public:
    Rezerwacja tablicaRezerwacji[100];  //ile maksymalnie rezerwacji moze byc?


    Stolik(int miejsca) {
        iloscStolikow++;
        numerStolika = iloscStolikow;
        liczbaMiejsc = miejsca;
    }


    void zarezerwujStolik(int data, int godzina) {      //data i godzina sa podawane podczas wywietlania stolikow

        //wprowadzenie danych rezerwacji
        string imie, nazwisko, telefon;
        int czas, osoby;

        cout << endl;
        cout << "Podaj" << endl;
        cout << "Imie: " << endl;
        cin >> imie;
        cout << "Nazwisko: " << endl;
        cin >> nazwisko;
        cout << "Numer telefonu: " << endl;
        cin >> telefon;
        do {
            cout << "Jak dlugo: " << endl;
            cin >> czas;
            if (czas <= 0)cout << "Bledny czas, sprobuj jeszcze raz" << endl;
        } while (czas <= 0);
        do {
            cout << "Ilosc osob: " << endl;
            cin >> osoby;
            if (osoby > liczbaMiejsc) cout << "Za duzo osob, sprobuj jeszcze raz" << endl;
            if (osoby <= 0) cout << "Bledna ilsoc osob, sprobuj jeszcze raz" << endl;
        } while (osoby > liczbaMiejsc || osoby <= 0);

        int i = ++ostatniaRezerwacja;

        tablicaRezerwacji[i] = Rezerwacja(imie, nazwisko, telefon, osoby, czas, data, godzina);

        cout << "Twoj numer Rezerwacji: " << endl;
        cout << tablicaRezerwacji[i].getRezerwacja();

    }

    void anulujRezerwacjeStolika(int numer) {


    }

    static int getIloscStolikow() { //getter, nie ma go w diagramie klas -gicu
        return iloscStolikow;
    }


    int getOstatnia() {
        return ostatniaRezerwacja;

    }

    int getLiczbaMiejsc() {
        return liczbaMiejsc;
    }
};
int Stolik::iloscStolikow = 0;

class SystemRestauracji {                       //singleton
private:
    Stolik stoliki[7] = { Stolik(6), Stolik(6), Stolik(4), Stolik(4), Stolik(5), Stolik(5), Stolik(5) };
    //stoliki musza byc powiazane z systemem rezerwacji
public:
    SystemRestauracji() {

    }

    void WyswietlWolneStoliki(int data, int godzina) {
        bool czy_wolny = true;
        cout << "WOLNE STOLIKI" << endl;
        for (int i = 0; i < Stolik::getIloscStolikow(); i++) {
            for (int j = 0; j < stoliki[i].getOstatnia(); j++) {
                if (stoliki[i].tablicaRezerwacji[j].czyKoliduje(data, godzina)) {
                    czy_wolny = false;
                    break;
                }
            }
            if (czy_wolny) {
                cout << i + 1 << ". Stolik numer " << i + 1 << endl;
                cout << "Liczba miejsc: " << stoliki[i].getLiczbaMiejsc() << endl;
            }
        }
    }

    Stolik getStolikONr(int nr_stolika) {
        return stoliki[nr_stolika - 1];
    }

    void WyswietlBiezaceMenu() {

    }

    void EdytujMenu() {

    }

    void SprawdzStanSkladnikow() {

    }

    void GenerujRaportStanowMagazynowych() {

    }

    void WprowadzenieTowaru() {

    }

    void RaportDobowy() {

    }

    void RaportMiesieczny() {

    }

};



int main() {



    SystemRestauracji* PICKERIA = new SystemRestauracji();

	

    int wybor;
    bool kierownik = false;
    cout << "MENU GLOWNE" << endl;
    cout << "1. Klient" << endl;
    cout << "2. Pracownik" << endl;
    cout << "3. Kierownik" << endl;
    cout << endl << "0. Zakoncz" << endl;
    //cout <<"TEST___iloscStolikow "<< Stolik::getIloscStolikow();   //testowa getter, stoliki dzialaja -gicu
    cin >> wybor;

    system("cls");

    switch (wybor) {
    case 1:
        cout << "KLIENT" << endl;
        cout << "1. Zarezerwuj stolik" << endl;
        cout << "2. Zamow posilek" << endl;
        cout << "3. Oplac zamowinie" << endl;       //czy konieczne? czy nie lepiej zintegrowac z zamowieniem posilku 
        cout << "4. Anuluj rezerwacje stolika" << endl;     // use case - zwolnienie stolika
        cout << "5. Anuluj zamowienie" << endl;
        cout << endl << "0. Zakoncz" << endl;
        cin >> wybor;

        system("cls");

        switch (wybor)
        {
        case 1:
            //Rezerwacja stolika
            int data, godzina;
            cout << "Rezerwacja stolika" << endl;
            cout << "Podaj date: " << endl;
            cin >> data;
            cout << "Podaj godzine: " << endl;
            cin >> godzina;

            PICKERIA->WyswietlWolneStoliki(data, godzina);

            int wybor;
            cout << "Wybierz stolik: " << endl;
            cin >> wybor;

            PICKERIA->getStolikONr(wybor).zarezerwujStolik(data, godzina);
            break;
        case 2:
            //Zamawianie posilku
            cout << "Zamawianie posilku" << endl;
            break;
        case 3:
            //Oplacanie zamowienia
            cout << "Oplacanie zamowienia" << endl;
            break;
        case 4:
            //Anulowanie rezerwacji stolika
            cout << "Anulowanie rezerwacji stolika" << endl;
            break;
        case 5:
            //Anulowanie zamowienia
            cout << "Anulowanie zamowienia" << endl;
            break;
        default:
            break;
        }
        break;
    case 2:
    case 3:

        if (wybor == 2) cout << "PRACOWNIK" << endl;
        else {
            cout << "KIEROWNIK" << endl;
            kierownik = true;
        }

        cout << "1. Przygotowanie zamowienia" << endl;
        cout << "2. Wydanie zamowienia" << endl;
        cout << "3. Weryfikacja stanu magazynowego" << endl;
        cout << "4. Anuluj rezerwacje stolika" << endl;
        cout << "5. Anuluj zamowienie" << endl;
        cout << "6. Generuj raport kasowy" << endl;

        if (kierownik) {
            cout << "7. Zamowienie towaru" << endl;
            cout << "8. Zmiana menu" << endl;

        }

        cout << endl << "0. Zakoncz" << endl;
        cin >> wybor;

        system("cls");

        switch (wybor)
        {
        case 1:
            //Przygotowanie zamowienia
            cout << "Przygotowanie zamowienia" << endl;
            break;
        case 2:
            //Wydanie zamowienia
            cout << "Wydanie zamowienia" << endl;
            break;
        case 3:
            //Weryfikacja stanu magazynowego
            cout << "Weryfikacja stanu magazynowego" << endl;
            break;
        case 4:
            //Anulowanie rezerwacji stolika
            cout << "Anulowanie rezerwacji stolika" << endl;
            break;
        case 5:
            //Anulowanie zamowienia
            cout << "Anulowanie zamowienia" << endl;
            break;
        case 6:
            //raport kasowy
            cout << "Raport kasowy" << endl;
            break;
        case 7:
            if (kierownik) {
                //zamowienie towaru
                cout << "Towar" << endl;
            }
            break;
        case 8:
            if (kierownik) {
                //zmiana menu
                cout << "Nowe menu" << endl;
            }
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }



    return 0;
}
