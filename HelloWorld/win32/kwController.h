#pragma once

#include<Windows.h>
#include<list>
using namespace std;

typedef unsigned KeySet;
/*

0.w
1.a
2.s
3.d
4.right
5.left
6.up
7.down
8.f5
9.f6
10.f7
11.f8
12.t

*/

enum KW_KEY
{
	KK_W = 0,
	KK_A,
	KK_S,
	KK_D,
	KK_RIGHT,
	KK_LEFT,
	KK_UP,
	KK_DOWN,
	KK_F5,
	KK_F6,
	KK_F7,
	KK_F8,
	KK_T
};

const float keyCoolTime = 0.5f;

class KwController
{
	KeySet m_KeySet;

	bool m_bWKeyPress;
	bool m_bAKeyPress;
	bool m_bSKeyPress;
	bool m_bDKeyPress;

	bool m_bRKeyPress;
	bool m_bLKeyPress;
	bool m_bUKeyPress;
	bool m_bDoKeyPress;

	bool m_bFunc5Press;
	bool m_bFunc6Press;
	bool m_bFunc7Press;
	bool m_bFunc8Press;

	bool m_bTKeyPress;

public:
	KwController();
	void getAsync();
	KeySet getKeySet(){ return m_KeySet; }
};