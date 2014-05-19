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
�� ��ü�� battle_unit class�� addchild�ϸ�
battle_unit�� �������ִ� tag�� �Ǻ��Ͽ� ������
list�� ������ �ִ´�. ���̶� ��ü���� ��ü������ ����
������ ���õ� ���� ó���ϴ� ��꿪Ȱ�� �Ѵ�.
ex)�浹ó��, �������ڽ�����, ���...
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

	Battle_Unit *m_pControl[4];  ///�̻�� ����
	CCSprite	*m_pRender;
public:
	CCSprite*	getRender()const{ return m_pRender; }

protected:
	KwController		m_ctrl;
	Battle_Cursor		*m_pCursor;
	int					m_iCursorIndex;

	int					m_iAttackBoxIndex;
	Battle_AttackBox	*m_pAttackBoxArray;//���ùڽ��� �������� �Ҵ���.
protected:
	//�浹üũ�� �����ϱ� ���� ����Ʈ����... tag�� ���ؼ� ���� ����...
	vector<Battle_Unit*>	m_ObjectArray;
	vector<Battle_Unit*>	m_HeroArray;
	vector<Battle_Unit*>	m_EnermyArray;
	
	//debug code..
	vector<CCLabelBMFont*>	m_HeroLabelArray;
public:
	//Collision manager�� ��Ȱ�� ������...
	//������ ��������Ʈ�� ���� ������ ���ؼ� �浹�Ǿ����� �浹 >_<
	~BackGroundSprite();

	bool isCollision(Battle_Unit *target, int tag);
	bool isCollision(My3DCube *pos, int tag);

	//target�� vector��ŭ �̵��ϰ� �ʹٸ� �� �Լ��� �浹�� �˻��ؾ���?
	CG3Point moveRayCast(My3DCube target, const CG3Point &vector, int tag);
	kwSprite* makeObject(int tag);

public:
	bool init(float w, float h, float rate);
	void tick(ccTime dt);
	void addChild(Battle_Unit* child);
	void addChild(Battle_AttackBox *child);
	void addChild(kwSprite* child);
	Battle_Unit* getCurrentTargetPointer();  //Battle_Cursor�� �����ϴ� �޼ҵ�
	
	vector<Battle_Unit*>* getArrayPointerByTag(int tag);

	void requestUseAttackBox(shared_ptr<kwMsg_Action> msg, Battle_Unit*owner);
	//���� �� ������ ������ ����.
	/*
	orderAttack�� ���ùڽ��� �ʿ� ��û�ϴ� ����...�� ���� �� ����...

	���ݹڽ��� ũ�� 
	*/

	void setDeepDark(float op){ m_pDeepDark->setOpacity(op); }

private:
	inline void ctrlFunc(ccTime dt);

	void doATB(ccTime dt);

};