#include"BPAttack.h"

#include<DxLib.h>

#include"../../../Manager/Collision.h"
#include"../../../Manager/SceneManager.h"

#include"../Player.h"

BPAttack::BPAttack() : PlayerAttackBase(),
	aliveCounter_(0),
	bounce_(0),
	image_(0),
	power_(0)
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
	if (!obj_.isAlive_)return;

	if (aliveCounter_-- <= 0 || bounce_ > BOUNCE_MAX)obj_.isAlive_ = false;

	obj_.pos_ += vec_;

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
	DrawRotaGraphF(obj_.disppos_.x, obj_.disppos_.y, 1.0f + power_ / 5.0f, atan2(vec_.y, vec_.x), image_, true);
}

void BPAttack::Release(void)
{
}

void BPAttack::On(Vector2F pPos, Vector2F vec)
{
	obj_.isAlive_ = true;

	this->vec_ = vec * DEFAULT_SPEED;

	obj_.pos_ = pPos;
	ChangeDispPos();
	if (obj_.disppos_.x < DEFAULT_SIZE_X / 2) {
		obj_.pos_.x += (DEFAULT_SIZE_X / 2) - obj_.disppos_.x;
		ChangeDispPos();
	}
	if (obj_.disppos_.x > Application::SCREEN_SIZE_X - DEFAULT_SIZE_X / 2) {
		obj_.pos_.x -= obj_.disppos_.x - (Application::SCREEN_SIZE_X - DEFAULT_SIZE_X / 2);
		ChangeDispPos();
	}

	aliveCounter_ = ALIVE_TIME;
	power_ = 1;
	bounce_ = 0;
}

void BPAttack::Parry(Vector2F pos)
{
	bounce_ = 0;
	if (power_ < POWER_MAX) power_++;

	Vector2F v = obj_.pos_ - pos;
	if (v.x == 0.0f && v.y == 0.0f) {
		return; 
	}
	float size = sqrtf(v.x * v.x + v.y * v.y);
	v /= size;
	vec_ = v * DEFAULT_SPEED;
}
