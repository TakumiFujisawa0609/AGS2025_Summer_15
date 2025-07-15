#include "BamBeam.h"
#include"../../../../../Application.h"
BamBeam::BamBeam()
{
	img_ = LoadGraph("Data/Image/Boss/Nokopy/Bamboo.png");
}

BamBeam::~BamBeam()
{
}

void BamBeam::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	obj_.radius_ = 128;
	obj_.size_ = { 32,35 };
	obj_.speed_ = 10.0f;
	lookOn_ = false;
	obj_.isAlive_ = false;
	obj_.isCircle_ = false;
	target_ = { 0.0f,0.0f };
	drawPos_ = { 0.0f, 0.0f };
	isParry_ = true;
}

void BamBeam::Update(void)
{
	if (lookOn_) {
		obj_.isAlive_ = true;
		obj_.pos_ = drawPos_ = *boss;
		if (boss->x < target_.x) {
			obj_.pos_.x += obj_.radius_ / 2;
			dir_ = AttackBase::DIR::RIGHT;
			lookOn_ = false;
		}
		else {
			obj_.pos_.x += obj_.radius_ / 2;
			dir_ = AttackBase::DIR::LEFT;
			lookOn_ = false;
		}
	}
	else {
		switch (dir_)
		{
		case AttackBase::LEFT:
			target_.x = 0;
			drawPos_.x -= (drawPos_.x >= target_.x) ? obj_.speed_ * 2 : 0;

			obj_.size_.x = (obj_.pos_.x - drawPos_.x) * 2;

			break;
		case AttackBase::RIGHT:
			target_.x = Application::SCREEN_SIZE_X;
			drawPos_.x += (drawPos_.x <= target_.x) ? obj_.speed_ * 2 : 0;
			obj_.size_.x = (drawPos_.x - obj_.pos_.x) * 2;

			break;
		}
	}

}

void BamBeam::Draw(void)
{
	if (obj_.isAlive_) {
		if (dir_ == RIGHT) {
			DrawRectGraph(obj_.pos_.x, obj_.pos_.y, 0, 0, drawPos_.x, drawPos_.y, img_, true);
		}
		else {
			DrawRectGraph(drawPos_.x, obj_.pos_.y, 0, 0, std::abs(drawPos_.x - obj_.pos_.x), drawPos_.y, img_, true);
		}
	}
}

void BamBeam::Release(void)
{
}

const std::vector<Base> BamBeam::Get(void) const
{
	std::vector <Base>ret;
	ret.emplace_back(obj_);
	return ret;
}

void BamBeam::On(void)
{
}

void BamBeam::Off(void)
{
	obj_.isAlive_ = false;
}

