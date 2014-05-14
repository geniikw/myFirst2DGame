#pragma once
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

#include"MotionFileFormatClass.h"

/// 설명
// 생성자로 만들면 해당하는 이미지의 내용과 data가 불려져옴?;

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
	//쓸모없음;;;
};

