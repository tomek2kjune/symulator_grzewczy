#pragma once
#include "Regulator.h"

class BB_Regulator : public Regulator {
public:
	virtual float steruj(float _dt); //zwraca poziom mocy grzejnika
};
