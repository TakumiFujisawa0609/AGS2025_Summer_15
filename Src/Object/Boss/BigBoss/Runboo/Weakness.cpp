#include "Weakness.h"
#include"../../../UnitBase.h"
#include"../../../../Manager/Camera.h"
#include"Attack/WeakBullet.h"
#include"Attack/Laser.h"

Weakness::Weakness()
{
	bullet_ = nullptr;
	laser_ = nullptr;
}

Weakness::~Weakness()
{
}

//初期化
void Weakness::Init(Vector2F disppos, float moveSpeed)
{
	BossBase::Init();
	moveSpeed_ = moveSpeed;

	Camera::CreateInstance();

	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Weakness.png").c_str());

	unit_.nextpos_ = disppos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	bullet_ = new WeakBullet(moveSpeed_);
	bullet_->Init(&unit_.pos_);

	laser_ = new Laser(moveSpeed_);
	laser_->Init(&unit_.pos_);

	unit_.size_ = { SIZE_X,SIZE_Y };
	unit_.radius_ = 64.0f;

	cnt_ = GetRand(16.0f);

	//unit_.pos_ + start_;
	unit_.hp_ = HP_MAX;
	unit_.isAlive_ = true;

	ChangeState(STATE::IDLE);

	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;

	attack_ = ATTACK::NON;

	laser_->SetTarget(*playerPosPtr_);

}

void Weakness::Init(void) {}

void Weakness::Update(Vector2F boss)
{
	if (!unit_.isAlive_)return;
	unit_.nextpos_.x = boss.x;
}

void Weakness::Update() 
{

	// カウント更新
	cnt_ += 0.1f;

	BossBase::Update();

	// ランダムにゆらゆら動く
	//const float noiseX = (GetRand(200) - 100) / 500.0f;
	const float noiseY = (GetRand(200) - 100) / 500.0f;

	// 元の位置から縦にゆらゆら動かす
	//unit_.nextpos_.x += sinf(cnt_) * AMPLITUDE + noiseX;
	unit_.nextpos_.y += cosf(cnt_ * 0.8f) * AMPLITUDE + noiseY;

	if (unit_.inviCounter_ > 0)
	{
		unit_.inviCounter_--;
	}

	if (unit_.hp_ <= 0)
	{
		bullet_->SetIsAlive(false);
		if (unit_.hp_ <= 0) {
			unit_.isAlive_ = false;
		}

		ChangeState(STATE::DEATH);
	}
	bullet_->Update(unit_.pos_);
	laser_->Update(unit_.pos_);

}

void Weakness::Draw()
{
	DrawRotaGraph(
		unit_.disppos_.x,
		unit_.disppos_.y,
		1.0f, 0.0f,
		image_, true
	);

	if (!unit_.isAlive_)return;

	DrawBar(
		unit_.disppos_.x - SIZE_X / 2 - 50,
		unit_.disppos_.y - SIZE_Y / 2,
		unit_.disppos_.x + SIZE_X / 2 + 50,
		unit_.disppos_.y - SIZE_Y / 2 + 16,
		unit_.hp_, HP_MAX, RGB(0, 0, 255)
	);

	bullet_->Draw();
	laser_->Draw();
}

void Weakness::Release()
{
	bullet_->Release();
	delete bullet_;
	bullet_ = nullptr;

	laser_->Release();
	delete laser_;
	laser_ = nullptr;

	DeleteGraph(image_);

	Camera::DeleteInstance();
}

AttackBase* Weakness::GetAttackIns(void)
{
	return nullptr;
}

std::vector<Base> Weakness::GetObj(void)
{


	return bullet_->Get();
}

void Weakness::ObjHit(int i)
{
	bullet_->Hit();
}

void Weakness::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0 || unit_.isInvincible_) return;

	unit_.hp_ -= dmg;
	unit_.inviCounter_ = INVI_COUNTER;
}

void Weakness::Idle(void)
{

}

void Weakness::Move(void)
{
}

void Weakness::Attack(void)
{
}

void Weakness::Damage(void)
{


}

//死んだ後の処理
void Weakness::Death(void)
{
	auto& camera_ = Camera::GetInstance();

	unit_.pos_.x += moveSpeed_;

	unit_.pos_.x += camera_.GetPos().x + Application::SCREEN_SIZE_X / 2;
}
