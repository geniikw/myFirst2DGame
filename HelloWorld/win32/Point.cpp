#include"Point.h"
#include"header.h"

#include"Matrix3x3.h"

void CG3Point::rotationAxis(const CG3Point &axis, const float &Radian)
{
	// make arbitrary rotation matrix 
	float a = axis.x;
	float b = axis.y;
	float c = axis.z;
	float cosTheta = cosf(Radian);
	float sinTheta = sinf(Radian);

	Matrix3x3 rotationMatrix(
		a * a * (1 - cosTheta) + cosTheta,
		a * b * (1 - cosTheta) - c * sinTheta,
		a * c * (1 - cosTheta) + b * sinTheta,

		a * b * (1 - cosTheta) + c * sinTheta,
		b * b * (1 - cosTheta) + cosTheta,
		b * c * (1 - cosTheta) - a * sinTheta,

		a * c * (1 - cosTheta) - b * sinTheta,
		b * c * (1 - cosTheta) + a * sinTheta,
		c * c * (1 - cosTheta) + cosTheta);
}

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
