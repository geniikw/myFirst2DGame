#include"MotionFileFormatClass.h"

#define ifdelete(p) if((p)!=NULL) delete (p)
#define ifarrydelete(p) if((p)!=NULL) delete [] (p)

void MotionFileFormatClass::fileSetup(list<dataMotion> *ml, wstring imgname)
{
	ifdelete(m_pHeader);
	m_pHeader = new MotionFileHeader;
	
	lstrcpy(m_pHeader->ImgName, imgname.c_str());
	m_pHeader->motionCount = ml->size();

	ifdelete(m_pSaveData);
	m_pSaveData = new MotionFileSet[ml->size()];

	list<dataMotion>::iterator it;
	int n = 0;
	for (it = ml->begin(); it != ml->end(); it++)
	{
		lstrcpy(m_pSaveData[n].MotionName, it->getName()->c_str());
		m_pSaveData[n].frameCount = it->getMaxIndex()+1;

		ifarrydelete(m_pSaveData[n].frame);
		m_pSaveData[n].frame = new dataFrame[m_pSaveData[n].frameCount];
		for (int i = 0; i < m_pSaveData[n].frameCount; i++)
		{
			m_pSaveData[n].frame[i] = *it->getFrameByIndex(i);
		}
		n++;
	}
}

void MotionFileFormatClass::fileout()
{
	WCHAR buf[64];

	lstrcpy(buf, m_pHeader->ImgName);
	lstrcat(buf, L".dat");

	FILE *f;
	_wfopen_s(&f, buf, L"w+");

	fwrite(m_pHeader, sizeof(MotionFileHeader), 1, f);

	for (int n = 0; n < m_pHeader->motionCount; n++)
	{
		fwrite(m_pSaveData[n].MotionName, sizeof(WCHAR), 20, f);
		fwrite(&m_pSaveData[n].frameCount, sizeof(int), 1, f);
		for (int i = 0; i < m_pSaveData[n].frameCount; i++)
		{
			fwrite(&m_pSaveData[n].frame[i], sizeof(dataFrame), 1, f);
		}
	}
	
	fclose(f);
}

void MotionFileFormatClass::fileload(wstring *filename)
{
	WCHAR buf[64];

	lstrcpy(buf, filename->c_str());
	lstrcat(buf, L".dat");

	FILE *f;
	_wfopen_s(&f, buf, L"r+");


	if (m_pHeader == NULL)
		m_pHeader = new MotionFileHeader;
	else
		return;

	fread(m_pHeader, sizeof(MotionFileHeader), 1, f);

	if (!lstrcmp(m_pHeader->ImgName, filename->c_str()))
		m_pSaveData = new MotionFileSet[m_pHeader->motionCount];
	else
		return;

	dataFrame temp;
	for (int n = 0; n < m_pHeader->motionCount; n++)
	{
		fread(m_pSaveData[n].MotionName, sizeof(WCHAR), 20, f);
		fread(&m_pSaveData[n].frameCount, sizeof(int), 1, f);
		
		ifarrydelete(m_pSaveData[n].frame);
		m_pSaveData[n].frame = new dataFrame[m_pSaveData[n].frameCount];
		for (int i = 0; i < m_pSaveData[n].frameCount; i++)
		{
			fread(&temp, sizeof(dataFrame), 1, f);
			m_pSaveData[n].frame[i] = temp;
		}
	}

	fclose(f);
}

void MotionFileFormatClass::fileSetout(list<dataMotion> *ml,wstring *filename)
{
	if (lstrcmp(m_pHeader->ImgName, filename->c_str()))
		return;//파일이름이 다르면 그냥 리턴

	dataMotion temp;

	for (int n = 0; n < m_pHeader->motionCount; n++)
	{
		temp.setName(m_pSaveData[n].MotionName);
		for (int i = 0; i < m_pSaveData[n].frameCount; i++)
		{
			temp.pushFrame(m_pSaveData[n].frame[i]);
		}
		ml->push_back(temp);
		temp.clearAllData();
	}
}
