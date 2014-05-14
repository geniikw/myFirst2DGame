#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include"Point.h"

#include"cocos2d.h"
using namespace cocos2d;
//캐릭터의 데이터를 저장하는 클래스.
#include"Character_data.h"

const int screenHeight = 800;

//범용 define
#define errorBOX(msg) MessageBoxA(NULL, msg, "error", MB_OK)

//wchar_t 에서 char 로의 형변환 함수
char * wtoa(wchar_t* str);
std::string wstring2string(std::wstring wstr);
std::wstring string2wstring(std::string str);

//linear function; 대상이 -값이면... 답이 없나? tmin값도 넣어야 되나 고민중.
inline float linear(float min, float max, float &target, float tmax)
{
	return min + (max - min)*target / tmax;
}

inline float square(float value)
{
	return value * value;
} 

inline float CG3PointLenght(const CG3Point &point)
{
	return sqrtf(square(point.x) + square(point.y) + square(point.z));
}

//global values const

typedef unsigned int cInt; // 합치는 함수 combineInt(int,...), 분석하는 함수 analyzeCInd(cInd,int);,특정비트를 바꾸는 함수 setAbit

//count 는 가변인수의 갯수
cInt combineInt(int count, ...);
//분석할 자료, 순번  해당 순번의 bool
bool analyzeCInt(cInt value,int number );
//분석할 자료, 순번, 바꿀 값
cInt setAbit(cInt x, int n, int b);
/* BattleScene */

const CG3Point G_POSITION_HERO_START[4] = { 
CG3Point(160.f, 110.f, 0.f),
CG3Point(100.f, 70.f, 0.f),
CG3Point(160.f, 30.f, 0.f),
CG3Point(220.f, 70.f, 0.f)
};

const CG3Point G_POSITION_OBJECT_START[10] = {
	CG3Point(0.f, 0.f, 0.f),
	CG3Point(0.f, 40, 0.f),
	CG3Point(0.f, 80.f, 0.f),
	CG3Point(0.f, 120.f, 0.f), 
	CG3Point(0.f, 160.f, 0.f),
	CG3Point(800.f, 0.f, 0.f),
	CG3Point(800.f, 40.f, 0.f),
	CG3Point(800.f, 80.f, 0.f),
	CG3Point(800.f, 120.f, 0.f),
	CG3Point(800.f, 160.f, 0.f)
};

//640 x 160 맵에서 인덱스에 해당하는 적의 위치를 리턴한다.
CG3Point getEnermyPositionByIndex(int index);

/* enums.. */
enum SPD_RANK
{//수치는 이동거리를 나타냄...
	SR_E = 80,   //매우 느림
	SR_D = 100,   //느림
	SR_C = 120,   //평범
	SR_B = 140,	//약간 빠름
	SR_A = 200,	//빠름
	SR_S = 400,	//매우 빠름
	SR_SS = 900,	//눈에 보이지 않음
	SR_SSS = -1	//이형환위
};

/* is in kwSprite.. ref it; */

//typedef enum CharacterTag{
//	CT_NOTHING,
//	CT_HERO	= 1,
//	CT_ENERMY = 2,
//	CT_OBJECT = 4,
//	CT_UI = 8
//} CT;
//

const int MAX_CHARACTER_NUMBER = 15;
typedef enum CharacterName
{
	CN_NOTHING,
	CN_HERO_REIMU,
	CN_HERO_SAKUYA,
	CN_HERO_YOUMU,
	CN_HERO_MARISA,
	CN_HERO_ALICE,
	CN_HERO_REMILIA,
	CN_HERO_YUYUKO,
	CN_HERO_PATCHOULI,
	CN_HERO_YUKARI,
	CN_HERO_REISEN,
	CN_HERO_AYA,
	CN_HERO_SUIKA,
	CN_HERO_KOMACHI,
	CN_HERO_IKU,
	CN_HERO_TENCHI,
	CN_HERO_MEILING
} CN;

typedef enum BATTLE_EFFECT_LIST
{
	BE_HIT,
	BE_CUT
}BE;

const int MAX_CARD_NUMBER = 9;
typedef enum AC_CARD_LIST
{
	AC_NOHING,
	AC_ATTACK1,
	AC_ATTACK2,
	AC_ATTACK3,
	AC_ATTACK4,
	AC_ATTACK5,
	AC_MOVE,
	AC_BACKSTEP,
	AC_AVOID,
	AC_DEFENCE,
	AC_NOCARD_BACK
} AC;

typedef enum CharacterAnimationTag{
	CAT_STAND,  //일단 IDLE1 에 대응...
	CAT_WALK,
	CAT_RUN,
	CAT_BACK,
	CAT_ATTACK1,
	CAT_ATTACK2,
	CAT_ATTACK3,
	CAT_ATTACK4,
	CAT_ATTACK5,
	CAT_GUARD,
	CAT_HIT
} CAT;

enum ENUM_ZORDER
{
	EZ_BACK = -1000,
	EZ_FILED = 0,
	EZ_UI = 1000
};

const int		G_MAX_DIGIT = 4;
const int		MAX_HERO_COUNT = 4;
const float		G_GRAVITY_FACTOR = 100.f;

/* character size list */
const CG3Point g_LargeSize(50, 10, 120);
const CG3Point g_NormalSize(30, 5, 80);
const CG3Point g_SmallSize(25, 4, 50);
const CG3Point g_CubeSizeX10(10, 10, 10);
const CG3Point g_ZakuSize(200,15,400);
const CG3Point g_WoodStakeSize(30,40,150);

/* character list */
const Character_data g_Debug(0, "Debug", 100, 10, SR_SS, g_NormalSize);
const Character_data g_Reimu(1, "Reimu", 100, 10, SR_C, g_NormalSize);
const Character_data g_Marisa(2, "Marisa", 90, 8, SR_A, g_NormalSize);

/* enermy list */
const Character_data g_DebugEnermy(1000, "Debug", 100, 10, SR_SS, g_NormalSize);
const Character_data g_DebugBoss(1001, "DebugBoss", 100, 20, SR_C, g_LargeSize);
const Character_data g_DebugZaku(1002, "zaku", 100, 20, SR_C, g_ZakuSize);

/* Object list */
const Character_data g_WoodStake(2000, "WoodStake", 0, 0, SR_E, g_WoodStakeSize);

/* CGPoint oerator func */
const CGPoint operator+(const CGPoint &rs, const CGPoint &ls);
const CGPoint operator-(const CGPoint &rs, const CGPoint &ls);
const CGPoint operator*(const CGPoint &rs, const float &ls);
const CGPoint operator/(const CGPoint &rs, const float &ls);
const CGPoint getMidPoint(const CGPoint &pos1, const CGPoint &pos2, const float ratio = 0.5f);