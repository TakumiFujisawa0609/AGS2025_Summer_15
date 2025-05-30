#include "EnemyBamboo.h"
#include<cmath>
#include"../../Utility/AsoUtility.h"
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
	rotate_ = 0.0f;
}

void EnemyBamboo::Update()
{
	Move(targetPos_, MOVE_SPEED);

	EnemyBase::Update();

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
	EnemyBase::Release();
}

void EnemyBamboo::SetStartPos(int ii)
{
	unit_.pos_ = START_POS[ii];
}


void EnemyBamboo::SetDmg(int damage)
{
	unit_.hp_ -= damage;

	if (unit_.hp_ <= 0)
	{
		unit_.isAlive_ = false;
	}
}