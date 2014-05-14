#pragma once
#include"kwSprite.h"
#include"Point.h"
#include"Animation.h"
#include<memory>
using namespace cocos2d;

class BackGroundSprite;
class kwMsg_Action;
class Battle_Damage;
class kwMoving;

/*
BackGroundSprite가 초기화 될때 has관계로 같이 초기화 된다.
*/
class Battle_AttackBox: public kwSprite, Animation
{
	bool			  m_bIsUsed;
	float			  m_fRemainTime;
	BackGroundSprite *m_pMap;
	shared_ptr<kwMsg_Action> m_pMsgAction;
	int				  m_iHitedNumber;//적중된 적의 수
	kwMoving		  *m_pMoving;  //이것이 가리키는 것에 대한 행동을 한다.

public:

	Battle_AttackBox();
	~Battle_AttackBox();
	
	//get함수
	bool getIsUsed(){ return m_bIsUsed; }
	shared_ptr<kwMsg_Action> getMsgAction(){ return m_pMsgAction; }

	//init함수
	void setParentsMap(BackGroundSprite* map);
	CCSprite* getOwner(){ return this; }

	//tick함수
	void tick(ccTime dt);
	virtual void doAni(ccTime dt);

	//setup 함수
	void setUp(shared_ptr<kwMsg_Action> msg);
	void setDown();
};