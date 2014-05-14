#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class SceneLoading : public CCLayer
{
private:
	char buf[32];
	float m_fLoadingCooltime;

private:
	float m_fLoadingTime;
	float m_fX;
	GLubyte m_r;
	GLubyte m_g;
	GLubyte m_b;

	bool m_bR;
	bool m_bG;
	bool m_bB;

	CCSprite *m_pLoadingText;
	CCSprite *m_pLoadingImage;

	CCLabelBMFont *m_pLoadingFileText;

public:
	static CCScene* scene();
	LAYER_NODE_FUNC(SceneLoading)

	bool init();
	void tick(ccTime dt);
	void tick2(ccTime dt);

	void LoadingAnimation(ccTime dt);

};