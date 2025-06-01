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
	unit_.nextpos_ = unit_.pos_;
	unit_.radius_ = 0;
	unit_.size_ = { 140, 240};
	unit_.speed_ = 10.0f;

	pattaern_ = E_MOVE;
	attackState_ = NON;
}

void BossTutorial::Update()
{
	ChangeState();

	if (pattaern_ == E_MOVE) {
		unit_.nextpos_ += GetMoveVec(unit_.nextpos_, player_->GetUnit().pos_, unit_.speed_);
	}

	EnemyBase::Update();

}

void BossTutorial::Draw()
{
	if (unit_.isDraw_)
	{
		DrawBox(unit_.disppos_.x - 70, unit_.disppos_.y - 120, unit_.disppos_.x + 70, unit_.disppos_.y + 120, 0xfffff0, true);
	}
	DrawFormatString(120, 120, 0x0fffff, "boss(%.2f,%.2f)", unit_.nextpos_.x, unit_.nextpos_.y);
}

void BossTutorial::Release()
{

}


void BossTutorial::ChangeState(void)
{
	switch (pattaern_)
	{
	case BossTutorial::E_NON:
		if (EnCount())pattaern_ = E_MOVE;
		break;
	case BossTutorial::E_MOVE:
		Move();
		break;
	case BossTutorial::E_ATTACK:
		Attack();
		break;
	}
}


bool BossTutorial::EnCount(void)
{
	Vector2F vec = { player_->GetUnit().pos_.x - unit_.nextpos_.x,player_->GetUnit().pos_.y - unit_.nextpos_.y };

	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (distance < 500.0f)return true;

	return false;
}


void BossTutorial::Move()
{

}


void BossTutorial::Attack()
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
		unit_.xAccel_ = 0;


		break;

	case Collision::RIGHT:

		//右側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0;


		break;

	}
}