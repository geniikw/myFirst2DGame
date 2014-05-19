#include"Matrix3x3.h"

Matrix3x3::Matrix3x3()
{
	//3x3 단위행렬로 초기화.
	m_row[0].x = 1;
	m_row[1].y = 1;
	m_row[2].z = 1;
}
Matrix3x3::Matrix3x3(CG3Point row1, CG3Point row2, CG3Point row3)
{
	m_row[0] = row1;
	m_row[1] = row2;
	m_row[2] = row3;
}

Matrix3x3::Matrix3x3(float aa, float ab, float ac, 
					 float ba, float bb, float bc, 
					 float ca, float cb, float cc)
{
	m_row[0].x = aa;
	m_row[0].y = ab;
	m_row[0].z = ac;

	m_row[1].x = ba;
	m_row[1].y = bb;
	m_row[1].z = bc;

	m_row[2].x = ca;
	m_row[2].y = cb;
	m_row[2].z = cc;

}