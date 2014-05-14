#include"kwOrder.h"

#include"Battle_Unit.h"
kwOrder::kwOrder(Battle_Unit *owner)
{
	m_iProcess = OP_STANDBY;
	m_pOwner = owner;
}
