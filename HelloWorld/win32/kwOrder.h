#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"kwSprite.h"

//명령 객체 이것을 받은 BG는 해당하는 명령을 실행한다....
//부모 클레스임...

enum orderProcess
{
	OP_STANDBY,
	OP_EXECUTING,
	OP_END	//안쓸듯...? 
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
	
	orderProcess m_iProcess;	//행위상태
	Battle_Unit *m_pOwner;		//행위객체
public:
	kwOrder(Battle_Unit *owner);

	//실행하는 함수 이렇게 하고 false를 리턴하면 사라짐...
    virtual	bool execute(ccTime dt) = 0;

};
