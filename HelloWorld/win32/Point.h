#pragma once

#include<math.h>
///자주쓰는 구조체인데 크기가 커서 이렇게 넣어놓음...

struct CG3Point
{
	float x;
	float y;
	float z;
public://내부에 정의부에 선언된 함수는 inline이래...

	CG3Point getXYPosition() const { CG3Point res = *this; res.z = 0; return res; }

	//백터로 사용되었을때 길이를 구함
	float getVectorLenght(){ return sqrtf(x*x + y*y + z*z); }
	CG3Point getUnitVector(){ return *this / getVectorLenght(); }

	CG3Point operator+=(const CG3Point &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	CG3Point operator/=(const CG3Point &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	CG3Point operator/(const float &value) const
	{
		CG3Point temp;
		temp.x = x / value;
		temp.y = y / value;
		temp.z = z / value;
		return temp;
	}
	CG3Point operator*(const float &value) const
	{
		CG3Point temp;
		temp.x = x * value;
		temp.y = y * value;
		temp.z = z * value;
		return temp;
	}

	const CG3Point& operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	const CG3Point operator+(const CG3Point &other) const
	{
		CG3Point temp;
		temp.x = x + other.x;
		temp.y = y + other.y;
		temp.z = z + other.z;
		return temp;
	}
	const CG3Point operator-(const CG3Point &other) const
	{
		CG3Point temp;
		temp.x = x - other.x;
		temp.y = y - other.y;
		temp.z = z - other.z;
		return temp;
	}
	const CG3Point operator*(const CG3Point &other) const
	{
		CG3Point temp;
		temp.x = x * other.x;
		temp.y = y * other.y;
		temp.z = z * other.z;
		return temp;
	}

	CG3Point()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
	CG3Point(float ix, float iy, float iz)
	{
		x = ix;
		y = iy;
		z = iz;
	}
};

//start에서 dest를 가리키는 단위백터 
CG3Point operator>>(const CG3Point &ls, const CG3Point &rs);

const CG3Point CG3PointZero = CG3Point(0.f, 0.f, 0.f);

struct CG3Cube
{
	CG3Point origin;
	CG3Point size;
};


float ccp3Distance(const CG3Point& pos1, const CG3Point& pos2);
