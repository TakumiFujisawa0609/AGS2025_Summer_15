#include"BossBase.h"

#include<DxLib.h>

BossBase::BossBase()
{
}

BossBase::~BossBase()
{
}

void BossBase::Init(void)
{
	ChangeState(STATE::IDLE);
}

void BossBase::Update(void)
{
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;

	(this->*stateFuncPtr)();

	UnitBase::Update();
}

void BossBase::ChangeState(STATE s)
{
	state_ = s;
	switch (state_)
	{
	case BossBase::STATE::IDLE:
		stateFuncPtr = &BossBase::Idle;
		break;
	case BossBase::STATE::MOVE:
		stateFuncPtr = &BossBase::Move;
		break;
	case BossBase::STATE::ATTACK:
		stateFuncPtr = &BossBase::Attack;
		break;
	case BossBase::STATE::DAMAGE:
		stateFuncPtr = &BossBase::Damage;
		break;
	case BossBase::STATE::DEATH:
		stateFuncPtr = &BossBase::Death;
		break;
	}
}

void BossBase::IsGround(Collision::DIR dir)
{
}

void BossBase::SetPlayerPosPtr(const Vector2F* pos)
{
	playerPosPtr_ = pos;
}

void BossBase::SetDown(Vector2F pos)
{
	unit_.inviCounter_ = 30;

	unit_.isGravity_ = true;
	unit_.isXAttenu = true;

	if (unit_.pos_.x < pos.x) {
		bossDir_ = AttackBase::DIR::RIGHT;
	}
	else {
		bossDir_ = AttackBase::DIR::LEFT;
	}
	unit_.yAccel_ = -10.0f;
	unit_.xAccel_ = 0.0f;

	unit_.nextpos_.y += unit_.yAccel_;

}

