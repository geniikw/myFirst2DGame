#pragma once

class kwMsg_Ani
{
public:

	int m_iCAT;
	int m_iFrameStartIndex;
	int m_iFrameRepeatIndex;
	int m_iFrameEndIndex;
	float m_fFrameMaxTime;

public:
	kwMsg_Ani(int cat, int fsi,int fri, int fei, float fmt);
};