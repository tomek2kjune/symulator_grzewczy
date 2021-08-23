#include "BB_Regulator.h"

float BB_Regulator::steruj(float _dt)
{
	float tempAktualna = pomieszczenie->getTemperatura();

	if (tempAktualna < tempOczekiwana)
	{
		return 1.0f;
	}
	else if (tempAktualna >= tempOczekiwana)
	{
		return 0.0f;
	}
}
