#pragma once
#include"cocos2d.h"
using namespace cocos2d;

/*
���� CCSprite�� �ڽ� ��ü���� kwShadow�� ���� ��� �޴´�.
ex ) class Object_Unit : public CCSprite, public kwShadow;

addChild �� ��ü���� makeShadow(float anchor)�� �����Ѵ�.
tick���� doKwShadowInTick�� �߰��Ѵ�.
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
	virtual CCSpriteFrame* getOwnerCurrentFrame() = 0; //���� �������� ��� �Լ�
	virtual BackGroundSprite*	getBackGround() = 0;		  //getparent()�� ������ ��
	virtual CCNode* getOwner() = 0;				  //this �� �����ϸ� ��.
};
