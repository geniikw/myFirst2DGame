#pragma once
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

#include"MotionFileFormatClass.h"

/// ����
// �����ڷ� ����� �ش��ϴ� �̹����� ����� data�� �ҷ�����?;

struct gl2DFrame
{
	wstring motionName;
	vector<CGRect> frame;
};

class MotionSet
{
private:
	float m_fImageH;

public:

	vector<gl2DFrame> m_pMotions;
public:
	MotionSet(wstring *filename);

private:
	gl2DFrame converterMyFrameToGlFrame(dataMotion &in);
	//�������;;;
};

