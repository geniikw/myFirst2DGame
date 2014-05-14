#pragma once
#include"kwController.h"

#include"header_Unit.h"
#include"Action_Card.h"
#include<list>
using namespace std;

//이 유닛을 어떻게 조립하는 것에 대하여
//hero도 되고 enermy도 되게 만들자.

const int MAX_CARD_SLOT = 4;

class BackGroundSprite;
class Battle_AttackBox; //중복타격을 방지...
class kwMoving;

struct st_AB
{
	Battle_AttackBox *pAB;
	float			 remain;
};

class Battle_Unit : public kwSprite , 
	public Status, public Animation, public Shadow
{
//	friend kwOrderMoveToPoint;	//움직이는 명령은 battle unit을 이동시킴
								//kwOrderAttack같은 명령은 friend 시킬 필요가 없음.
protected:
	BackGroundSprite *m_pMap;   //add차일드 될때 add되는 맵의 정보를 가져옴
	CG3Point		  m_StartPosition;
	int				  m_iActionCount;  //이 수에 해당하는 행동을 취함.
public:
	int getActionCount(){ return m_iActionCount;}
	void setActionCount(int ac){ m_iActionCount = ac; }

protected:
	list<Action_Card>	m_listCard[MAX_CARD_SLOT];	
	list<kwOrder*> m_listOrder;	//order 명령 큐
	kwOrder*	m_pCurOrder;	//실행중인 명령
	kwMoving*	m_pMoving;		//실행중인 이동.

public:
	void doAction();

protected:						//데미지 중복방지를 위해 저장함
	list<st_AB*> m_listABPointer;

public:
	bool init();
	void damaged(Battle_AttackBox* box);
	void damaged(CG3Point force, int damage);

	bool checkAttackBox(Battle_AttackBox* box);


public:
	Battle_Unit();
	~Battle_Unit();
	void setParentMap(BackGroundSprite * pMap){ m_pMap = pMap; }
	BackGroundSprite* getParentMap() const{ return m_pMap; }
	void doKeySet(const KeySet &set);
	void initPosition(const CG3Point &pos); //처음 생성될때 사용하는 위치 지정 함수
	CG3Point getinitPosition(){ return m_StartPosition; }
	void setMoving(kwMoving* moving){ m_pMoving = moving; }

	void addOrder(kwOrder* order);
	void addOrder(kwOrderHit* order);

	void tick(ccTime dt);
	void doOrder(ccTime dt);
protected:
	//kwShadow의 추상함수
	virtual CCSpriteFrame* getOwnerCurrentFrame(); //현재 프레임을 얻는 함수
	virtual BackGroundSprite*	getBackGround();		  //getparent()를 넣으면 됨
	virtual CCSprite* getOwner(){return this;}			  //this 를 리턴하면 됨.
	virtual void doKwShadowInTick();
protected:
	//tick 내부에서 기능별 구분을 위한 함수들
	virtual void doAni(ccTime dt);
	void doAB(ccTime dt);
	
protected:

	//이걸로 케릭터 데이터를 접근하자...
	int	m_iCharacterName; //초상화, 일러 등등 관련
	
public:
	void setCharacterName(int CN) { m_iCharacterName = CN; }
	int getCharacterName(){ return m_iCharacterName; }

	virtual void doCard(const Action_Card &card);


public:

	void turnStart();
	void turnEnd();

};