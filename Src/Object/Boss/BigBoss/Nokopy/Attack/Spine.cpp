#include "Spine.h"
#include"../../../../../Utility/AsoUtility.h"

Spine::Spine()
{
	obj_.resize(MAX_NUM);
	for (int i = 0; i < obj_.size(); i++) {
		auto& o = obj_[i];
		o.radius_ = 32;
		o.isCircle_ = true;
		o.pos_.x += i * 168;
		o.pos_.y = 672;
		o.isAlive_ = false;
		isParry_ = true;
	}
	couner_ = 0;
	img_ = LoadGraph("Data/Image/Boss/Nokopy/Takenoko.png");
}

Spine::~Spine()
{
}

void Spine::Init(const Vector2F* pos)
{
	for (auto& o : obj_) {
		o.isAlive_ = false;
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
			o.isAlive_ = true;
			o.pos_.y -= 50;
		}
	}

	couner_++;
}

void Spine::Draw(void)
{
	if (couner_ > 0) {

	for (auto& o : obj_) {
			DrawRotaGraph(o.pos_.x, o.pos_.y, 0.1,0, img_, true);
	}
	}
}

void Spine::Release(void)
{
	DeleteGraph(img_);
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
