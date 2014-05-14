#pragma once

#include"cocos2d.h"
using namespace cocos2d;
#include<iostream>
#include<vector>
using namespace std;

struct Resource_Unit
{
	string szName;
	CCTexture2D *pRes;

	Resource_Unit()
	{	
		pRes = NULL;
	}	
	~Resource_Unit()
	{
		if (pRes) delete pRes;
	}
};


struct LoadingResult
{
	bool result;
	string filename;
};

class Manager_Resource
{
private:
	HWND m_gInst;

private:
	char m_szBuf[64];
	char m_szBuf2[64];
	FILE *m_pFile;
	
private:
	Manager_Resource();
	vector<Resource_Unit*> m_arrayStorage;

public:
	~Manager_Resource();
	static Manager_Resource *instance;
	static Manager_Resource *getInstance();
	//처음 호출하면 생성자에서 로딩을 끝내고
	// * 수정 로딩화면에 필요한 것만 불러오고 틱에서 리소스를 불러옴
	//이후 필요하면 호출을함.

	LoadingResult LoadingTick();

	bool LoadingResourceWithFile(string file, string str);
	CCTexture2D* getResourceWithString(string str);
	CCSpriteFrame* getFrameWithString(string str);
};

