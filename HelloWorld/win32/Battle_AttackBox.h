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
BackGroundSprite�� �ʱ�ȭ �ɶ� has����� ���� �ʱ�ȭ �ȴ�.
*/
class Battle_AttackBox: public kwSprite, Animation
{
	bool			  m_bIsUsed;
	float			  m_fRemainTime;
	BackGroundSprite *m_pMap;
	shared_ptr<kwMsg_Action> m_pMsgAction;
	int				  m_iHitedNumber;//���ߵ� ���� ��
	kwMoving		  *m_pMoving;  //�̰��� ����Ű�� �Ϳ� ���� �ൿ�� �Ѵ�.

public:

	Battle_AttackBox();
	~Battle_AttackBox();
	
	//get�Լ�
	bool getIsUsed(){ return m_bIsUsed; }
	shared_ptr<kwMsg_Action> getMsgAction(){ return m_pMsgAction; }

	//init�Լ�
	void setParentsMap(BackGroundSprite* map);
	CCSprite* getOwner(){ return this; }

	//tick�Լ�
	void tick(ccTime dt);
	virtual void doAni(ccTime dt);

	//setup �Լ�
	void setUp(shared_ptr<kwMsg_Action> msg);
	void setDown();
};