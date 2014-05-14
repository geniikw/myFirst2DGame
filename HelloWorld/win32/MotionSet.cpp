#include"MotionSet.h"
#include<list>

using namespace std;
#include"header.h"
///////////////////////////////////////////////////////////////////////

MotionSet::MotionSet(wstring *filename)
{
	MotionFileFormatClass f;
	f.fileload(filename);
	
	list<dataMotion> templist;
	
	WCHAR *buf = new WCHAR[64];
	memset(buf, NULL, sizeof(WCHAR)*64);
	lstrcpy(buf, filename->c_str());
	lstrcat(buf, L".png");

	char *tempBuf = wtoa(buf);
	m_fImageH = CCSprite::spriteWithFile(tempBuf)->getContentSize().height;
	delete tempBuf;
	delete [] buf;
	
	f.fileSetout(&templist, filename);

	list<dataMotion>::iterator it;
	for (it = templist.begin(); it != templist.end(); it++)
	{
		m_pMotions.push_back(converterMyFrameToGlFrame(*it));
	}
}

gl2DFrame MotionSet::converterMyFrameToGlFrame(dataMotion& in)
{
	gl2DFrame temp;

	temp.motionName = *in.getName();

	int w, h, x, y;

	for (int n = 0; n < in.getMaxIndex() + 1; n++)
	{
		dataFrame *frame = in.getFrameByIndex(n);
		w = frame->m_srcFrame.w;
		h = frame->m_srcFrame.h;
		x = frame->m_srcFrame.x;
		y = frame->m_srcFrame.y;
		
		CGRect temp2 = { (float)x, (float)y, (float)w, (float)h };

		temp.frame.push_back(temp2);
	}
	
	return temp;
}