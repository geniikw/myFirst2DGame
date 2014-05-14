#include"UI_TownMenu.h"
#include"Manager_Resource.h"

bool UI_TownMenu::init()
{
	if (!initWithTexture(Manager_Resource::getInstance()->getResourceWithString("Menu")))
		false;

	return true;
}


void UI_TownMenu::tick(ccTime dt)
{

}