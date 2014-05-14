#pragma once

struct FrameUnit
{
	int x;
	int y;
	int w;
	int h;
};

struct FrameOptionData
{
	int offsetX;
	int offsetY;
	int delay;
	int something;
};

class dataFrame
{
//protected:
public://일단은 선언만 하자. 흐규흐규
	FrameUnit m_srcFrame;
	FrameOptionData m_otherFrameData;

public:
	dataFrame(FrameUnit src, FrameUnit Clash = { 0, 0, 0, 0 }){	;}
	dataFrame(int sx, int sy, int sw, int sh, int cx=0, int cy=0, int cw=0,int ch = 0)
	{
		m_srcFrame = { sx, sy, sw, sh };
		m_otherFrameData = { cx, cy, cw, ch };
	}

	dataFrame(){ ; }
};