#include"Battle_Cursor.h"
#include"BackGroundSprite.h"

Battle_Cursor::Battle_Cursor(float radius, float height)
{
	kwSprite::init();

	My3DCursor *temp = new My3DCursor(radius, height);
	setPosData(temp);
	m_pTarget = NULL;
	m_fSinValue = 0.f;
	schedule(schedule_selector(Battle_Cursor::tick));
}

void Battle_Cursor::tick(ccTime dt)
{
	Manager_Global *pG = Manager_Global::getInstance();
	dt = pG->g_fBattleDT * dt;

	//애니메이션 효과. 돌아감 ㅇㅇ;
	((My3DCursor*)m_pPosData)->addAngle(dt*30.f);

	if (m_pTarget == NULL)
		return;
	
	m_fSinValue += dt * 5.f;//특정 팩터... 뭔가 급박하면 빨리 왔다 갔다 한다던지..

	CG3Point target = m_pTarget->get3DPosition();
	target.z = target.z + ((My3DCube*)m_pTarget->getPosData())->getSize().z + 10.f + 5.f*sinf(m_fSinValue);
	CG3Point temp = target - this->get3DPosition();
	
	addPosition(temp / 4 * dt * 100.f);
}

void Battle_Cursor::setTarget(kwSprite* target)
{
	m_pTarget = target;
}
