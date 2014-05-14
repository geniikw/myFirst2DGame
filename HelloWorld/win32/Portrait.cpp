#include"Portrait.h"
#include"header.h"
#include"Manager_Resource.h"

Portrait::Portrait()
{

	CCSprite::init();

	CCTexture2D *portaits = Manager_Resource::getInstance()->getResourceWithString("portrait");
	
	CCAnimation *pPA = new CCAnimation;
	pPA->initWithName("PORTRAIT");

	pPA->addFrameWithTexture(portaits, CGRect(0, 0, 1, 1));
	for (int n = 0; n < MAX_CHARACTER_NUMBER+1; n++)
	{
		pPA->addFrameWithTexture(portaits, CGRect(226*(n%8),(n/8) * 482 , 224, 480));
	}
	this->addAnimation(pPA);

}

void Portrait::setPortrait(int CharacterName)
{
	m_iCharacterName = CharacterName;
	setDisplayFrame("PORTRAIT", m_iCharacterName);
}