#pragma once
#include "Regulator.h"

class PID_Regulator : public Regulator {
public:
	PID_Regulator(float _Kp, float _Ki, float _Kd); //konstruktor
	virtual float steruj(float _dt); //zwraca poziom mocy grzejnika

private:
	const float Kp; //czlon proporcjonalny
	const float Ki; //czlon calkujacy
	const float Kd; //czlon rozniczkujacy
	float preUchyb = 0; //poprzedni uchyb
	float calka = 0; //calka
};
