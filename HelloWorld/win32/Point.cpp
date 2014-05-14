#include"Point.h"
#include"header.h"


float ccp3Distance(const CG3Point& pos1, const CG3Point& pos2)
{
	return	sqrtf(square(pos1.x - pos2.x) + square(pos1.y - pos2.y) + square(pos1.z - pos2.z));
}

CG3Point operator>>(const CG3Point &ls, const CG3Point &rs)
{
	CG3Point vect = rs - ls;
	vect = vect.getUnitVector();
	return vect;
}