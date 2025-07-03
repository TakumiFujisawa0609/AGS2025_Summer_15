#include"Blast.h"

#include<DxLib.h>

Blast::Blast()
{
}

Blast::~Blast()
{
}

void Blast::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);

}
void Blast::Update(void)
{
	for (auto& o : obj_) {
		if (!o.isAlive_)continue;
		o.pos_ += vec_;

		Vector2F v = target_ - o.pos_;
		float dis = sqrtf(v.x * v.x + v.y * v.y);

		if (dis < 5.0f) {
			o.size_ *= 2.0f;
			o.isAlive_ = false;
		}
	}
}
void Blast::Draw(void)
{
	for (auto& o : obj_) {
		if (!o.isAlive_)continue;
		DrawCircleAA(o.disppos_.x, o.disppos_.y, o.radius_, 30, RGB(0, 0, 0));
	}
}
void Blast::Release(void)
{

}

const std::vector<Base> Blast::Get(void) const
{
	return std::vector<Base>();
}

void Blast::On(int i,Vector2F pPos)
{
	if (obj_.size() - 1 < i)return;

	obj_[i].pos_ = *boss;

	target_ = pPos;

	Vector2F v = target_ - obj_[i].pos_;
	float size = sqrtf(v.x * v.x + v.y * v.y);
	vec_ = (v / size) * 5.0f;

	obj_[i].isAlive_ = true;
}
