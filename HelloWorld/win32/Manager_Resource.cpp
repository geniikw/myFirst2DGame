#include"Manager_Resource.h"

Manager_Resource::Manager_Resource()
{
	fopen_s(&m_pFile, "LoadingList.list", "r");
}

Manager_Resource::~Manager_Resource()
{
	fclose(m_pFile);
}

Manager_Resource* Manager_Resource::getInstance()
{
	if (instance == NULL)
	{
		instance = new Manager_Resource;
	}
	return instance;
}

CCTexture2D* Manager_Resource::getResourceWithString(string str)
{
	vector<Resource_Unit*>::iterator it;

	for (it = m_arrayStorage.begin(); it != m_arrayStorage.end(); it++)
	{
		if ((*it)->szName == str)
		{
			return (*it)->pRes; //이게 맞나??-_-;
		}
	}
	//찾고 없으면 널 리턴...
	return NULL;
}



CCSpriteFrame* Manager_Resource::getFrameWithString(string str)
{
	CCTexture2D *res;
	res = getResourceWithString(str);
	
	CCSpriteFrame *result;
	result = new CCSpriteFrame;
	result->initWithTexture(res, CGRect(0,0,res->getContentSize().width,res->getContentSize().height));

	return result;
}

bool Manager_Resource::LoadingResourceWithFile(string file,string str)
{
	Resource_Unit *temp = new Resource_Unit;
	temp->szName = str;
	temp->pRes = new CCTexture2D;
	//temp->pRes = CCTextureCache::sharedTextureCache()->addImage(file.append(".png").c_str());
	temp->pRes = CCTextureCache::sharedTextureCache()->addImage(file.c_str());

	if (temp->pRes == NULL)
		return false;

	m_arrayStorage.push_back(temp);
	return true;
}

LoadingResult Manager_Resource::LoadingTick()
{
	LoadingResult temp;
	fscanf_s(m_pFile, "%s %s\n", &m_szBuf, 64, &m_szBuf2, 64);
	if (strcmp(m_szBuf,"END"))
	{
		LoadingResourceWithFile(m_szBuf, m_szBuf2);
		temp.result = true;
		temp.filename = m_szBuf;
		return temp;
	}
	temp.result = false;
	return temp;
}
