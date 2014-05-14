#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"header.h"
/*
설명 :
CCSprite에 포함되는 맴버 변수로 디자인된 클래스
이걸 포함하면 다 쓸 수 있당.
- 개관
2.5D를 표현할 때 가장 중요한점은
디스플레이와 게임로직에 대한 좌표를 구분하는 것이다.
기존 가지고 있는 setposition은 디스플레이시만 사용하여 이동하게 하고
실제 캐릭터를 움직이게 하기 위해서는 MyUnit내에 들어 있는 좌표값을 이동해
주어야 한다.

- cc3dDraw
CCSprite::draw()를 오버라이딩한 함수내에서만 쓰인다. 게임로직에 사용되고 있는
공간을 폴리곤으로 그린다.

- setPostion
결국 sprite 내에서는 this->setPosition이 아닌 my3dpos->setPosition을
해야 캐릭터를 이동시킬 수 있다.

- getdisplayposition & getdisplayscale
캐릭터가 어디에 위치하여 있는지 그리고 그 위치점에서의 크기를 알아낸다.
이 정보는 캐릭터를 디스플레이 하는 것에 사용된다.

**** 해야할것
폴리곤을 rotate 하기 위해서는 어떤것을 해야 할까.
그리는 방식 자체를 중심점으로잡아야하나? 그래야 되넹.
*/
#include"Point.h"

//struct;...
struct mapData
{
	float fMapWidth;
	float fMapHeight;
	float fSizeRate;
	
	//ver 1.01;
	float fCenterTilt; //기울이는데 필요함 ㅇㅇ;
};
//변환 함수
class MYUnit
{
	//My3DEllipse;
	//My3DTriangle; or My3D피자모양;
protected:
	//맵의 플롯의 정보 이정보는 글로벌함... 따라서 CCSpriteMyMap에서 정보를만들고(new)
	//CCSpriteMyUnit(가제) 에서는 Map의 정보를 참조하는 식으로 만들잣!
	mapData *m_pMapData;
	//만든사람이면 1로 만듦 이후 소멸자에서 이값이 1이면 delete
	bool m_bMapDataMakerFlag;

public://맵정보 세팅 이걸 따로 빼는게 낫지 않을까...
	void makeMapData(float w, float h, float rate, float anchor);
	void setMapData(mapData *map){ m_pMapData = map; }
	void setCenterTilt(float tilt){	if (m_bMapDataMakerFlag == true)m_pMapData->fCenterTilt = tilt; }

	mapData* getMapData(){ return m_pMapData; }

protected://이러지 말고... -_- 함수를 넣자!
	inline float getTilt(float anchor);

protected:
	//anchorPoint와 rotation 정보
	//2014-03-26에 추가함
	//2014-03-30회전 제거.
	CG3Point m_Anchor;
public:
	void setAnchor(const CG3Point &ahr){ m_Anchor = ahr; }
	CG3Point& getAnchor(){ return m_Anchor; }
public://틸트도 조정..
	void setSizeRate(float rate);

protected:
	CG3Point m_pos;  //위치를 담고 있음
	
public://생성자 함수
	MYUnit();
	virtual ~MYUnit();

	//set func
	void setPosition(const CG3Point& pos){ m_pos = pos; }
	//get func
	CGPoint getDisplayPosition(int option = 0);
	CG3Point getPosition() const { return m_pos; }
	float   getDisplayScale();

	//add func;
	void addPosition(const CG3Point &add);

	//translate func  
	inline CGPoint transDisplayPosition(float x, float y, float z);
	inline float transDisplayUnit(float value)
	{
		return linear(1, m_pMapData->fSizeRate, m_pos.y, m_pMapData->fMapHeight) * value;
	}

public://virtual func 
	virtual void cc3dDraw() = 0;
	virtual float getRadius() const { return 0.f; }
	virtual CGPoint getOffset(){ return ccp(0.f, 0.f); }
	virtual CG3Point getOrigin() { return m_pos; }
	virtual float getXLength(){ return 0.f; }
	virtual float getYLength(){ return 0.f; }
	virtual float getZLength(){ return 0.f; }

	/* 
	스프라이트 안에서는 ccDraw들의 기능들이 scale setposition등에 영향을 받는다. 
	하지만 이 기능들은 원근감을 표현하기 위한 수단으로 사용하려고 한다. 따라서 
	포지션에 관련 없는 값을 출력하기 위해여 cc3dDrawInSp를 만듦
	*/
	virtual void cc3dDrawInSP(const CGPoint &minus,const float &scale){ cc3dDraw(); }
	
public:
	virtual float MYUnitGetMaxX() const { return m_pos.x; }
	virtual float MYUnitGetMaxY() const { return m_pos.y; }
	virtual float MYUnitGetMaxZ() const { return m_pos.z; }
	virtual float MYUnitGetMinX() const { return m_pos.x; }
	virtual float MYUnitGetMinY() const { return m_pos.y; }
	virtual float MYUnitGetMinZ() const { return m_pos.z; }
	/*
	뭔가를 그리기 위해서는 점이외의 정보가 필요함
	예를 들어 사각형이면 높이와 넓이가 
	큐브는 x축길이, y축길이, z축길이가 필요하다.
	그래서 인터페이스로 만듦
	*/

public://static 함수들
	//모든 단위를 AABB 알고리즘으로 충돌 유무룰 판단한다. 
	static bool AABBCheck(const MYUnit& cube1, const MYUnit& cube2);
	static bool AABBCheckByPoint(MYUnit* cube1, MYUnit* cube2);
	static bool SphereCheck(const MYUnit& cube1, const MYUnit& cube2);
	static bool SphereCheckByPoint(MYUnit* cube1, MYUnit* cube2);

};
