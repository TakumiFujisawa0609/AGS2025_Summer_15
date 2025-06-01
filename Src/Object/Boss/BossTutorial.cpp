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

	pattaern_ = E_NON;
	attackState_ = NON;
	attackCounter_ = 0;
	targetIndex_ = -1;
	encount_ = false;
}

void BossTutorial::Update()
{
	if (EnCount())encount_ = true;

	if (encount_) {
		PattaernManager();
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


void BossTutorial::PattaernManager(void)
{
	switch (pattaern_)
	{
	case BossTutorial::E_NON:
		// ランダムで1つ選ぶ
		targetIndex_ = GetRand(2); // 0,1,2のいずれか
		attackCounter_ = 0;
		pattaern_ = E_MOVE;
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
	if (targetIndex_ < 0) return; // 念のため

	Vector2F point = BOSS_POINT[targetIndex_];

	if (attackCounter_ == 0) {
		Vector2F d = { point.x - unit_.nextpos_.x, point.y - unit_.nextpos_.y };
		float t = d.x / unit_.speed_;
		if (t <= 0.0f) t *= -1;
		float jumppower = (d.y + 0.5f * gravity_ * t * t) / t;
		unit_.yAccel_ -= jumppower;
	}

	attackCounter_++;

	unit_.nextpos_.x += GetMoveVec(unit_.nextpos_, point, unit_.speed_).x;

	if (GetDis(unit_.nextpos_, point) <= unit_.speed_ && GetDis(unit_.nextpos_, point) >= -unit_.speed_) {
		attackCounter_ = 0;
		pattaern_ = E_ATTACK;
	}
}


void BossTutorial::Attack()
{
	//pattaern_ = E_NON;

	if (CheckHitKey(KEY_INPUT_U) == 1) {
		pattaern_ = E_NON;
	}
	

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