#pragma once
#include"dataMotion.h"
#include<stdio.h>

//����� �� ���� 
//�����̸�
//�̹��������̸�
//��Ǽ�

//��ǿ� �� ����//
//����̸�
//������1,������2,������3...

//�����ӿ� �� ����.
//srcX, srcY, srcW, srcH;

struct MotionFileHeader
{
	WCHAR ImgName[20];
	int motionCount;
};

struct MotionFileSet
{
	WCHAR MotionName[20];
	int frameCount;
	dataFrame *frame;
public:
	MotionFileSet()
	{
		frame = NULL;
	}
};

class MotionFileFormatClass
{
	MotionFileHeader *m_pHeader;
	MotionFileSet *m_pSaveData;

public:
	MotionFileFormatClass()
	{
		m_pSaveData = NULL;
		m_pHeader = NULL;
	}

	~MotionFileFormatClass()
	{
		if (m_pSaveData != NULL)
		{
			for (int n = 0; n < m_pHeader->motionCount; n++)
			{
				delete[] m_pSaveData[n].frame;
			}
			delete m_pSaveData;
		}
		
		if (m_pHeader != NULL)
			delete m_pHeader;
	}
	void fileSetup(list<dataMotion> *ml, wstring imgname);
	void fileSetout(list<dataMotion> *ml, wstring *filename);
	
	void fileout();
	void fileload(wstring *filename);

	void clear();

};