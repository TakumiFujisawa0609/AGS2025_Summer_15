#include "Weakness.h"
#include"../../../UnitBase.h"
#include"../../../../Manager/Camera.h"
#include"Attack/WeakBullet.h"

Weakness::Weakness()
{
	bullet_ = nullptr;
}

Weakness::~Weakness()
{
}

//初期化
void Weakness::Init(Vector2F disppos, float moveSpeed)
{
	moveSpeed_ = moveSpeed;

	Camera::CreateInstance();

	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Weakness.png").c_str());

	unit_.nextpos_ = disppos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	bullet_ = new WeakBullet(moveSpeed_);
	bullet_->Init(&unit_.pos_);

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
}

void Weakness::Init(void) {}

void Weakness::Update(Vector2F boss)
{
	unit_.nextpos_.x = boss.x;
}

void Weakness::Update() 
{

	// カウント更新
	cnt_ += 0.1f;

	// ランダムにゆらゆら動くオフセットを加える
	//const float noiseX = (GetRand(200) - 100) / 500.0f;
	const float noiseY = (GetRand(200) - 100) / 500.0f;

	// 元の位置にsin波を少し加える + ノイズ
	//unit_.nextpos_.x += sinf(cnt_) * AMPLITUDE + noiseX;
	unit_.nextpos_.y += cosf(cnt_ * 0.8f) * AMPLITUDE + noiseY;

	if (unit_.inviCounter_ > 0)
	{
		unit_.inviCounter_--;
		if (unit_.inviCounter_ <= 0)
		{
			ChangeState(STATE::IDLE);
		}
	}

	bullet_->Update(unit_.pos_);

	BossBase::Update();
}

void Weakness::Draw()
{
	//ボス描画（とりあえずDrawBox）
	//DrawBox(
	//	unit_.disppos_.x - unit_.size_.x / 2,
	//	unit_.disppos_.y - unit_.size_.y / 2,
	//	unit_.disppos_.x + unit_.size_.x / 2,
	//	unit_.disppos_.y + unit_.size_.y / 2,
	//	RGB(255, 0, 255),
	//	true
	//);

	DrawRotaGraph(
		unit_.disppos_.x,
		unit_.disppos_.y,
		1.0f, 0.0f,
		image_, true
	);

	DrawBar(
		unit_.disppos_.x - SIZE_X / 2 - 50,
		unit_.disppos_.y - SIZE_Y / 2,
		unit_.disppos_.x + SIZE_X / 2 + 50,
		unit_.disppos_.y - SIZE_Y / 2 + 16,
		unit_.hp_, HP_MAX, RGB(0, 0, 255)
	);

	bullet_->Draw();
}

void Weakness::Release()
{
	bullet_->Release();
	delete bullet_;
	bullet_ = nullptr;

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

	ChangeState(STATE::DAMAGE);

	unit_.hp_ -= dmg;
	unit_.inviCounter_ = INVI_COUNTER;
}

void Weakness::StateManager(void)
{
	switch (state_)
	{
	case BossBase::STATE::IDLE:
	case BossBase::STATE::MOVE:
		Move();
		break;
	case BossBase::STATE::ATTACK:
		Attack();
		break;
	case BossBase::STATE::DAMAGE:
		Damage();
		break;
	case BossBase::STATE::DEATH:
		Death();
		break;
	}
}

void Weakness::Idle(void)
{

}

void Weakness::Move(void)
{
}

void Weakness::Attack(void)
{
	switch (attack_)
	{
	case Weakness::NON:
		break;
	case Weakness::BULLET:
		break;
	case Weakness::BOUND:

		break;
	}

}

void Weakness::Damage(void)
{


}

void Weakness::Death(void)
{
}
