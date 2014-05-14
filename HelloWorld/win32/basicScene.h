#include"cocos2d.h"

using namespace cocos2d;

class basicScene : public CCLayer
{

public:
	static CCScene* scene();

	LAYER_NODE_FUNC(basicScene)

	bool init();
	void tick(ccTime dt);
};