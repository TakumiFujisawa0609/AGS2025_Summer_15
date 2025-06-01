#include"BossTutorial.h"


BossTutorial::BossTutorial()
{
}

BossTutorial::~BossTutorial()
{
}

void BossTutorial::Init()
{
	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 4500,250 };
	unit_.radius_ = 0;
	unit_.size_ = { 140, 240};

	pattaern_ = E_NON;
}

void BossTutorial::Update()
{
	EnemyBase::Update();


	switch (pattaern_)
	{
	case BossTutorial::E_NON:
	
		break;
	case BossTutorial::E_MOVE:
		
		break;
	case BossTutorial::E_ATTACK:
		
		break;
	}

}

void BossTutorial::Draw()
{
	if (unit_.isDraw_)
	{
		DrawBox(unit_.disppos_.x - 70, unit_.disppos_.y - 120, unit_.disppos_.x + 70, unit_.disppos_.y + 120, 0xfffff0, true);
	}
	DrawFormatString(120, 120, 0x0fffff, "boss(%.2f,%.2f)", unit_.pos_.x, unit_.pos_.y);
}

void BossTutorial::Release()
{

}

void BossTutorial::Move()
{

}

void BossTutorial::Attack()
{

}

void BossTutorial::MoveX()
{

}

void BossTutorial::MoveY()
{

}

void BossTutorial::IsGround(Collision::DIR dir)
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
		unit_.isGravity_ = false;

		break;

	case Collision::LEFT:

		//左側の壁に衝突していたら行う処理


		break;

	case Collision::RIGHT:

		//右側の壁に衝突していたら行う処理


		break;

	}
}