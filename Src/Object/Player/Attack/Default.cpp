#include"Default.h"

#include<DxLib.h>

#include"../Player.h"

Default::Default(Vector2F* pPos, AsoUtility::DIRECTION* dir) : PlayerAttackBase(pPos, dir)
{

}

Default::~Default()
{
}

void Default::Init()
{
	obj_.radius_ = 90.0f;
	obj_.size_ = { obj_.radius_,obj_.radius_ };
}

void Default::Update()
{
	if (obj_.isAlive_) {

		obj_.pos_ = *pPos_;

		switch (*dir_)
		{
		case AsoUtility::DIRECTION::E_DIR_LEFT:
			obj_.pos_.x -= Player::LOAD_SIZE_X / 2;
			break;
		case AsoUtility::DIRECTION::E_DIR_RIGHT:
			obj_.pos_.x += Player::LOAD_SIZE_X / 2;
			break;
		default:
			break;
		}
	}

	ChangeDispPos();
}

void Default::Draw()
{
	if (obj_.isAlive_) {
		//DrawCircleAA(obj_.disppos_.x, obj_.disppos_.y, obj_.radius_, 30, RGB(255, 0, 0));
	}
}

void Default::Release()
{
}