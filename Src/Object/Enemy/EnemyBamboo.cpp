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
	isMove_ = true;
}

void EnemyBamboo::Update()
{
	Move();

	StageCollisionUpdate();
}

void EnemyBamboo::Draw()
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

void EnemyBamboo::Release()
{
}

void EnemyBamboo::SetStartPos(int ii)
{
	unit_.pos_ = START_POS[ii]; 
}

void EnemyBamboo::Move()
{
	Collision& ins = Collision::GetInstance();

	if ((unit_.pos_.x - unit_.size_.x / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::LEFT)) {
		if (!isMove_)
		{
			isMove_ = true;
		}
	}
	if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT)) {

		if (isMove_)
		{
			isMove_ = false;
		}
	}

	if (unit_.pos_.x - 250 <= targetPos_.x && unit_.pos_.x + 250 >= targetPos_.x)
	{
		isMove_ = (unit_.pos_.x <= targetPos_.x);
	}

	unit_.pos_.x += isMove_ ? MOVE_SPEED : -MOVE_SPEED;

}