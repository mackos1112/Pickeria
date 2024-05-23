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
	int nrwMenu;                        //potrzebne dla ulatwienia wskazywania towaru przy zamawianiu - uroki interfejsu tekstowego
	static int ostatniwMenu;
	string nazwa;
	vector<ElementPosilku> elementy;
	float cena;

public:
	Posilek() : cena(0) {
		ostatniwMenu++;
		nrwMenu = ostatniwMenu;
	}

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

	string getNazwa() const {
		return nazwa;
	}

	void setNazwa(const string& nazwaZ) {
		this->nazwa = nazwaZ;
	}

	int getNr() const {
		return nrwMenu;
	}

	bool sprawdzStanSkladnikow(int ilosc) const {
		for (const auto& element : elementy) {
			if (ilosc > element.getSkladnik()->getIlosc_na_magazynie()) {
				return false;
			}
		}
		return true;
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

int Posilek::ostatniwMenu = 0;

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

		try {
			double cena = stod(cenaStr);
			skladniki.emplace_back(nazwa, jednostka, cena);
		}
		catch (const invalid_argument& e) {
			cerr << "Blad konwersji ceny dla skladnika: " << nazwa << endl;
		}
		catch (const out_of_range& e) {
			cerr << "Cena poza zakresem dla skladnika: " << nazwa << endl;
		}
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

			try {
				float ilosc = stof(iloscStr);

				auto it = find_if(skladniki.begin(), skladniki.end(), [&nazwaSkladnika](const Skladnik& s) {
					return s.getNazwaSkladnika() == nazwaSkladnika;
					});

				if (it != skladniki.end()) {
					ElementPosilku element(const_cast<Skladnik*>(&(*it)), ilosc);
					posilek.dodajElement(element);
				}
				else {
					cerr << "Skladnik " << nazwaSkladnika << " nie znaleziony w bazie." << endl;
				}
			}
			catch (const invalid_argument& e) {
				cerr << "Blad konwersji ilosci dla skladnika: " << nazwaSkladnika << endl;
			}
			catch (const out_of_range& e) {
				cerr << "Ilosc poza zakresem dla skladnika: " << nazwaSkladnika << endl;
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

	int getIlosc() const {
		return ilosc;
	}

	Posilek getPosilek() const {
		return posilek;
	}
};

class Zamowienie {
private:
	int numerZamowienia;
	list<ElementZamowienia> elementZamowienia;
	float kwota;
	string numerRezerwacji;
	int statusZamowienia;
	static int licznikZamowien;

public:
	Zamowienie() : kwota(0), statusZamowienia(0) {
		licznikZamowien++;
		numerZamowienia = licznikZamowien;
	}

	void finalizujZamowienie() {
		// Implementacja metody finalizujZamowienie
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

	void dodajElementZamowienia(const ElementZamowienia& element) {
		elementZamowienia.push_back(element);
	}

	float getKwota() const {
		return kwota;
	}

	int getNumerZamowienia() const {
		return numerZamowienia;
	}

	void setNumerRezerwacji(const string& nr) {
		numerRezerwacji = nr;
	}

	string getNumerRezerwacji() const {
		return numerRezerwacji;
	}

	int getStatusZamowienia() const {
		return statusZamowienia;
	}
};

int Zamowienie::licznikZamowien = 0;

class Platnosc {
private:
	int numerPlatnosci;
	Zamowienie zamowienie;
	float napiwek;
	int statusPlatnosci;

public:
	int zaplac() {
		statusPlatnosci = 1; // Płatność zrealizowana
		return 1;
	}

	void anulujPlatnosc() {
		statusPlatnosci = 9; // Płatność anulowana
	}

	float getNapiwek() const {
		return napiwek;
	}

	int getStatusPlatnosci() const {
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

	string getImie() const {
		return imieKlienta;
	}

	string getNazwisko() const {
		return nazwiskoKlienta;
	}

	string getNumer() const {
		return numerTelefonu;
	}

	string getRezerwacja() const {
		return numerRezerwacji;
	}

	bool czyKoliduje(int data, int godzina) const {
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

	string zarezerwujStolik(int data, int godzina) {
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

		return tablicaRezerwacji[i].getRezerwacja();
	}

	void anulujRezerwacjeStolika(const string& numer) {
		int indeks = -1;
		for (int i = 0; i < ostatniaRezerwacja; i++) {
			if (tablicaRezerwacji[i].getRezerwacja() == numer) {
				indeks = i;
				break;
			}
		}
		if (indeks > -1) {
			for (int i = indeks; i < ostatniaRezerwacja - 1; i++) tablicaRezerwacji[i] = tablicaRezerwacji[i + 1];
			ostatniaRezerwacja--;
			cout << "Rezerwacja prawidlowo anulowana" << endl;
		}
		else {
			cout << "Blad, nie ma takiej rezerwacji" << endl;
		}
	}

	static int getIloscStolikow() {
		return iloscStolikow;
	}

	int getOstatnia() const {
		return ostatniaRezerwacja;
	}

	int getLiczbaMiejsc() const {
		return liczbaMiejsc;
	}

	bool czyWolny(int data, int godzina) const {
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

	void wyswietlWolneStoliki(int data, int godzina) const {
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

	Posilek& getPosilekONr(int numer) {
		for (Posilek& posilek : menu) {
			if (posilek.getNr() == numer) {
				return posilek;
			}
		}
		throw invalid_argument("Posilek o podanym numerze nie istnieje.");
	}

	void wyswietlBiezaceMenu() const {
		for (const Posilek& posilek : menu) {
			posilek.wypisz();
		}
	}

	void edytujMenu() {
		// Implementacja edycji menu
	}

	void generujRaportStanowMagazynowych() const {
		cout << endl << "Raport Stanow Magazynowych" << endl;
		for (const Skladnik& skladnik : skladniki) {
			cout << "Skladnik: " << skladnik.getNazwaSkladnika() << ", Ilosc na magazynie: " << skladnik.getIlosc_na_magazynie() << endl;
		}
	}

	void sprawdzStanSkladnikow() const {
		for (const Skladnik& skladnik : skladniki) {
			cout << "Skladnik: " << skladnik.getNazwaSkladnika() << ", Ilosc na magazynie: " << skladnik.getIlosc_na_magazynie() << endl;
		}
	}

	void wprowadzenieTowaru() {
		// Implementacja wprowadzania towaru
	}

	void raportDobowy() {
		// Implementacja raportu dobowego
	}

	void raportMiesieczny() {
		// Implementacja raportu miesięcznego
	}

	void zamowieniePosilku(Zamowienie& zamowienie) {
		zamowienia.push_back(zamowienie);
		cout << "Zamowienie przyjete." << endl;
		cout << "Numer twojego zamowienia: " << zamowienie.getNumerZamowienia() << endl;
	}

	void anulowanieZamowienia(Zamowienie& zamowienie) {
		zamowienie.anulujZamowienie();
		cout << "Zamowienie anulowane." << endl;
	}
};

int main() {
	SystemRestauracji* PICKERIA = new SystemRestauracji();

	//inicjalizacja zmiennych wykorzystywanych pozniej w menu - kompilatorowi sie nie podoba jak inicjalizacja jest wewnatrz case
	int wybor, wybor2;
	int data, godzina;
	int wyborStolika;
	Zamowienie nowe;
	string nr;
	bool kontynuacja;
	string rezerwacja;
	//inicjalizacja zmiennych

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

			cout << "Rezerwacja stolika" << endl;
			cout << "Podaj date: " << endl;
			cin >> data;
			cout << "Podaj godzine: " << endl;
			cin >> godzina;

			PICKERIA->wyswietlWolneStoliki(data, godzina);

			cout << "Wybierz stolik: " << endl;
			cin >> wyborStolika;

			PICKERIA->getStolikONr(wyborStolika).zarezerwujStolik(data, godzina);
			break;
		case 2:
			// Zamawianie posilku
			cout << "Zamawianie posilku" << endl;

			cout << "Czy zarezerwowales juz stolik? " << endl;
			cout << "1. Tak" << endl;
			cout << "2. Nie" << endl;
			cin >> wybor;

			switch (wybor) {
			case 1:
				cout << "Podaj numer rezerwacji: " << endl;
				cin >> nr;
				break;
			default:
				//przerobic aby pobieralo czas z momentu zamawiania
				cout << "Rezerwacja stolika" << endl;
				cout << "Podaj date: " << endl;
				cin >> data;
				cout << "Podaj godzine: " << endl;
				cin >> godzina;

				PICKERIA->wyswietlWolneStoliki(data, godzina);

				cout << "Wybierz stolik: " << endl;
				cin >> wyborStolika;

				nr = PICKERIA->getStolikONr(wyborStolika).zarezerwujStolik(data, godzina);
				break;
			}
			nowe.setNumerRezerwacji(nr);
			PICKERIA->wyswietlBiezaceMenu();
			kontynuacja = false;
			do {
				cout << "Wybierz co chcialbys zjesc: " << endl;
				cin >> wybor;
				cout << "Podaj ilosc: " << endl;
				cin >> wybor2;
				if (PICKERIA->getPosilekONr(wybor).sprawdzStanSkladnikow(wybor2)) {
					cout << "Dodano do zamowienia: " << PICKERIA->getPosilekONr(wybor).getNazwa() << endl;
					ElementZamowienia nowyEl(PICKERIA->getPosilekONr(wybor), wybor2);
					nowe.dodajElementZamowienia(nowyEl);
					kontynuacja = false;
				}
				else {
					cout << "Niestety towar niedostepny wybierz cos innego" << endl;
					kontynuacja = true;
				}
				if (!kontynuacja) {
					cout << "Czy chcialbys cos jeszcze zamowic?" << endl;
					cout << "1. Tak" << endl;
					cout << "2. Nie" << endl;
					cin >> wybor;
					if (wybor == 1) kontynuacja = true;
					else kontynuacja = false;
				}
			} while (kontynuacja);

			nowe.setStatusZamowienia(1);        //status 1 - zamowienie przyjete
			PICKERIA->zamowieniePosilku(nowe);

			break;
		case 3:
			// Oplacanie zamowienia
			cout << "Oplacanie zamowienia" << endl;
			break;
		case 4:
			// Anulowanie rezerwacji stolika
			cout << "Anulowanie rezerwacji stolika" << endl;
			cout << "Podaj numer stolika: " << endl;
			cin >> wybor2;
			cout << "Podaj numer rezerwacji: " << endl;
			cin >> rezerwacja;
			PICKERIA->getStolikONr(wybor2).anulujRezerwacjeStolika(rezerwacja);
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
			PICKERIA->generujRaportStanowMagazynowych();
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

	delete PICKERIA;

	return 0;
}