#pragma once
#include"Point.h"
#include"Matrix3x3.h"

CG3Point operator*(const Matrix3x3 &mat, const CG3Point &vect);
