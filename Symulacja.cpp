#include "Symulacja.h"
#include "Pomieszczenie.h"
#include "BrakPomieszczenia.h"
#include "BrakGrzejnika.h"
#include "BrakRegulatora.h"
#include <iostream>
#include <string>
#include <fstream>

Symulacja::Symulacja(Pomieszczenie* _pomieszczenie, Grzejnik* _grzejnik, Regulator* _regulator)
{
	pomieszczenie = _pomieszczenie;
	grzejnik = _grzejnik;
	regulator = _regulator;
	if (_pomieszczenie == 0)
	{
		BrakPomieszczenia brakPomieszczenia;
		throw brakPomieszczenia;
	}
	else if (_grzejnik == 0)
	{
		BrakGrzejnika brakGrzejnika;
		throw brakGrzejnika;
	}
	else if (_regulator == 0)
	{
		BrakRegulatora brakRegulatora;
		throw brakRegulatora;
	}
}

void Symulacja::iteracja(float dt)
{
	pomieszczenie->aktualizuj(dt);
	grzejnik->setPoziomMocy(regulator->steruj(dt));
	pomieszczenie->dodajCieplo(grzejnik->getMocAktualna());
}

void Symulacja::przebieg(int iteracje, float dt)
{	
	for (int i = 1; i <= iteracje; i++)
	{
		iteracja(dt);
		std::cout << "Temperatura w chwili " << i*dt << ": " << pomieszczenie->getTemperatura() << std::endl;
		zapiszPomiar(i*dt);
	}
	zapiszPlik();
}

void Symulacja::zapiszPomiar(float moment)
{
	czas.push_back(moment);
	temp.push_back(pomieszczenie->getTemperatura());
	moc.push_back(grzejnik->getMocAktualna());
}

void Symulacja::zapiszPlik()
{
	std::ofstream raport("raport.csv");

	raport << "czas," << "temp," << "moc" << std::endl;

	for (int i = 0; i < czas.size(); i++)
	{
		raport << czas.at(i) << "," << temp.at(i) << "," << moc.at(i) << std::endl;
	}
	
	raport.close();
}

