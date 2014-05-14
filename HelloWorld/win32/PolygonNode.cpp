#include"PolygonNode.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

bool PolygonNode::init()
{
	if (!CCSprite::init()) return false;

	m_bClosed = true;
	m_bStroke = true;
	m_bFill = true;

	this->m_strokeColor = ccc4(255, 0, 0, 255);
	this->m_fillColor = ccc4(255, 255, 255, 255);

	return true;
}

void PolygonNode::draw()
{
	CCSprite::draw();
	ccDrawPloy();
}

void PolygonNode::ccDrawPloy()
{
	//¹ä¾ÆÀú¾¾µé¾î¿È??
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);


	//º¹ºÙÇÔ ¤·¤·;
	glVertexPointer(2, GL_FLOAT, 0, this->m_pGlPoints);
	if (m_bFill) {
		// Set the OpenGL color
		glColor4ub(m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);

		// Draw the polygon
		if (m_bClosed)
			glDrawArrays(GL_TRIANGLE_FAN, 0, m_iNumberOfPoint);
		else
			glDrawArrays(GL_TRIANGLE_STRIP, 0, m_iNumberOfPoint);
	}
	if (m_bStroke) {
		glColor4f(m_strokeColor.r, m_strokeColor.g, m_strokeColor.b, m_strokeColor.a);
		if (m_bClosed)
			glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)m_iNumberOfPoint);
		else
			glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)m_iNumberOfPoint);
	}

	//¹ä¾ÆÀú¾¾ ³ª°¨
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}

PolygonNode* PolygonNode::PolygonWithPoint(vector<CGPoint> *points)
{
	PolygonNode *p = new PolygonNode;
	p->initWithPoints(points);
	return p;
}
PolygonNode* PolygonNode::PolygonWithRect(const CGSize& rect)
{
	PolygonNode *p = new PolygonNode;


	vector<CGPoint> *points = new vector<CGPoint>;

	points->push_back(ccp(0, 0));
	points->push_back(ccp(rect.width, 0));
	points->push_back(ccp(rect.width, rect.height));
	points->push_back(ccp(0, rect.height));

	p->initWithPoints(points);
	return p;
	
}

bool PolygonNode::initWithPoints(vector<CGPoint> *points)
{
	if (!CCSprite::init()) return false;

	this->setupPoints(points);

	return true;
}
void PolygonNode::setupPoints(vector<CGPoint> *points)
{
	m_iNumberOfPoint = points->size();

	ccVertex2F *newPoint = new ccVertex2F[m_iNumberOfPoint];
	

	vector<CGPoint>::iterator it;
	it = points->begin();

	for (int n = 0; n < m_iNumberOfPoint; n++)
	{
		CGPoint pt = *it;

		ccVertex2F temp;
		if (sizeof(CGPoint) == sizeof(ccVertex2F))//32bit machines
			temp = { pt.x *CC_CONTENT_SCALE_FACTOR(), pt.y * CC_CONTENT_SCALE_FACTOR() };
		else//64bit machines
			temp = { pt.x, pt.y };

		newPoint[n] = temp;

		it++;
	}

	m_pGlPoints = newPoint;

}

void PolygonNode::dealloc()
{
	delete[] this->m_pGlPoints;
	CCSprite::release();
}