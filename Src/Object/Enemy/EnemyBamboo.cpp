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
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;
	Move();
	UnitBase::Update();
}

void EnemyBamboo::Draw()
{
	if (unit_.isAlive_)
	{
		bool invic = false;
		if (!(unit_.inviCounter_ / 10 % 2 == 0))invic = true;

		if (invic)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, EX_SIZE, rotate_, modelId_, true, move_);

		if (invic)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawHp();
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

	unit_.inviCounter_ = 20;

}


void EnemyBamboo::Move()
{

	/*if (unit_.pos_.x < targetPos_.x - 50) {
		move_ = MOVE::RIGHT;
	}
	else if (unit_.pos_.x > targetPos_.x + 50) {
		move_ = MOVE::LEFT;
	}
	else {
		move_ = MOVE::IDOL;
	}*/

	//float dx = targetPos_.x - unit_.pos_.x;
	//if (std::abs(dx) > 50) {
	//	move_ = (dx > 0) ? MOVE::RIGHT : MOVE::LEFT;
	//}
	//else {
	//	move_ = MOVE::IDOL;
	//}

	switch (move_)
	{
	case MOVE::RIGHT:
		unit_.pos_.x += MOVE_SPEED;
		break;
	case MOVE::LEFT:
		unit_.pos_.x -= MOVE_SPEED;
		break;
	case MOVE::IDOL:
		break;
	}
}

void EnemyBamboo::DrawHp()
{
	int x1 = unit_.disppos_.x - 50;
	int y1 = unit_.disppos_.y - All_SIZE_Y + 10;
	int x2 = unit_.disppos_.x + 50;
	int y2 = unit_.disppos_.y - All_SIZE_Y + 20;
	DrawBar(x1, y1, x2, y2, unit_.hp_, HP_MAX, RGB(0, 0, 255));
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