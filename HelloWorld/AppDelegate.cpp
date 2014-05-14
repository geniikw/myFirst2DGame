#include "cocos2d.h"
using namespace cocos2d;

#include "AppDelegate.h"

//scenes
#include "win32\SceneTitle.h"
#include "win32\SceneTown.h"
#include "win32/SceneLoading.h"
#include "win32/SceneBattle.h"

//�Ŵ��� �Լ�
#include "win32/Manager_Resource.h"
Manager_Resource* Manager_Resource::instance = NULL;
#include "win32\Manager_Global.h"
Manager_Global* Manager_Global::instance = NULL;
#include"win32/Manager_Sound.h"
Manager_Sound* Manager_Sound::instance = NULL;

//���� �Ŵ����� ����...?

AppDelegate::AppDelegate()
:m_pMainWnd(NULL){
}
AppDelegate::~AppDelegate(){
CCX_SAFE_DELETE(m_pMainWnd);
}
bool AppDelegate::applicationDidFinishLaunching()
{

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	// ������ �ʱ�ȭ
	if (!(m_pMainWnd = new CCXEGLView()) || !m_pMainWnd->Create(L"GameSchool", h*640/480, h))
	{
			delete m_pMainWnd;
			return false;
	}
	

	// ���� ������ â�� ������ �����Ѵ�.
	CCDirector::sharedDirector()->setOpenGLView(m_pMainWnd);

	// ������ �����մϴ�. (�����쿡���� �ǹ� ����)
	CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationPortrait);

	// �����ӷ���Ʈ�� ǥ���մϴ�.
	CCDirector::sharedDirector()->setDisplayFPS(false);

	// ������ �ʴ� �׷����� �̹����� �����մϴ�.
	CCDirector::sharedDirector()->setAnimationInterval(1.0 / 60);

	// �������� ����� Scene�� �����մϴ�.
	CCDirector::sharedDirector()->runWithScene(SceneLoading::scene());
	//CCDirector::sharedDirector()->setFullScreen(true);

	return true;
}

// ���ø����̼��� ��׶���� ���� �Ʒ� �Լ��� ���� �մϴ� (�������� ���)
void AppDelegate::applicationDidEnterBackground(){
    CCDirector::sharedDirector()->pause();
	// ���� ���ÿ���� ������ ����� ��� �Ʒ� �ڵ带 ����ϸ� ���嵵 �����մϴ�.
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// ���ø����̼��� ��׶���κ��� ���ƿ������ �� �Լ��� ���� �մϴ� (�������� ���)
void AppDelegate::applicationWillEnterForeground(){
    CCDirector::sharedDirector()->resume();
	
	// ���� ���ÿ���� ������ ����� ��� �Ʒ��ڵ带 ����ϸ� ���尡 �����մϴ�.
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
