#include "EnemyBamboo.h"
#include<cmath>
#include"../../Utility/AsoUtility.h"
#include "../Manager/EnemyManager.h"

EnemyBamboo::EnemyBamboo()
{
}

EnemyBamboo::~EnemyBamboo()
{
}

void EnemyBamboo::Init()
{
	modelId_ = LoadGraph("Data/Image/Enemy/EnemyBamboo.png");

	unit_.isAlive_ = true;
	unit_.hp_ = HP_MAX;
	unit_.pos_ = { 500,250 };
	unit_.nextpos_ = unit_.pos_;
	unit_.radius_ = 0;
	unit_.size_ = { All_SIZE_X , All_SIZE_Y };
	targetPos_ = { 0.0f, 0.0f };
	rotate_ = 0.0f;
	isMove_ = true;
}

void EnemyBamboo::Update()
{
	Move();
	UnitBase::Update();

}

void EnemyBamboo::Draw()
{
	if (unit_.isDraw_)
	{
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, EX_SIZE, rotate_, modelId_, true, move_);
	}
}

void EnemyBamboo::Release()
{
	DeleteGraph(modelId_);
}

void EnemyBamboo::SetStartPos(int ii)
{
	unit_.nextpos_ = START_POS[ii];
}


void EnemyBamboo::SetDmg(int damage)
{
	unit_.hp_ -= damage;

	if (unit_.hp_ <= 0)
	{
		unit_.isAlive_ = false;
	}
}


void EnemyBamboo::Move()
{

	// ターゲットが近くにいるかどうかを判別
	if (unit_.nextpos_.x - 250 <= targetPos_.x && unit_.nextpos_.x + 250 >= targetPos_.x)
	{
		//if (unit_.nextpos_.x - 5 <= targetPos_.x)
		//{
		//	unit_.nextpos_.x += MOVE_SPEED;  // 右へ
		//}
		//else if (unit_.nextpos_.x + 5 >= targetPos_.x)		//改善余地
		//{
		//	unit_.nextpos_.x -= MOVE_SPEED;  // 左へ
		//}
		
		// ターゲットの近くにいる場合その方向に向かって進む
		move_ = unit_.nextpos_.x <= targetPos_.x ? RIGHT : LEFT;
	}

	switch (move_)
	{
	case EnemyBamboo::RIGHT:
		unit_.nextpos_.x += MOVE_SPEED;
		break;
	case EnemyBamboo::LEFT:
		unit_.nextpos_.x -= MOVE_SPEED;
		break;
	case EnemyBamboo::IDOL:
		break;
	}


}

// 接地している時の数値の代入などをまとめた関数
void EnemyBamboo::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:

		//天井に衝突していたら行う処理
		unit_.yAccel_ = 0;

		break;

	case Collision::DOWN:

		//地面に接地していたら行う処理
		unit_.yAccel_ = 0;
		unit_.isGround_ = true;
		//unit_.isGravity_ = false;

		break;

	case Collision::LEFT:

		//左側の壁に衝突していたら行う処理
		if (!(unit_.nextpos_.x - 250 <= targetPos_.x && unit_.nextpos_.x + 250 >= targetPos_.x)) move_ = RIGHT;


		break;

	case Collision::RIGHT:

		//右側の壁に衝突していたら行う処理
		if (!(unit_.nextpos_.x - 250 <= targetPos_.x && unit_.nextpos_.x + 250 >= targetPos_.x)) move_ = LEFT;
		

		break;

	}
}