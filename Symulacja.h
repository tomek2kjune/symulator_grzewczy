#pragma once
#include "Pomieszczenie.h"
#include "Grzejnik.h"
#include "Regulator.h"
#include "vector"

class Symulacja {
public:
	Symulacja(Pomieszczenie* _pomieszczenie, Grzejnik* _grzejnik, Regulator* _regulator); //konstruktor
	void przebieg(int iteracje, float t); //przeprowadza symulacje

private:
	void zapiszPomiar(float moment); //przechwytuje pomiar proby do vector'ow
	void iteracja(float dt); //przeprowadza probke symulacji
	Regulator* regulator; //regulator
	Grzejnik* grzejnik; //grzejnik
	Pomieszczenie* pomieszczenie; //pomieszczenie
	void zapiszPlik(); //zapisuje pomiary do pliku
	std::vector<float> czas; //kontener na czas
	std::vector<float> temp; //kontener na temperature
	std::vector<float> moc; //kontener na moc
};
