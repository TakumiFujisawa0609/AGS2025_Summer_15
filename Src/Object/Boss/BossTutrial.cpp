#include"BossTutrial.h"


BossTutrial::BossTutrial()
{
}

BossTutrial::~BossTutrial()
{
}

void BossTutrial::Init()
{
	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 3000,250 };
	unit_.radius_ = 0;
	unit_.size_ = { 140, 240};
}

void BossTutrial::Update()
{
	EnemyBase::Update();

}

void BossTutrial::Draw()
{
	if (unit_.isDraw_)
	{
		DrawBox(unit_.disppos_.x - 70, unit_.disppos_.y - 120, unit_.disppos_.x + 70, unit_.disppos_.y + 120, 0xff0000, true);
	}
	DrawFormatString(120, 120, 0x0ff0ff, "boss(%.2f,%.2f)", unit_.pos_.x, unit_.pos_.y);
}

void BossTutrial::Release()
{

}



void BossTutrial::MoveX()
{

}

void BossTutrial::MoveY()
{

}

void BossTutrial::IsGround(Collision::DIR dir)
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



void BossTutrial::Move()
{

}