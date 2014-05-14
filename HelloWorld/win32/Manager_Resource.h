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
	//ó�� ȣ���ϸ� �����ڿ��� �ε��� ������
	// * ���� �ε�ȭ�鿡 �ʿ��� �͸� �ҷ����� ƽ���� ���ҽ��� �ҷ���
	//���� �ʿ��ϸ� ȣ������.

	LoadingResult LoadingTick();

	bool LoadingResourceWithFile(string file, string str);
	CCTexture2D* getResourceWithString(string str);
	CCSpriteFrame* getFrameWithString(string str);
};

