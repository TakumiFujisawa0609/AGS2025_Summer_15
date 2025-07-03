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
void Weakness::Init(Vector2F disppos)
{
	Camera::CreateInstance();

	unit_.nextpos_ = disppos;
	unit_.pos_ = unit_.nextpos_;

	unit_.size_ = { SIZE_X,SIZE_Y };

	////画面の左端を見る
	//start_.x = 0.0f;
	//start_.y = 0.0f;

	cnt_ = GetRand(16);

	//unit_.pos_ + start_;
	unit_.hp_ = HP_MAX;
	unit_.isAlive_ = true;

	ChangeState(STATE::IDLE);

	//WeakBullet* bullet = new WeakBullet();
	//bullet->Init(&unit_.disppos_);

	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;

	bullet_ = new WeakBullet();
	bullet_->Init(&unit_.pos_);
}

void Weakness::Init(void) {}

void Weakness::Update(Vector2F boss)
{
	unit_.nextpos_.x += 1.0f;

	BossBase::Update();

	bullet_->Update();
}

void Weakness::Update() {}

void Weakness::Draw()
{
	//ボス描画（とりあえずDrawBox）
	DrawBox(
		unit_.disppos_.x - unit_.size_.x / 2,
		unit_.disppos_.y - unit_.size_.y / 2,
		unit_.disppos_.x + unit_.size_.x / 2,
		unit_.disppos_.y + unit_.size_.y / 2,
		RGB(255, 0, 255),
		true
	);

	bullet_->Draw();
}

void Weakness::Release()
{
	bullet_->Release();
	delete bullet_;
	bullet_ = nullptr;

	Camera::DeleteInstance();
}

AttackBase* Weakness::GetAttackIns(void)
{
	return nullptr;
}

std::vector<Base> Weakness::GetObj(void)
{
	std::vector<Base>ret;

	ret = bullet_->Get();

	return ret;
}

void Weakness::ObjHit(int i)
{

}

void Weakness::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0 || unit_.isInvincible_) return;

	unit_.hp_ -= dmg;

	if (unit_.hp_ <= 0)
	{
		unit_.isAlive_ = false;
		ChangeState(STATE::DEATH); // 状態遷移も必要なら
	}
}

void Weakness::Idle(void)
{
	// カウント更新
	cnt_ += 0.1f;

	// ランダムにゆらゆら動くオフセットを加える
	const float noiseX = (GetRand(200) - 100) / 500.0f;
	const float noiseY = (GetRand(200) - 100) / 500.0f;

	// 元の位置にsin波を少し加える + ノイズ
	unit_.nextpos_.x += sinf(cnt_) * AMPLITUDE + noiseX;
	unit_.nextpos_.y += cosf(cnt_ * 0.8f) * AMPLITUDE + noiseY;
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

void Weakness::Death(void)
{
}
