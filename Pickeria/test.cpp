#include "pch.h"
#include "CppUnitTest.h"
#include "Pickeria.cpp"

// Test klasy Skladnik
TEST(SkladnikTest, Konstruktor) {
	Skladnik s("Pomidor", "kg", 5.0);
	EXPECT_EQ(s.getNazwaSkladnika(), "Pomidor");
	EXPECT_EQ(s.getJednostka(), "kg");
	EXPECT_DOUBLE_EQ(s.getCenaJednostkowa(), 5.0);
}

TEST(SkladnikTest, SetGetMethods) {
	Skladnik s("Pomidor", "kg", 5.0);
	s.setNazwaSkladnika("Ogórek");
	s.setJednostka("szt");
	s.setCenaJednostkowa(3.0);
	EXPECT_EQ(s.getNazwaSkladnika(), "Ogórek");
	EXPECT_EQ(s.getJednostka(), "szt");
	EXPECT_DOUBLE_EQ(s.getCenaJednostkowa(), 3.0);
}

// Test klasy ElementPosilku
TEST(ElementPosilkuTest, Konstruktor) {
	ElementPosilku ep(5);
	EXPECT_EQ(ep.getIlosc(), 5);
}

TEST(ElementPosilkuTest, SetGetIlosc) {
	ElementPosilku ep(5);
	ep.setIlosc(10);
	EXPECT_EQ(ep.getIlosc(), 10);
}

// Test klasy Posilek
TEST(PosilekTest, SetGetCena) {
	Posilek p;
	p.setCena(25.5);
	EXPECT_DOUBLE_EQ(p.getCena(), 25.5);
}

// Test klasy Platnosc
TEST(PlatnoscTest, AnulujPlatnosc) {
	Platnosc p;
	p.anulujPlatnosc();
	// Zak³adaj¹c, ¿e jest metoda getStatusPlatnosci() do sprawdzenia statusu p³atnoœci
	// EXPECT_EQ(p.getStatusPlatnosci(), 9);
}

TEST(PlatnoscTest, Zaplac) {
	Platnosc p;
	EXPECT_EQ(p.zaplac(), 1);
}

// Test klasy Rezerwacja
TEST(RezerwacjaTest, Konstruktor) {
	Rezerwacja r("Jan", "Kowalski", "123456789", 4, 2, 20230521, 18);
	EXPECT_EQ(r.getImie(), "Jan");
	EXPECT_EQ(r.getNazwisko(), "Kowalski");
	EXPECT_EQ(r.getNumer(), "123456789");
}

// Test klasy Stolik
TEST(StolikTest, Konstruktor) {
	Stolik s(4);
	EXPECT_EQ(s.getLiczbaMiejsc(), 4);
}

TEST(StolikTest, GetIloscStolikow) {
	Stolik s1(4);
	Stolik s2(6);
	EXPECT_EQ(Stolik::getIloscStolikow(), 3);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}