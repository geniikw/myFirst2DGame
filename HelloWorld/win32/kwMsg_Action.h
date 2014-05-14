#pragma once
#include"Point.h"
#include<memory>
#include"header.h"

class Battle_Unit;
class kwMoving;

class kwMsg_Action
{
public:
	//목표타겟... 이동할때도 필요하긴 하다..?
	//어디로 이동 하는가? 이동할 때 필요한 정보는? 어떻게 이동하는가?
	//내 생각에는 백터를 잘 활용해야 될 것 같다...
	//다시 바꾸자 아무리 생각해도 너무 무리하는것 같다. 현재 상태를 유지함...
	//이동,대기,명령등을 유지하고 바꿀려면 이거 자체를 개조하는 식으로 하자
	
	//공격할 타겟의 포인터 여기서 공격대상의 tag, 위치 등을 참조한다.	

	//animation관련 정보.
	
	kwMoving                *m_pOwnerMoving;
		
	//타겟이 존재한다면 이후 밑에 값을 넣어주고 없다면 그대로 놔둔다. 
	Battle_Unit				*m_pTarget;
	int						 m_iDamage;				
	
	//비트연산으로 한다 예를들어 4,5 프레임에서 각각 어택박스를 생성한다면 ..00011000 이런식으로 ABFrame값을 설정한다.
	//만드는 함수는 
	cInt					 m_iABFrame;
	float					 m_fABRemainTime;
	kwMoving				*m_pABMoving;

	CG3Point				 m_vctABforce;
	CG3Point				 m_sizeAB;
	CG3Point				 m_offsetAB;

public:
	kwMsg_Action(
		kwMoving* pOwnerMoving = NULL,
		Battle_Unit* pTarget = NULL,
		int damage = 0 ,
		int abFrame = 0,
		float abRemain = 0.f,
		kwMoving* abMoving = NULL,
		CG3Point vct   = CG3PointZero,
		CG3Point abSize = CG3PointZero,
		CG3Point offset = CG3PointZero);

	~kwMsg_Action();

};