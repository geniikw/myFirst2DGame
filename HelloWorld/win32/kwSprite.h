#pragma once
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;

#include"myUnitHeader.h"
//일단 parents pointer를 가지고 있자...
class kwOrder;

typedef enum CharacterTag{
	CT_NOTHING,
	CT_HERO = 1,
	CT_ENERMY = 2,
	CT_OBJECT = 4,
	CT_UI = 8
} CT;


class kwSprite : public CCSprite
{//object-c 형식(no 생성자)

protected:
	//위치정보 넓이 높이 원형 네모 등의 종류 그리는 것에 관한 정보를 담고 잇는 클라스
	//현재 문제는 거의 모든 기능을 형태가 큐브인 것으로 상정하고 쓰고 있음...
	MYUnit *m_pPosData;
	int  m_iTag;		//원래 여기다가 안쓸려고 했던거 같은데...
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

	//option 값에 1을 주면 z가 0.f인 xy 좌표를 반환
	CG3Point get3DPosition(int option = 0) const;
	CG3Point get3DRightSide(int option =0 ) const;
	CG3Point get3DLeftSide(int option  = 0) const;
	CGPoint getDisplayPosition(){ return m_pPosData->getDisplayPosition(); }
	CG3Point getInsideRandPosition();


	void addPosition(const CG3Point &pos);
	bool AABBCheck(const kwSprite &target) const;

	//override CCSprite::draw();
	void draw();

	//render get /sset 사실상 쓰면 안됨... debug용
	void setRender(bool b){ m_bRender = b; }
	bool getRender(){ return m_bRender; }

public:/// FUNCTION FOR LOADING ANIMATION RECOURCE ///
	void setResourceWithString(string resName);

};

CG3Point operator>>(const kwSprite& s, const kwSprite &dest);