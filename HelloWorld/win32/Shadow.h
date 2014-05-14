#pragma once
#include"cocos2d.h"
using namespace cocos2d;

/*
사용법 CCSprite의 자식 객체에서 kwShadow를 같이 상속 받는다.
ex ) class Object_Unit : public CCSprite, public kwShadow;

addChild 된 객체에서 makeShadow(float anchor)를 실행한다.
tick에서 doKwShadowInTick를 추가한다.
*/

class BackGroundSprite;
class Shadow
{

protected:
	CCSprite	   *m_pShadow;
	float			m_fAngle;
	float			m_fYScale;

public:

	Shadow();
	~Shadow();
	bool makeShadow(float anchor);
	//this func must be in Sprite's tick func

	void setShadowIsVisible(bool);

	virtual void doKwShadowInTick() = 0;
	virtual CCSpriteFrame* getOwnerCurrentFrame() = 0; //현재 프레임을 얻는 함수
	virtual BackGroundSprite*	getBackGround() = 0;		  //getparent()를 넣으면 됨
	virtual CCNode* getOwner() = 0;				  //this 를 리턴하면 됨.
};
