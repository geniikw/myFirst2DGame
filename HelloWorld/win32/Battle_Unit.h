#pragma once
#include"kwController.h"

#include"header_Unit.h"
#include"Action_Card.h"
#include<list>
using namespace std;

//�� ������ ��� �����ϴ� �Ϳ� ���Ͽ�
//hero�� �ǰ� enermy�� �ǰ� ������.

const int MAX_CARD_SLOT = 4;

class BackGroundSprite;
class Battle_AttackBox; //�ߺ�Ÿ���� ����...
class kwMoving;

struct st_AB
{
	Battle_AttackBox *pAB;
	float			 remain;
};

class Battle_Unit : public kwSprite , 
	public Status, public Animation, public Shadow
{
//	friend kwOrderMoveToPoint;	//�����̴� ����� battle unit�� �̵���Ŵ
								//kwOrderAttack���� ����� friend ��ų �ʿ䰡 ����.
protected:
	BackGroundSprite *m_pMap;   //add���ϵ� �ɶ� add�Ǵ� ���� ������ ������
	CG3Point		  m_StartPosition;
	int				  m_iActionCount;  //�� ���� �ش��ϴ� �ൿ�� ����.
public:
	int getActionCount(){ return m_iActionCount;}
	void setActionCount(int ac){ m_iActionCount = ac; }

protected:
	list<Action_Card>	m_listCard[MAX_CARD_SLOT];	
	list<kwOrder*> m_listOrder;	//order ��� ť
	kwOrder*	m_pCurOrder;	//�������� ���
	kwMoving*	m_pMoving;		//�������� �̵�.

public:
	void doAction();

protected:						//������ �ߺ������� ���� ������
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
	void initPosition(const CG3Point &pos); //ó�� �����ɶ� ����ϴ� ��ġ ���� �Լ�
	CG3Point getinitPosition(){ return m_StartPosition; }
	void setMoving(kwMoving* moving){ m_pMoving = moving; }

	void addOrder(kwOrder* order);
	void addOrder(kwOrderHit* order);

	void tick(ccTime dt);
	void doOrder(ccTime dt);
protected:
	//kwShadow�� �߻��Լ�
	virtual CCSpriteFrame* getOwnerCurrentFrame(); //���� �������� ��� �Լ�
	virtual BackGroundSprite*	getBackGround();		  //getparent()�� ������ ��
	virtual CCSprite* getOwner(){return this;}			  //this �� �����ϸ� ��.
	virtual void doKwShadowInTick();
protected:
	//tick ���ο��� ��ɺ� ������ ���� �Լ���
	virtual void doAni(ccTime dt);
	void doAB(ccTime dt);
	
protected:

	//�̰ɷ� �ɸ��� �����͸� ��������...
	int	m_iCharacterName; //�ʻ�ȭ, �Ϸ� ��� ����
	
public:
	void setCharacterName(int CN) { m_iCharacterName = CN; }
	int getCharacterName(){ return m_iCharacterName; }

	virtual void doCard(const Action_Card &card);


public:

	void turnStart();
	void turnEnd();

};