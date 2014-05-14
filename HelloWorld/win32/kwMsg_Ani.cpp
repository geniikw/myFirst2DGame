#include"kwMsg_Ani.h"

kwMsg_Ani::kwMsg_Ani(int cat, int fsi,int fri, int fei, float fmt)
{
	m_iCAT = cat;
	m_iFrameStartIndex = fsi;
	m_iFrameRepeatIndex = fri;
	m_iFrameEndIndex = fei;
	m_fFrameMaxTime = fmt;
}