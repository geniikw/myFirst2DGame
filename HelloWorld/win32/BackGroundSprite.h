#pragma once
#include"cocos2d.h"
using namespace cocos2d;

//my class include
#include"kwSprite.h"
#include<vector>
#include<memory>
using namespace std;

#include"kwController.h"
#include"Battle_ATB.h"
class Battle_Unit;
class Battle_Cursor;
class Battle_AttackBox;
class kwMsg_Action;
class Battle_Portrait;
const int g_MaxAttackBox = 20;

/* 
이 객체에 battle_unit class를 addchild하면
battle_unit이 가지고있는 tag를 판별하여 각각의
list에 유닛을 넣는다. 맵이란 객체지만 전체적으로 보면
전투에 관련된 일을 처리하는 허브역활을 한다.
ex)충돌처리, 데미지박스관리, 등등...
*/

enum BattleTurnEnum
{
	BT_NOHING,
	BT_HERO,
	BT_ENERMY
};

class BackGroundSprite : public kwSprite
{

	int					m_iBattleTurn;

	void AttackControll(KeySet key);
	void DefenceControll(KeySet key);

	Battle_Portrait		*m_pPortrait[MAX_HERO_COUNT];
	Battle_ATB			m_ATBHero;
	Battle_ATB			m_ATBEnermy;

	float				m_fHeroATBFacter;
	float				m_fEnermyATBFacter;


private:

	CCLayerColor		*m_pDeepDark;

	CCSprite			*m_pSky;

	//debug
	CCSprite	*m_pWall;
	CG3Point	m_DebugPos;

private:

	Battle_Unit *m_pControl[4];  ///미사용 아직
	CCSprite	*m_pRender;
public:
	CCSprite*	getRender()const{ return m_pRender; }

protected:
	KwController		m_ctrl;
	Battle_Cursor		*m_pCursor;
	int					m_iCursorIndex;

	int					m_iAttackBoxIndex;
	Battle_AttackBox	*m_pAttackBoxArray;//어택박스를 동적으로 할당함.
protected:
	//충돌체크시 구분하기 위한 리스트벡터... tag를 비교해서 따로 넣음...
	vector<Battle_Unit*>	m_ObjectArray;
	vector<Battle_Unit*>	m_HeroArray;
	vector<Battle_Unit*>	m_EnermyArray;
	
	//debug code..
	vector<CCLabelBMFont*>	m_HeroLabelArray;
public:
	//Collision manager의 역활을 수행함...
	//인자의 스프라이트가 가진 정보랑 비교해서 충돌되었으면 충돌 >_<
	~BackGroundSprite();

	bool isCollision(Battle_Unit *target, int tag);
	bool isCollision(My3DCube *pos, int tag);

	//target이 vector만큼 이동하고 싶다면 이 함수로 충돌을 검사해야함?
	CG3Point moveRayCast(My3DCube target, const CG3Point &vector, int tag);
	kwSprite* makeObject(int tag);

public:
	bool init(float w, float h, float rate);
	void tick(ccTime dt);
	void addChild(Battle_Unit* child);
	void addChild(Battle_AttackBox *child);
	void addChild(kwSprite* child);
	Battle_Unit* getCurrentTargetPointer();  //Battle_Cursor에 접근하는 메소드
	
	vector<Battle_Unit*>* getArrayPointerByTag(int tag);

	void requestUseAttackBox(shared_ptr<kwMsg_Action> msg, Battle_Unit*owner);
	//들어가야 될 정보는 다음과 같음.
	/*
	orderAttack이 어택박스를 맵에 요청하는 구조...흠 뭔가 좀 구려...

	공격박스의 크기 
	*/

	void setDeepDark(float op){ m_pDeepDark->setOpacity(op); }

private:
	inline void ctrlFunc(ccTime dt);

	void doATB(ccTime dt);

};