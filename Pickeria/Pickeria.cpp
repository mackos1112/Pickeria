// Pickeria.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
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


int main()
{
	std::cout << "Ciekawe czy to dziala\n";
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln