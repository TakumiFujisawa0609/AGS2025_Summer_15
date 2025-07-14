#include "Spine.h"

Spine::Spine()
{
	obj_.resize(MAX_NUM);
	for (int i = 0; i < obj_.size(); i++) {
		auto& o = obj_[i];
		o.size_={ 64,0 };
		o.pos_.x += i * 168;
		o.pos_.y = 672;
		o.isAlive_ = false;
	}
	couner_ = 0;
}

Spine::~Spine()
{
}

void Spine::Init(const Vector2F* pos)
{
	for (auto& o : obj_) {
		o.isAlive_ = true;
		o.size_ = { 64,0 };
		o.pos_.y = 672;

	}
	couner_ = 0;
}

void Spine::Update(void)
{
	for (auto& o : obj_)
	{
		if (couner_ < 5) {
			o.pos_.y -= 10;

		}
		else if (couner_ < 60) {
		}
		else if (couner_ < 70) {
			o.pos_.y -= 100;
			o.size_.y = -(o.pos_.y- 672);
		}
	}

	couner_++;
}

void Spine::Draw(void)
{
	for (auto& o : obj_) {
		if (o.isAlive_) {
		DrawBox(o.pos_.x, o.pos_.y, o.pos_.x + o.size_.x, 672, 0x00ff00, true);
		}
	}
}

void Spine::Release(void)
{
}

void Spine::Off(void)
{
	for (int i = 0; i < obj_.size(); i++) {
		auto& o = obj_[i];
		o.pos_.y = 672;
		o.isAlive_ = false;
	}
	couner_ = 0;
}

void Spine::Create(void)
{
}
