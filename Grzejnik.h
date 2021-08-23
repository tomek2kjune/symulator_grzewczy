#pragma once

class Grzejnik {
public:
	Grzejnik(const float _mocMax); //konstruktor
	float getMocAktualna() { return mocMax * poziomMocy; } //zwraca aktualna moc grzejnika
	void setPoziomMocy(float _poziomMocy); //ustawia poziom mocy

private:
	const float mocMax;
	float poziomMocy;
};