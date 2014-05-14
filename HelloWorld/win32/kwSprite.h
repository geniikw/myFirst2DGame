#pragma once
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;

#include"myUnitHeader.h"
//�ϴ� parents pointer�� ������ ����...
class kwOrder;

typedef enum CharacterTag{
	CT_NOTHING,
	CT_HERO = 1,
	CT_ENERMY = 2,
	CT_OBJECT = 4,
	CT_UI = 8
} CT;


class kwSprite : public CCSprite
{//object-c ����(no ������)

protected:
	//��ġ���� ���� ���� ���� �׸� ���� ���� �׸��� �Ϳ� ���� ������ ��� �մ� Ŭ��
	//���� ������ ���� ��� ����� ���°� ť���� ������ �����ϰ� ���� ����...
	MYUnit *m_pPosData;
	int  m_iTag;		//���� ����ٰ� �Ⱦ����� �ߴ��� ������...
	bool m_bRender;

public:
	MYUnit* getPosData() const{ return m_pPosData; }
	void setPosData(MYUnit* pos){ m_pPosData = pos; }
	void reMakeCubeData(const CG3Point &shape);

public:
	int getTag(){ return m_iTag; }
	void setTag(int tag){ m_iTag = tag; }

public:
	bool init();
	bool init(const CG3Point &size);
	bool init(float x, float y, float z = 0.f); //init cube

	//bool init(float r);		//init ellipse
	virtual ~kwSprite();

	//fix position and scale with DrawData;
	void refreshPosition();

	virtual void setPosition(const CG3Point &pos);
	virtual void addChild(kwSprite *child);

	//my func;

	//option ���� 1�� �ָ� z�� 0.f�� xy ��ǥ�� ��ȯ
	CG3Point get3DPosition(int option = 0) const;
	CG3Point get3DRightSide(int option =0 ) const;
	CG3Point get3DLeftSide(int option  = 0) const;
	CGPoint getDisplayPosition(){ return m_pPosData->getDisplayPosition(); }
	CG3Point getInsideRandPosition();


	void addPosition(const CG3Point &pos);
	bool AABBCheck(const kwSprite &target) const;

	//override CCSprite::draw();
	void draw();

	//render get /sset ��ǻ� ���� �ȵ�... debug��
	void setRender(bool b){ m_bRender = b; }
	bool getRender(){ return m_bRender; }

public:/// FUNCTION FOR LOADING ANIMATION RECOURCE ///
	void setResourceWithString(string resName);

};

CG3Point operator>>(const kwSprite& s, const kwSprite &dest);