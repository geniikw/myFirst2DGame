#include"UI_CharState.h"
#include"Manager_Resource.h"


bool UI_CharState::init()
{
	if (!initWithTexture(Manager_Resource::getInstance()->getResourceWithString("CharMenu")))
		return false;


	return true;
}


void UI_CharState::tick(ccTime dt)
{

}

float UI_CharState::getMenuAngle()
{
	switch (m_iNumber)
	{
	case 0:return 190.f; break;
	case 1:return 280.f; break;
	case 2:return 10.f; break;
	case 3:return 100.f; break;
	}
}