#include "PlayerAttackBase.h"
#include"../../../Manager/Camera.h"


PlayerAttackBase::PlayerAttackBase()
{
}

PlayerAttackBase::PlayerAttackBase(Vector2F* pPos, AsoUtility::DIRECTION* dir)
{
	pPos_ = pPos;
	dir_ = dir;
	obj_.isAlive_ = false;
}

PlayerAttackBase::~PlayerAttackBase(){}

void PlayerAttackBase::ChangeDispPos(void)
{
	obj_.disppos_.x = obj_.pos_.x - Camera::GetInstance().GetPos().x;
	obj_.disppos_.y = obj_.pos_.y - Camera::GetInstance().GetPos().y;
}

