#include<DxLib.h>
#include "Takenoko.h"
#include"../../../../../Application.h"

Takenoko::Takenoko()
{
}

Takenoko::~Takenoko()
{
}

void Takenoko::Init(Vector2F pos)
{
 	obj_.radius_ = 10;
	obj_.pos_ = pos;
	obj_.isAlive_ = true;
}

void Takenoko::Update(void)
{
	if (obj_.pos_.x<0 || obj_.pos_.x>Application::SCREEN_SIZE_X) {
		obj_.isAlive_ = false;
	}
}

void Takenoko::Draw(void)
{
	DrawCircle(obj_.pos_.x, obj_.pos_.y, obj_.radius_, 0x000AAA);
}

void Takenoko::Release(void)
{
}
