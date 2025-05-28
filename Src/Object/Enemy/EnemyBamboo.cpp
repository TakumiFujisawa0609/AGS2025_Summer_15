#include "EnemyBamboo.h"
#include<cmath>
#include"../../Utility/AsoUtility.h"
#include"../../Manager/Collision.h"
#include "../Manager/EnemyManager.h"

EnemyBamboo::EnemyBamboo()
{
	unit_.modelId_ = LoadGraph("Data/Image/Enemy/EnemyBamboo.png");
}

EnemyBamboo::~EnemyBamboo()
{
}

void EnemyBamboo::Init()
{
	unit_.isAlive_ = true;
	unit_.hp_ = HP_MAX;
	unit_.pos_ = { 500,250 };
	unit_.radius_ = 0;
	unit_.size_ = { All_SIZE_X , All_SIZE_Y };
	targetPos_ = { 0.0f, 0.0f };
	move_ = RIGHT;
	rotate_ = 0.0f;
}

void EnemyBamboo::Update()
{
	if (DeathProcess() == false)
	{
		Move();

		StageCollisionUpdate();
	}
}

void EnemyBamboo::Draw()
{
	if (unit_.isDraw_)
	{
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, EX_SIZE, rotate_, unit_.modelId_, true, move_);
	}
}

void EnemyBamboo::Release()
{
	DeleteGraph(unit_.modelId_);
}

bool EnemyBamboo::DeathProcess()
{
	if (!unit_.isAlive_)
	{
		float cnt_ = 0.0f;
		cnt_++;
		if (cnt_ > 30)
		{
			move_ = IDOL;
		}
		else
		{
			rotate_ += 0.7f;
			if (rotate_ > 20.0f)
			{
				unit_.isDraw_ = false;
				cnt_ = 0.0f;
				return true;
			}
		}

	}
	return false;
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

	// ターゲットが近くにいるかどうかを判別
	if (unit_.pos_.x - 250 <= targetPos_.x && unit_.pos_.x + 250 >= targetPos_.x)
	{
		//if (unit_.pos_.x - 5 <= targetPos_.x)
		//{
		//	unit_.pos_.x += MOVE_SPEED;  // 右へ
		//}
		//else if (unit_.pos_.x + 5 >= targetPos_.x)		//改善余地
		//{
		//	unit_.pos_.x -= MOVE_SPEED;  // 左へ
		//}
		
		// ターゲットの近くにいる場合その方向に向かって進む
		move_ = unit_.pos_.x <= targetPos_.x ? RIGHT : LEFT;
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
	case EnemyBamboo::RIGHT:
		unit_.pos_.x += MOVE_SPEED;
		break;
	case EnemyBamboo::LEFT:
		unit_.pos_.x -= MOVE_SPEED;
		break;
	case EnemyBamboo::IDOL:
		break;
	}
}