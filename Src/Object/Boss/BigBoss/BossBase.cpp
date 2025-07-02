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
