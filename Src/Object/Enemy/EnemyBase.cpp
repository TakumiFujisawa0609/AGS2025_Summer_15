#include "EnemyBase.h"
#include"../../Manager/Collision.h"


EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}


void EnemyBase::Init()
{
	move_ = RIGHT;
}

void EnemyBase::Update()
{
	UnitBase::Update();
}

void EnemyBase::Draw()
{

}

void EnemyBase::Release()
{
}


void EnemyBase::Move(Vector2F targetpos, float moveSpeed)
{
	Collision& ins = Collision::GetInstance();

	// ターゲットが近くにいるかどうかを判別
	if (unit_.pos_.x - 250 <= targetpos.x && unit_.pos_.x + 250 >= targetpos.x)
	{
		// ターゲットの近くにいる場合その方向に向かって進む
		move_ = unit_.pos_.x <= targetpos.x ? RIGHT : LEFT;
	}
	else
	{
		// 壁に当たったら反対の方向を向く
		if ((unit_.pos_.x - unit_.size_.x / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::LEFT))
		{
			move_ = RIGHT;
		}
		if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT))
		{
			move_ = LEFT;
		}
	}

	switch (move_)
	{
	case EnemyBase::RIGHT:
		unit_.pos_.x += moveSpeed;
		break;
	case EnemyBase::LEFT:
		unit_.pos_.x -= moveSpeed;
		break;
	case EnemyBase::IDOL:
		break;
	}
}
