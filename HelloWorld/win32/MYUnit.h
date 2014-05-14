#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"header.h"
/*
���� :
CCSprite�� ���ԵǴ� �ɹ� ������ �����ε� Ŭ����
�̰� �����ϸ� �� �� �� �ִ�.
- ����
2.5D�� ǥ���� �� ���� �߿�������
���÷��̿� ���ӷ����� ���� ��ǥ�� �����ϴ� ���̴�.
���� ������ �ִ� setposition�� ���÷��̽ø� ����Ͽ� �̵��ϰ� �ϰ�
���� ĳ���͸� �����̰� �ϱ� ���ؼ��� MyUnit���� ��� �ִ� ��ǥ���� �̵���
�־�� �Ѵ�.

- cc3dDraw
CCSprite::draw()�� �������̵��� �Լ��������� ���δ�. ���ӷ����� ���ǰ� �ִ�
������ ���������� �׸���.

- setPostion
�ᱹ sprite �������� this->setPosition�� �ƴ� my3dpos->setPosition��
�ؾ� ĳ���͸� �̵���ų �� �ִ�.

- getdisplayposition & getdisplayscale
ĳ���Ͱ� ��� ��ġ�Ͽ� �ִ��� �׸��� �� ��ġ�������� ũ�⸦ �˾Ƴ���.
�� ������ ĳ���͸� ���÷��� �ϴ� �Ϳ� ���ȴ�.

**** �ؾ��Ұ�
�������� rotate �ϱ� ���ؼ��� ����� �ؾ� �ұ�.
�׸��� ��� ��ü�� �߽���������ƾ��ϳ�? �׷��� �ǳ�.
*/
#include"Point.h"

//struct;...
struct mapData
{
	float fMapWidth;
	float fMapHeight;
	float fSizeRate;
	
	//ver 1.01;
	float fCenterTilt; //����̴µ� �ʿ��� ����;
};
//��ȯ �Լ�
class MYUnit
{
	//My3DEllipse;
	//My3DTriangle; or My3D���ڸ��;
protected:
	//���� �÷��� ���� �������� �۷ι���... ���� CCSpriteMyMap���� �����������(new)
	//CCSpriteMyUnit(����) ������ Map�� ������ �����ϴ� ������ ������!
	mapData *m_pMapData;
	//�������̸� 1�� ���� ���� �Ҹ��ڿ��� �̰��� 1�̸� delete
	bool m_bMapDataMakerFlag;

public://������ ���� �̰� ���� ���°� ���� ������...
	void makeMapData(float w, float h, float rate, float anchor);
	void setMapData(mapData *map){ m_pMapData = map; }
	void setCenterTilt(float tilt){	if (m_bMapDataMakerFlag == true)m_pMapData->fCenterTilt = tilt; }

	mapData* getMapData(){ return m_pMapData; }

protected://�̷��� ����... -_- �Լ��� ����!
	inline float getTilt(float anchor);

protected:
	//anchorPoint�� rotation ����
	//2014-03-26�� �߰���
	//2014-03-30ȸ�� ����.
	CG3Point m_Anchor;
public:
	void setAnchor(const CG3Point &ahr){ m_Anchor = ahr; }
	CG3Point& getAnchor(){ return m_Anchor; }
public://ƿƮ�� ����..
	void setSizeRate(float rate);

protected:
	CG3Point m_pos;  //��ġ�� ��� ����
	
public://������ �Լ�
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
	��������Ʈ �ȿ����� ccDraw���� ��ɵ��� scale setposition� ������ �޴´�. 
	������ �� ��ɵ��� ���ٰ��� ǥ���ϱ� ���� �������� ����Ϸ��� �Ѵ�. ���� 
	�����ǿ� ���� ���� ���� ����ϱ� ���ؿ� cc3dDrawInSp�� ����
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
	������ �׸��� ���ؼ��� ���̿��� ������ �ʿ���
	���� ��� �簢���̸� ���̿� ���̰� 
	ť��� x�����, y�����, z����̰� �ʿ��ϴ�.
	�׷��� �������̽��� ����
	*/

public://static �Լ���
	//��� ������ AABB �˰������� �浹 ������ �Ǵ��Ѵ�. 
	static bool AABBCheck(const MYUnit& cube1, const MYUnit& cube2);
	static bool AABBCheckByPoint(MYUnit* cube1, MYUnit* cube2);
	static bool SphereCheck(const MYUnit& cube1, const MYUnit& cube2);
	static bool SphereCheckByPoint(MYUnit* cube1, MYUnit* cube2);

};
