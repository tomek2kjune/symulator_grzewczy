#pragma once
#include "Pomieszczenie.h"

class Regulator {
public:
	virtual float steruj(float _dt) = 0; //zwraca poziom mocy grzejnika
	void setPomieszczenie(Pomieszczenie* _pomieszczenie); //ustala pomieszczenie
	void setTempOczekiwana(float _tempOczekiwana); //ustala temperature oczekiwana

protected:
	float tempOczekiwana = 20.0f; //temperatura oczekiwana
	Pomieszczenie* pomieszczenie; //pomieszczenie
};
