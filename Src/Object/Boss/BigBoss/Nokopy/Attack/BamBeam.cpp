#include "BamBeam.h"
#include"../../../../../Application.h"
BamBeam::BamBeam()
{
}

BamBeam::~BamBeam()
{
}

void BamBeam::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	obj_.radius_ = 128;
	obj_.size_ = { 32,128 };
	obj_.speed_ = 10.0f;
	lookOn_ = false;
	obj_.isAlive_ = false;
	obj_.isCircle_ = false;
	target_ = { 0.0f,0.0f };
	drawPos_ = {0.0f, 0.0f};
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
			drawPos_.x -= (drawPos_.x >= target_.x) ? obj_.speed_*2 : 0;

			obj_.size_.x = (obj_.pos_.x-drawPos_.x)*2;

		//	obj_.isAlive_ = (drawPos_.x >= target_.x) ? true : false;
			break;
		case AttackBase::RIGHT:
			target_.x = Application::SCREEN_SIZE_X;
			drawPos_.x += (drawPos_.x <=target_.x ) ? obj_.speed_*2 : 0;
			obj_.size_.x =( drawPos_.x-obj_.pos_.x)*2;

		//	obj_.isAlive_ = (drawPos_.x <= target_.x) ? true : false;
			break;
		}
	}

}

void BamBeam::Draw(void)
{
	if (obj_.isAlive_) {
	DrawBox(obj_.pos_.x, obj_.pos_.y, drawPos_.x, drawPos_.y+obj_.size_.y/2, GetColor(0, 200, 0), true);
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
}

