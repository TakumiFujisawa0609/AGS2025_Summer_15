#include "Pbullet.h"

Pbullet::Pbullet() {
}

Pbullet::~Pbullet() {
}

void Pbullet::Init(const Vector2F* pos) 
{
	AttackBase::Init(pos);

	end_ = false;


}

void Pbullet::Update(void) 
{
	for (auto& p : obj_) {
		if (!p.isAlive_)continue;




	}
}

void Pbullet::Draw(void) 
{
}

void Pbullet::Release(void) 
{
}

void Pbullet::On(int i, Vector2F pPos) 
{
	if (obj_.size() <= i)return;

	obj_[i].pos_ = *boss;

	Vector2F v = pPos - obj_[i].pos_;
	float dis = sqrtf(v.x * v.x + v.y * v.y);
	v /= dis;

	move_[i] = v * SPEED;

	obj_[i].isAlive_ = true;
}

void Pbullet::Hit(int i)
{
	if (obj_.size() <= i)return;


}