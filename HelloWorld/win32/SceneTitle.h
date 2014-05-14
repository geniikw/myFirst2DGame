#include"cocos2d.h"

using namespace cocos2d;


class SceneTitle : public CCLayer
{

private:
	CCSprite *m_pTitle;
	CCSprite *m_pIllust;
	CCSprite *m_pBack;
	CCSprite *m_pString;
	CCLayerColor *m_pShadow;

private:

	int m_iStep;
	float m_fTitleOpasity;
	float m_iOffsetIllust;
	float m_iOffsetBG;

	int m_iGoalOffsetBG;
	int m_fLayerColor;

public:
	SceneTitle();
	static CCScene* scene();
	LAYER_NODE_FUNC(SceneTitle)
	bool init();
	void tick(ccTime dt);
};