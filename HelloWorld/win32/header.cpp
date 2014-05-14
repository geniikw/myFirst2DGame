#include"header.h"
using namespace cocos2d;
char * wtoa(wchar_t* str)
{
	//반환할 char* 변수 선언
	char* pStr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}

std::string wstring2string(std::wstring wstr) {
	std::string str(wstr.length(), ' ');
	copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}

std::wstring string2wstring(std::string str) {
	std::wstring wstr(str.length(), L' ');
	copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

CG3Point getEnermyPositionByIndex(int index)
{
	return CG3Point(350 + (index % 28 * 10), 30 + (index / 28) * 6, 0);
}

cInt combineInt(int count, ...)
{
	va_list p;
	va_start(p, count);

	cInt res = 0;
	int temp;
	for (int n = 0; n < count; n++ )
	{
		temp = va_arg(p, int);
		
		res = res | (1 << (temp - 1));
	}

	return res;
}
bool analyzeCInt(cInt value, int number)
{
	return value & (1 << number - 1);
}
cInt setAbit(cInt x, int n, int b)
{	//인터넷에서 복붙함 ㅇㅇ;
	if (b == 1)
		return (cInt)(x | (1 << n - 1));

	return (cInt)(x & (~(1 << n - 1)));
}


const CGPoint operator+(const CGPoint &rs, const CGPoint &ls)
{
	CGPoint res;
	res.x = rs.x + ls.x;
	res.y = rs.y + ls.y;
	return res;
}

const CGPoint operator-(const CGPoint &rs, const CGPoint &ls)
{
	CGPoint res;
	res.x = rs.x - ls.x;
	res.y = rs.y - ls.y;
	return res;
}

const CGPoint operator*(const CGPoint &rs, const float &ls)
{
	CGPoint res;
	res.x = rs.x * ls;
	res.y = rs.y * ls;
	return res;
}

const CGPoint operator/(const CGPoint &rs, const float &ls)
{
	CGPoint res;
	res.x = rs.x / ls;
	res.y = rs.y / ls;
	return res;
}

const CGPoint getMidPoint(const CGPoint &pos1, const CGPoint &pos2, const float ratio)
{
	CGPoint dif = pos1 - pos2;
	return  pos1 + dif * ratio;
}
