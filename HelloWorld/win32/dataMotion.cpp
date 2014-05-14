#include"dataMotion.h"


list<dataFrame>::iterator dataMotion::getByIndex(int index)
{
	list<dataFrame>::iterator it;
	it = m_listFrame.begin();
	for (int n = 0; n < index; n++)
	{
		it++;
	}
	return it;
}
void dataMotion::deleteByIndex(int index)
{
	m_listFrame.erase(getByIndex(index));
}

void dataMotion::setByIndex(int index, dataFrame Frame)
{
	m_listFrame.erase(getByIndex(index));
	m_listFrame.insert(getByIndex(index), Frame);
}

dataFrame* dataMotion::getFrameByIndex(int index)
{
	if (this->getMaxIndex() == -1)
		return NULL;

	if (index > getMaxIndex())
		return NULL;

	return &(*getByIndex(index));
}


void dataMotion::clearAllData()
{
	m_listFrame.clear();
	//while (m_listFrame.size() != 0)
	//{
	//	m_listFrame.pop_back();
	//}
}