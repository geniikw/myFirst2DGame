#pragma once
//#include"header.h"

#include"Object_Char.h"
#include"kwController.h"

//kwsprite
#include"Battle_Unit.h"
#include"BackGroundSprite.h"
#include"Battle_Cursor.h"
#include"kwController.h"
//vecter
#include<vector>

using namespace cocos2d;
using namespace std;


class Battle_MenuUI;

class SceneBattle : public CCLayer
{

private://node..
	BackGroundSprite	 m_BG;
	Battle_MenuUI		*m_pMenuUI;
public :

	static CCScene* scene();
	LAYER_NODE_FUNC(SceneBattle)
	
	bool init();
	void tick(ccTime dt);

};