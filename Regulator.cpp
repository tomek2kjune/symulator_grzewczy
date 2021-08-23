#include "Regulator.h"
#include "BrakPomieszczenia.h"

void Regulator::setPomieszczenie(Pomieszczenie * _pomieszczenie)
{
	pomieszczenie = _pomieszczenie;
	if (_pomieszczenie == 0)
	{
		BrakPomieszczenia brakPomieszczenia;
		throw brakPomieszczenia;
	}
}

void Regulator::setTempOczekiwana(float _tempOczekiwana)
{
	tempOczekiwana = _tempOczekiwana;
}
