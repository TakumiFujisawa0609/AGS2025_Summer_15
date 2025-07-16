#include"BPAttack.h"

#include<DxLib.h>

#include"../../../Manager/Collision.h"
#include"../../../Manager/SceneManager.h"

#include"../Player.h"
#include"ThrowBamboo.h"
#include"GrowBamboo.h"
#include"Firecracker.h"

BPAttack::BPAttack() : PlayerAttackBase()
{
}

BPAttack::~BPAttack()
{
}


void BPAttack::Init(int image)
{
	this->image_ = image;

	obj_.radius_ = DEFAULT_RADIUS;

	obj_.size_ = { DEFAULT_SIZE_X,DEFAULT_SIZE_Y };
}

void BPAttack::Update(void)
{
	if (attack_) {
		attack_->Update();
	}
	// オブジェクトが生存していなければ処理しない
	if (!obj_.isAlive_) return;

	if (aliveCounter_-- <= 0 || bounce_ > BOUNCE_MAX)obj_.isAlive_ = false;

	obj_.pos_ += vec_;

	// 表示座標を更新
	ChangeDispPos();

	if (obj_.disppos_.x < DEFAULT_SIZE_X / 2 || obj_.disppos_.x > Application::SCREEN_SIZE_X - DEFAULT_SIZE_X / 2) {
		vec_.x *= -1;
		obj_.pos_ += vec_;
		if (power_ < POWER_MAX) power_++;
		bounce_++;
		obj_.size_ = { DEFAULT_SIZE_X * (1.0f + power_ / 5.0f),DEFAULT_SIZE_Y * (1.0f + power_ / 5.0f) };
	}
	if (obj_.disppos_.y<DEFAULT_SIZE_Y / 2 || obj_.disppos_.y>Application::SCREEN_SIZE_Y - DEFAULT_SIZE_Y / 2) {
		vec_.y *= -1;
		obj_.pos_ += vec_;
		if (power_ < POWER_MAX) power_++;
		bounce_++;
		obj_.size_ = { DEFAULT_SIZE_X * (1.0f + power_ / 5.0f),DEFAULT_SIZE_Y * (1.0f + power_ / 5.0f) };
	}
}

void BPAttack::Draw(void)
{
	if (!obj_.isAlive_)return;
	DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, 1.0f + power_ / 5.0f, atan2(vec_.y, vec_.x), image_, true);
}

void BPAttack::Release(void)
{
	if (attack_) {
		attack_->Release();
	}
}

void BPAttack::On(Vector2F pPos, Vector2F vec)
{
	// 攻撃オブジェクトを有効化し、初期パラメータを設定
	obj_.isAlive_ = true;

	this->vec_ = vec * DEFAULT_SPEED;

	obj_.pos_ = pPos;

	aliveCounter_ = ALIVE_TIME;
	power_ = 1;
	bounce_ = 0;
}

void BPAttack::Parry(Vector2F pos)
{
	bounce_ = 0;
	if (power_ < POWER_MAX) power_++;

	Vector2F v = obj_.pos_ - pos;
	float size = sqrtf(v.x * v.x + v.y * v.y);
	v /= size;
	vec_ = v * DEFAULT_SPEED;
}

