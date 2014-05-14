#pragma once
#include<vector>
#include"cocos2d.h"


using namespace cocos2d;

//
// http://www.deluge.co/?q=cocos-2d-custom-filled-polygon
// writer : genii ( kiwon Kim )
// date	  : 2014-03-19
// 

class PolygonNode : public CCSprite
{
	
private:
	int m_iNumberOfPoint;  // 점의 갯수
	ccVertex2F *m_pGlPoints; // 점 저장하는곳
	ccColor4B m_strokeColor; 
	ccColor4B m_fillColor;
	bool m_bStroke;
	bool m_bFill;
	bool m_bClosed;
public:

	//override node method
	bool init();
	void draw();
	
	
	void ccDrawPloy();
	
	static PolygonNode* PolygonWithPoint(vector<CGPoint> *points);
	static PolygonNode* PolygonWithRect(const CGSize& rect);

	bool initWithPoints(vector<CGPoint> *points);
	void setupPoints(vector<CGPoint> *points);

	void dealloc();
	

	PolygonNode(){ ; }
	~PolygonNode(){ ; }
};