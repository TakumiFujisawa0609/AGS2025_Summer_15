#include "EnemyBamboo.h"
#include<cmath>
#include"../../Utility/AsoUtility.h"
#include"../../Manager/Collision.h"
#include "../Manager/EnemyManager.h"

EnemyBamboo::EnemyBamboo()
{

}

EnemyBamboo::~EnemyBamboo()
{
}

void EnemyBamboo::Init()
{
	unit_.isAlive_ = true;
	unit_.hp_ = HP_MAX;
	unit_.pos_ = { 500,250 };
	unit_.radius_ = ENEMYBAMBOO_RADIUS;
	unit_.size_ = { unit_.radius_ * 2.0f,unit_.radius_ * 2.0f };
	targetPos_ = { 0.0f, 0.0f };
	move_ = RIGHT;
}

void EnemyBamboo::Update()
{
	Move();

	StageCollisionUpdate();
}

void EnemyBamboo::Draw()
{
	if (unit_.isAlive_)
	{
		//DrawCircle(unit_.disppos_.x, unit_.disppos_.y, unit_.radius_, 0x00ff00, true);
		DrawBox(
			unit_.disppos_.x - unit_.radius_,
			unit_.disppos_.y - unit_.radius_,
			unit_.disppos_.x + unit_.radius_,
			unit_.disppos_.y + unit_.radius_,
			0xfff000, true
		);
	}
}

void EnemyBamboo::Release()
{
}

void EnemyBamboo::SetDmg(int damage)	
{
	unit_.hp_ -= damage;

	if (unit_.hp_ <= 0)
	{
		unit_.isAlive_ = false;
	}
}

void EnemyBamboo::SetStartPos(int ii)
{
	unit_.pos_ = START_POS[ii]; 
}

void EnemyBamboo::Move()
{
	Collision& ins = Collision::GetInstance();

	if ((unit_.pos_.x - unit_.size_.x / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::LEFT)) 
	{
		move_ = RIGHT;
	}
	if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT)) 
	{
		move_ = LEFT;
	}

	if (unit_.pos_.x - 250 <= targetPos_.x && unit_.pos_.x + 250 >= targetPos_.x)
	{
		move_ = unit_.pos_.x <= targetPos_.x? RIGHT : LEFT;
	}

	switch (move_)
	{
	case EnemyBamboo::RIGHT:
		unit_.pos_.x += MOVE_SPEED;
		break;
	case EnemyBamboo::LEFT:
		unit_.pos_.x -= MOVE_SPEED;
		break;
	}

}