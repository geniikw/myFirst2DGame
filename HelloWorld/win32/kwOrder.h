#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"kwSprite.h"

//��� ��ü �̰��� ���� BG�� �ش��ϴ� ����� �����Ѵ�....
//�θ� Ŭ������...

enum orderProcess
{
	OP_STANDBY,
	OP_EXECUTING,
	OP_END	//�Ⱦ���...? 
};

enum orderTag
{
	NOTHING,
	OT_MOVE,
	OT_ATTACK,
	OT_HIT,
	OT_WAIT
};

class Battle_Unit;
class kwOrder
{
friend bool operator==(const kwOrder& ls, const kwOrder &rs);
friend bool operator==(const kwOrder& ls, const CAT &rs);
protected:
	
	orderProcess m_iProcess;	//��������
	Battle_Unit *m_pOwner;		//������ü
public:
	kwOrder(Battle_Unit *owner);

	//�����ϴ� �Լ� �̷��� �ϰ� false�� �����ϸ� �����...
    virtual	bool execute(ccTime dt) = 0;

};
