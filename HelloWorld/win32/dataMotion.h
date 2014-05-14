#pragma once
#include"dataFrame.h"
#include<Windows.h>
#include<list>

using namespace std;

class dataMotion
{
	wstring			m_szMotionname;
	list<dataFrame> m_listFrame;

public:
	dataMotion(){ ; }

	int getMaxIndex(){ return m_listFrame.size() - 1; }//���࿡ -1�̸� �ƹ��͵� ���ٴ� �� 
	void pushFrame(dataFrame Frame){ m_listFrame.push_back(Frame); }
	void setName(wstring name){ m_szMotionname = name; }
	wstring* getName(){ return &m_szMotionname; }

	void popFrame(){ m_listFrame.pop_back(); }

	//cpp�� ����'';
	dataFrame* getFrameByIndex(int index);
	void deleteByIndex(int index);
	void setByIndex(int index,dataFrame Frame);

	void clearAllData();

private:
	list<dataFrame>::iterator getByIndex(int index);
};
