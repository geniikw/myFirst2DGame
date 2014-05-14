#pragma once
#include"dataMotion.h"
#include<stdio.h>

//헤더에 들어갈 내용 
//게임이름
//이미지파일이름
//모션수

//모션에 들어갈 내용//
//모션이름
//프레임1,프레임2,프레임3...

//프레임에 들어갈 내용.
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