#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Skladnik {
private:
	string nazwaSkladnika;
	string jednostka;
	double cenaJednostkowa;
	static int idCounter;
	int id;
	int ilosc_na_magazynie;

public:
	Skladnik(string nazwa, string jednostkaZ, double cena) : nazwaSkladnika(nazwa), jednostka(jednostkaZ), cenaJednostkowa(cena), ilosc_na_magazynie(0) {
		id = ++idCounter;
	}

	string getNazwaSkladnika() const {
		return nazwaSkladnika;
	}

	string getJednostka() const {
		return jednostka;
	}

	double getCenaJednostkowa() const {
		return cenaJednostkowa;
	}

	int getID() const {
		return id;
	}

	int getIlosc_na_magazynie() const {
		return ilosc_na_magazynie;
	}

	void setIlosc_na_magazynie(int ilosc) {
		ilosc_na_magazynie = ilosc;
	}

	void setNazwaSkladnika(string nazwa) {
		nazwaSkladnika = nazwa;
	}

	void setJednostka(string jednostka) {
		this->jednostka = jednostka;
	}

	void setCenaJednostkowa(double cena) {
		cenaJednostkowa = cena;
	}
};

int Skladnik::idCounter = 0;

class ElementPosilku {
private:
	Skladnik* skladnik;
	float ilosc;

public:
	ElementPosilku(Skladnik* skl, float ilosc) : skladnik(skl), ilosc(ilosc) {}

	Skladnik* getSkladnik() const {
		return skladnik;
	}

	float getIlosc() const {
		return ilosc;
	}

	void setIlosc(float ilosc) {
		this->ilosc = ilosc;
	}

	double getKoszt() const {
		return ilosc * skladnik->getCenaJednostkowa();
	}
};

class Posilek {
private:
	vector<ElementPosilku> elementy;
	float cena;

public:
	Posilek() : cena(0) {}

	void dodajElement(const ElementPosilku& element) {
		elementy.push_back(element);
		cena += element.getKoszt();
	}

	float getCena() const {
		return cena;
	}

	double getKoszt() const {
		double koszt = 0.0;
		for (const auto& element : elementy) {
			koszt += element.getKoszt();
		}
		return koszt;
	}

	void wypisz() const {
		for (const auto& element : elementy) {
			cout << "Skladnik: " << element.getSkladnik()->getNazwaSkladnika()
				<< ", Ilosc: " << element.getIlosc()
				<< " " << element.getSkladnik()->getJednostka()
				<< ", Koszt: " << element.getKoszt() << " zl" << endl;
		}
		cout << "Calkowity koszt posilku: " << getKoszt() << " zl" << endl;
	}
};

void wczytajSkladniki(const string& filename, vector<Skladnik>& skladniki) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Nie mozna otworzyc pliku: " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string nazwa, jednostka, cenaStr;
		getline(ss, nazwa, ';');
		getline(ss, jednostka, ';');
		getline(ss, cenaStr, ';');
		double cena = stod(cenaStr);

		skladniki.emplace_back(nazwa, jednostka, cena);
	}

	file.close();
}

void wczytajPosilki(const string& filename, vector<Posilek>& posilki, const vector<Skladnik>& skladniki) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Nie mozna otworzyc pliku: " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string elementStr;
		Posilek posilek;

		while (getline(ss, elementStr, ';')) {
			stringstream elementSS(elementStr);
			string nazwaSkladnika, iloscStr;
			getline(elementSS, nazwaSkladnika, ',');
			getline(elementSS, iloscStr, ',');

			float ilosc = stof(iloscStr);

			auto it = find_if(skladniki.begin(), skladniki.end(), [&nazwaSkladnika](const Skladnik& s) {
				return s.getNazwaSkladnika() == nazwaSkladnika;
				});

			if (it != skladniki.end()) {
				ElementPosilku element(const_cast<Skladnik*>(&(*it)), ilosc);
				posilek.dodajElement(element);
			}
		}

		posilki.push_back(posilek);
	}

	file.close();
}

class ElementZamowienia {
private:
	Posilek posilek;
	int ilosc;

public:
	ElementZamowienia(Posilek p, int i) : posilek(p), ilosc(i) {}

	int getIlosc() {
		return ilosc;
	}

	Posilek getPosilek() {
		return posilek;
	}
};

class Zamowienie {
private:
	list<ElementZamowienia> elementZamowienia;
	float kwota;
	string numerRezerwacji;
	int statusZamowienia;
	int numerZamowienia;
	//10 zamowienie przyjmowane
	//11 zamowienie przyjete nie oplacone
	//12 nie oplacone w przygotowaniu
	//13 nie oplacone do wydania
	//21 przyjete ooplacone
	//22 oplacone i w przygotoweaniu
	//23 oplacone do wydania
	//31 final - oplacone i wydane
	//90 anulowane
	static int liczbaZamowien;

public:
	Zamowienie(string nrR) : kwota(0), statusZamowienia(0) {
		numerZamowienia = ++liczbaZamowien;
		numerRezerwacji = nrR;
	}

	void finalizujZamowienie() {
		// Implementacja metody finalizujZamowienie
		if (statusZamowienia < 20)
		{
		}
		else if (statusZamowienia > 20 && statusZamowienia < 30)	//jest 30 bo nie wiadomo czy w przyszlosci cos nie bedzie jeszcze dodane
		{
			statusZamowienia = 31;
		}
	}

	void anulujZamowienie() {
		statusZamowienia = 9; // Status anulowane
	}

	void przygotujZamowienie() {
		// Implementacja metody przygotujZamowienie
	}

	void setStatusZamowienia(int status) {
		statusZamowienia = status;
	}

	void dodajElementZamowienia(ElementZamowienia element) {
		elementZamowienia.push_back(element);
	}

	float getKwota() {
		return kwota;
	}

	int getNumerZamowienia() {
		return numerZamowienia;
	}

	void setNumerRezerwacji(string nr) {
		numerRezerwacji = nr;
	}

	string getNumerRezerwacji() {
		return numerRezerwacji;
	}

	int getStatusZamowienia() {
		return statusZamowienia;
	}
};
int Zamowienie::liczbaZamowien = 0;

class Platnosc {
private:
	int numerPlatnosci;
	Zamowienie zamowienie;
	float napiwek;
	int statusPlatnosci;

public:
	int zaplac() {
		statusPlatnosci = 1; // P³atnoœæ zrealizowana
		return 1;
	}

	void anulujPlatnosc() {
		statusPlatnosci = 9; // P³atnoœæ anulowana
	}

	float getNapiwek() {
		return napiwek;
	}

	int getStatusPlatnosci() {
		return statusPlatnosci;
	}
};

class Gotowka : public Platnosc {
private:
	float otrzymanaGotowka;

public:
	void wydajReszte() {
		// Implementacja metody wydajReszte
	}
};

class Karta : public Platnosc {
private:
	string nazwaKarty;
	string typKarty;
	string nazwaBanku;
	string dataWaznosci; // Typ zmieniony na string dla uproszczenia

public:
	void autoryzacja() {
		// Implementacja metody autoryzacja
	}
};

class Rezerwacja {
private:
	string numerRezerwacji;
	string imieKlienta;
	string nazwiskoKlienta;
	string numerTelefonu;
	int iloscOsob;
	int dataRezerwacji;
	int godzinaRezerwacji;
	int czasRezerwacji;

public:
	Rezerwacja(string imie, string nazwisko, string telefon, int osoby, int czas, int data, int godzina) {
		numerRezerwacji = imie.substr(0, 1) + nazwisko.substr(0, 1) + to_string(data) + "0" + to_string(godzina) + "o" + to_string(osoby);
		imieKlienta = imie;
		nazwiskoKlienta = nazwisko;
		numerTelefonu = telefon;
		iloscOsob = osoby;
		dataRezerwacji = data;
		godzinaRezerwacji = godzina;
		czasRezerwacji = czas;
	}

	Rezerwacja() {}

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

	bool czyKoliduje(int data, int godzina) {
		if (data != dataRezerwacji) return false;
		else {
			if (godzina >= godzinaRezerwacji && godzina <= (godzinaRezerwacji + czasRezerwacji)) return false;
			else return true;
		}
	}
};

class Stolik {
private:
	int numerStolika;
	int liczbaMiejsc;
	int ostatniaRezerwacja = 0;
	static int iloscStolikow;

public:
	Rezerwacja tablicaRezerwacji[100];

	Stolik(int miejsca) {
		iloscStolikow++;
		numerStolika = iloscStolikow;
		liczbaMiejsc = miejsca;
	}

	void zarezerwujStolik(int data, int godzina) {
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
			if (czas <= 0) cout << "Bledny czas, sprobuj jeszcze raz" << endl;
		} while (czas <= 0);
		do {
			cout << "Ilosc osob: " << endl;
			cin >> osoby;
			if (osoby > liczbaMiejsc) cout << "Za duzo osob, sprobuj jeszcze raz" << endl;
			if (osoby <= 0) cout << "Bledna ilosc osob, sprobuj jeszcze raz" << endl;
		} while (osoby > liczbaMiejsc || osoby <= 0);

		int i = ++ostatniaRezerwacja;

		tablicaRezerwacji[i] = Rezerwacja(imie, nazwisko, telefon, osoby, czas, data, godzina);

		cout << "Twoj numer Rezerwacji: " << endl;
		cout << tablicaRezerwacji[i].getRezerwacja();
	}

	void anulujRezerwacjeStolika(int numer) {
		// Implementacja anulowania rezerwacji stolika
	}

	static int getIloscStolikow() {
		return iloscStolikow;
	}

	int getOstatnia() {
		return ostatniaRezerwacja;
	}

	int getLiczbaMiejsc() {
		return liczbaMiejsc;
	}

	bool czyWolny(int data, int godzina) {
		for (int i = 0; i < ostatniaRezerwacja; i++) {
			if (tablicaRezerwacji[i].czyKoliduje(data, godzina)) {
				return false;
			}
		}
		return true;
	}
};

int Stolik::iloscStolikow = 0;

class SystemRestauracji {
private:
	Stolik stoliki[7] = { Stolik(6), Stolik(6), Stolik(4), Stolik(4), Stolik(5), Stolik(5), Stolik(5) };
	vector<Skladnik> skladniki;
	vector<Posilek> menu;
	vector<Zamowienie> zamowienia;

public:
	SystemRestauracji() {}

	void wyswietlWolneStoliki(int data, int godzina) {
		cout << "WOLNE STOLIKI" << endl;
		for (int i = 0; i < Stolik::getIloscStolikow(); i++) {
			if (stoliki[i].czyWolny(data, godzina)) {
				cout << i + 1 << ". Stolik numer " << i + 1 << endl;
				cout << "Liczba miejsc: " << stoliki[i].getLiczbaMiejsc() << endl;
			}
		}
	}

	Stolik& getStolikONr(int nr_stolika) {
		return stoliki[nr_stolika - 1];
	}

	void wyswietlBiezaceMenu() {
		for (const Posilek& posilek : menu) {
			posilek.wypisz();
		}
	}

	void edytujMenu() {
		// Implementacja edycji menu
	}

	void sprawdzStanSkladnikow() {
		for (const Skladnik& skladnik : skladniki) {
			cout << "Skladnik: " << skladnik.getNazwaSkladnika() << ", Ilosc na magazynie: " << skladnik.getIlosc_na_magazynie() << endl;
		}
	}

	void generujRaportStanowMagazynowych() {
		// Implementacja generowania raportu stanów magazynowych
	}

	void wprowadzenieTowaru() {
		// Implementacja wprowadzania towaru
	}

	void raportDobowy() {
		// Implementacja raportu dobowego
	}

	void raportMiesieczny() {
		// Implementacja raportu miesiêcznego
	}

	void zamowieniePosilku(Zamowienie& zamowienie) {
		zamowienia.push_back(zamowienie);
		cout << "Zamowienie przyjete." << endl;
	}

	void anulowanieZamowienia(Zamowienie& zamowienie) {
		zamowienie.anulujZamowienie();
		cout << "Zamowienie anulowane." << endl;
	}
	Zamowienie getZamowienie(int nrZamoweinia) {
		for (Zamowienie& zam : zamowienia)
		{
			if (zam.getNumerZamowienia() == nrZamoweinia)
			{
				return zam;
			}
		}
	}
};

int main() {
	SystemRestauracji* PICKERIA = new SystemRestauracji();
	Zamowienie* zam01 = new Zamowienie("kg12313");
	PICKERIA->zamowieniePosilku(*zam01);
	system("cls");
	int wybor;
	bool kierownik = false;
	cout << "MENU GLOWNE" << endl;
	cout << "1. Klient" << endl;
	cout << "2. Pracownik" << endl;
	cout << "3. Kierownik" << endl;
	cout << endl << "0. Zakoncz" << endl;
	cin >> wybor;

	system("cls");

	switch (wybor) {
	case 1:
		cout << "KLIENT" << endl;
		cout << "1. Zarezerwuj stolik" << endl;
		cout << "2. Zamow posilek" << endl;
		cout << "3. Oplac zamowinie" << endl;
		cout << "4. Anuluj rezerwacje stolika" << endl;
		cout << "5. Anuluj zamowienie" << endl;
		cout << endl << "0. Zakoncz" << endl;
		cin >> wybor;

		system("cls");

		switch (wybor) {
		case 1:
			// Rezerwacja stolika
			int data, godzina;
			cout << "Rezerwacja stolika" << endl;
			cout << "Podaj date: " << endl;
			cin >> data;
			cout << "Podaj godzine: " << endl;
			cin >> godzina;

			PICKERIA->wyswietlWolneStoliki(data, godzina);

			int wyborStolika;
			cout << "Wybierz stolik: " << endl;
			cin >> wyborStolika;

			PICKERIA->getStolikONr(wyborStolika).zarezerwujStolik(data, godzina);
			break;
		case 2:
			// Zamawianie posilku
			cout << "Zamawianie posilku" << endl;

			break;
		case 3:
			// Oplacanie zamowienia
			cout << "Oplacanie zamowienia" << endl;
			//cout << Zamowienie::liczbaZamowien;
			cout << "Podaj numer zamowienia: ";
			int wyborZamowienia;
			cin >> wyborZamowienia;
			PICKERIA->getZamowienie(wyborZamowienia).finalizujZamowienie();

			break;
		case 4:
			// Anulowanie rezerwacji stolika
			cout << "Anulowanie rezerwacji stolika" << endl;
			break;
		case 5:
			// Anulowanie zamowienia
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

		switch (wybor) {
		case 1:
			// Przygotowanie zamowienia
			cout << "Przygotowanie zamowienia" << endl;
			break;
		case 2:
			// Wydanie zamowienia
			cout << "Wydanie zamowienia" << endl;
			break;
		case 3:
			// Weryfikacja stanu magazynowego
			cout << "Weryfikacja stanu magazynowego" << endl;
			PICKERIA->sprawdzStanSkladnikow();
			break;
		case 4:
			// Anulowanie rezerwacji stolika
			cout << "Anulowanie rezerwacji stolika" << endl;
			break;
		case 5:
			// Anulowanie zamowienia
			cout << "Anulowanie zamowienia" << endl;
			break;
		case 6:
			// Raport kasowy
			cout << "Raport kasowy" << endl;
			break;
		case 7:
			if (kierownik) {
				// Zamowienie towaru
				cout << "Towar" << endl;
			}
			break;
		case 8:
			if (kierownik) {
				// Zmiana menu
				cout << "Nowe menu" << endl;
				PICKERIA->edytujMenu();
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	vector<Skladnik> skladniki;
	wczytajSkladniki("skladniki.txt", skladniki);

	vector<Posilek> posilki;
	wczytajPosilki("menu.txt", posilki, skladniki);

	for (const auto& posilek : posilki) {
		posilek.wypisz();
		cout << endl;
	}
	return 0;
}