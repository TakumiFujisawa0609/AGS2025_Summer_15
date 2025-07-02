#include "BombooShoot.h"

BombooShoot::BombooShoot()
{
}

BombooShoot::~BombooShoot()
{
}

void BombooShoot::Init(void)
{
	BossBase::Init();
	unit_.isAlive_ = true;
	unit_.isDraw_ = false;
	unit_.nextpos_ = unit_.pos_;
	unit_.size_ = { SIZE_X, SIZE_Y };
	unit_.radius_ = unit_.size_.x / 2;
	unit_.speed_ = 10.0f;
	unit_.hp_ = BOSS_HP;


	state_ = BossBase::STATE::IDLE;
	attackState_ = NON;
	attackCounter_ = 0;
}

void BombooShoot::Update(void)
{
	BossBase::Update();
}

void BombooShoot::Draw(void)
{

}

void BombooShoot::Release(void)
{
	//画像の開放
	for (int i = 0; i < DRAW::DRAW_MAX; i++)DeleteGraph(img_[i]);
}

std::vector<Base*> BombooShoot::GetObj(void)
{
	switch (attackState_)
	{
	
	return std::vector<Base*>();
	}
}

void BombooShoot::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= dmg;
	//hitTimer_ = 10;
	unit_.inviCounter_ = 5;

	if (unit_.hp_ <= 0) {
		unit_.isAlive_ = false;
	}
}

void BombooShoot::Idle(void)
{
}

void BombooShoot::Move(void)
{
}

void BombooShoot::Attack(void)
{
	attackCounter_++;
	//アタックの状態遷移
	auto it = attackUpdateFuncs_.find(attackState_);
	(this->*(it->second))();

	//デバック用（アタックの状態を攻撃をしてないときの状態にする）
	if (CheckHitKey(KEY_INPUT_U) == 1) {
		state_ = BossBase::STATE::IDLE;
	}

	//バグが起きた時のための最終手段
	//（一定の時間を超えたら攻撃状態が強制的に終了する）
	if (attackCounter_ > 1000 || attackState_ == NON) {
		attackCounter_ = 0;
		state_ = BossBase::STATE::IDLE;
		attackState_ = NON;
	}
}

void BombooShoot::Damage(void)
{
}

void BombooShoot::Death(void)
{
}

void BombooShoot::IsGround(Collision::DIR dir)
{
}
