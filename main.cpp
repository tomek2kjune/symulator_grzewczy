#include "Symulacja.h"
#include "BB_Regulator.h"
#include "PID_Regulator.h"
#include "BrakPomieszczenia.h"
#include "BrakGrzejnika.h"
#include "BrakRegulatora.h"
#include <iostream>
#include <string>
#include <cmath>

//struktura danych probkowania
typedef struct Probkowanie
{
	int iloscProbek;
	float czasProbki;
}; 

//tworzy pomieszczenie
Pomieszczenie* createPomieszczenie()
{
	std::string swys, ssze, sgle;
	float wys, sze, gle;

	std::cout << "OKRESL WYMIARY POMIESZCZENIA" << std::endl << std::endl;
	std::cout << "Podaj wysokosc w metrach (np. 1.2): ";
	std::cin >> swys;
	std::cout << "Podaj szerokosc w metrach (np. 1.2): ";
	std::cin >> ssze;
	std::cout << "Podaj glebokosc w metrach (np. 1.2): ";
	std::cin >> sgle;

	wys = std::stof(swys);
	sze = std::stof(ssze);
	gle = std::stof(sgle);
	wys = fabs(wys);
	sze = fabs(sze);
	gle = fabs(gle);

	if (wys == 0)
	{
		wys = 1;
	}
	if (sze == 0)
	{
		sze = 1;
	}
	if (gle == 0)
	{
		gle = 1;
	}
	
	std::cin.ignore();

	return new Pomieszczenie(wys, sze, gle);
}

//zwraca ilosc probek
int getIloscProbek()
{
	std::string sile;
	int ile;

	std::cout << "Podaj ilosc probek symulacji (np. 100): ";
	std::cin >> sile;

	ile = abs(std::stoi(sile));

	if (ile == 0)
	{
		ile = 1;
	}

	return ile;
}

//zwraca czas probki
float getCzasProbki()
{
	std::string stim;
	float tim;

	std::cout << "Podaj czas probkowania symulacji (np. 0.5): ";
	std::cin >> stim;

	tim = fabs(std::stof(stim));

	if (tim == 0)
	{
		tim = 0.1;
	}

	return tim;
}

//tworzy strukture danych probkowania
Probkowanie createProbkowanie()
{
	Probkowanie probkowanie;

	std::cout << "OKRESL PROBKOWANIE" << std::endl << std::endl;

	probkowanie.czasProbki = getCzasProbki();
	probkowanie.iloscProbek = getIloscProbek();

	std::cin.ignore();

	return probkowanie;
}

//tworzy grzejnik
Grzejnik* createGrzejnik()
{
	std::string smoc;
	float moc;

	std::cout << "OKRESL PARAMTERY GRZEJNIKA" << std::endl << std::endl;
	std::cout << "Podaj moc nominalna grzejnika w Watach (np. 1000.0): ";
	std::cin >> smoc;

	moc = fabs(std::stof(smoc));

	std::cin.ignore();

	return new Grzejnik(moc);
}

//tworzy regulator
Regulator* createRegulator(Pomieszczenie* pomieszczenie)
{
	std::string temps;
	float temp;
	char input;

	std::cout << "OKRESL PARAMETRY REGULACJI" << std::endl << std::endl;
	std::cout << "Wprowadz oczekiwana temperature pomieszczenia w stopniach Celsjusza (np. 20.5): ";
	std::cin >> temps;

	temp = std::stof(temps);

	while (true)
	{
		std::cout << std::endl << "Wybierz typ regulatora" << std::endl;
		std::cout << "Regulator PID [wprowadz P]" << std::endl;
		std::cout << "Regulator BB [wprowadz B]" << std::endl;
		std::cin >> input;

		if (input == 'p' || input == 'P')
		{
			std::string sKp, sKd, sKi;
			float Kp, Kd, Ki;

			std::cout << std::endl << "Okresl parametry regulatora PID" << std::endl;
			std::cout << "Wprowadz wartosc czlonu proporcjonalnego (np. 1.2): ";
			std::cin >> sKp;
			std::cout << "Wprowadz wartosc czlonu calkujacego (np. 1.2): ";
			std::cin >> sKd;
			std::cout << "Wprowadz wartosc czlonu rozniczkujacego (np. 1.2): ";
			std::cin >> sKi;

			Kp = fabs(std::stof(sKp));
			Kd = fabs(std::stof(sKd));
			Ki = fabs(std::stof(sKi));

			Regulator* regulator = new PID_Regulator(Kp, Kd, Ki);
			regulator->setPomieszczenie(pomieszczenie);
			regulator->setTempOczekiwana(temp);
			std::cin.ignore();
			return regulator;
		}
		else if (input == 'b' || input == 'B')
		{
			Regulator* regulator = new BB_Regulator();
			regulator->setPomieszczenie(pomieszczenie);
			regulator->setTempOczekiwana(temp);
			std::cin.ignore();
			return regulator;
		}
		else
		{
			std::cout << "Nie ma takiej opcji :/";
		}
	}
}

//czeka na enter od uzytkownika i czysci konsole
void czekaj_i_czysc()
{
	std::cout << "Wcisnij [Enter], aby kontynuowac";
	std::cin.get();
	system("CLS");
}

//wita uzytkownika
void witam()
{
	std::cout << "Witamy w symulacji" << std::endl << std::endl;
	czekaj_i_czysc();
}

//informuje o gotowosci symulacji
void gotowy()
{
	std::cout << "SYMULACJA UTWORZONA POMYSLNIE" << std::endl << std::endl;
	czekaj_i_czysc();
}

//zegna uzytkownika
void zegnam()
{
	std::cout << std::endl << "+++ Symulacja zakonczona, raport wygenerowano +++" << std::endl << std::endl;
	czekaj_i_czysc();
}

//czysci pamiec po grzejnik, regulator i pomieszczenie
void deleteGRP(Grzejnik* grzejnik, Regulator* regulator, Pomieszczenie* pomieszczenie)
{
	if (grzejnik != 0)
	{
		delete grzejnik;
	}
	if (regulator != 0)
	{
		delete regulator;
	}
	if (pomieszczenie != 0)
	{
		delete pomieszczenie;
	}
}

//czysci pamiec po symulacja, grzejnik, regulator i pomieszczenie
void deleteWszystko(Symulacja* symulacja, Grzejnik* grzejnik, Regulator* regulator, Pomieszczenie* pomieszczenie)
{
	if(symulacja != 0)
	{
		delete symulacja;
	}
	if (grzejnik != 0)
	{
		delete grzejnik;
	}
	if (regulator != 0)
	{
		delete regulator;
	}
	if (pomieszczenie != 0)
	{
		delete pomieszczenie;
	}
}

//funkcja glowna programu
int main()
{
	Probkowanie probkowanie;
	
	witam();

	Pomieszczenie* pomieszczenie = createPomieszczenie();
	czekaj_i_czysc();

	Regulator* regulator = 0;
	try {
		regulator = createRegulator(pomieszczenie);
	}
	catch (BrakPomieszczenia brakPomieszczenia)
	{
		delete pomieszczenie;
		std::cout << "Brak pomieszczenia!";
		return 1;
	}
	czekaj_i_czysc();

	Grzejnik* grzejnik = createGrzejnik();
	czekaj_i_czysc();

	Symulacja* symulacja = 0;
	try {
		symulacja = new Symulacja(pomieszczenie, grzejnik, regulator);
	}
	catch (BrakGrzejnika brakGrzejnika)
	{
		deleteGRP(grzejnik, regulator, pomieszczenie);
		std::cout << "Brak grzejnika!";
		return 1;
	}
	catch (BrakRegulatora brakRegulatora)
	{
		deleteGRP(grzejnik, regulator, pomieszczenie);
		std::cout << "Brak regulatora!";
		return 1;
	}

	probkowanie = createProbkowanie();
	czekaj_i_czysc();

	gotowy();

	symulacja->przebieg(probkowanie.iloscProbek, probkowanie.czasProbki);

	zegnam();

	deleteWszystko(symulacja, grzejnik, regulator, pomieszczenie);

	return 0;
}