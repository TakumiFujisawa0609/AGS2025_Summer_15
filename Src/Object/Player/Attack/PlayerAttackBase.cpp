#include<DxLib.h>
#include "PlayerAttackBase.h"


PlayerAttackBase::PlayerAttackBase()
{
}


PlayerAttackBase::~PlayerAttackBase()
{
}


void PlayerAttackBase::Init(void)
{
}

void PlayerAttackBase::Init(Vector2F* movePos, Vector2F* drawPos)
{
	unit_.isAlive_ = false;
	pMovePos_= movePos;
	pDrawPos_ = drawPos;
	isattackEnd_ = false;
	attackCounter_ = 0;

}

void PlayerAttackBase::Update(void)
{
	ChangeDispPos();

}

void PlayerAttackBase::Draw(void)
{
}

void PlayerAttackBase::Release(void)
{
}

const std::vector<Base> PlayerAttackBase::GetStruct(void) const
{
	std::vector<Base>ret;

	ret.emplace_back(attackObj_);

	return ret;
}