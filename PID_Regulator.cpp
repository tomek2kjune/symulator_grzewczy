#include "PID_Regulator.h"

PID_Regulator::PID_Regulator(float _Kp, float _Ki, float _Kd)
	: Kp(_Kp)
	, Ki(_Ki)
	, Kd(_Kd)
{}

float PID_Regulator::steruj(float _dt)
{
	float tempAktualna = pomieszczenie->getTemperatura();
	float uchyb, P, I, D, zmiana, wyjscie;
	
	uchyb = tempOczekiwana - tempAktualna;

	P = Kp * uchyb;

	calka += uchyb * _dt;
	I = Ki * calka;

	zmiana = (uchyb - preUchyb) / _dt;
	D = Kd * zmiana;

	wyjscie = P + I + D;

	if (wyjscie < 0.0f)
	{
		wyjscie = 0.0f;
	}
	else if (wyjscie > 1.0f)
	{
		wyjscie = 1.0f;
	}

	return wyjscie;
}