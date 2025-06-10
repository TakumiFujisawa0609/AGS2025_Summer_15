#include "PlayerAttackBase.h"


PlayerAttackBase::PlayerAttackBase(Vector2F* pPos)
{
	pPos_ = pPos;
	obj_.isAlive_ = false;
}



void PlayerAttackBase::Init(AsoUtility::DIRECTION dir)
{
	dir_ == dir;
}
