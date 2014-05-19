#pragma once

#include"Point.h" 
using namespace std;

class Matrix3x3
{
	CG3Point m_row[3];
public:
	Matrix3x3();
	Matrix3x3(CG3Point, CG3Point, CG3Point);
	Matrix3x3(float, float, float, float, float, float, float, float, float);
};