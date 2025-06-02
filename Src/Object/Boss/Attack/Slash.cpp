#include"Slash.h"

#include<DxLib.h>

#include"../../../Manager/Camera.h"

Slash::Slash()
{
	image_ = -1;
}

Slash::~Slash()
{
}

void Slash::Init(const Vector2F* pos)
{
	image_ = LoadGraph("Data/Image/Boss/Slash.png");

	AttackBase::Init(pos);
	obj_.radius_ = 120.0f;
	obj_.size_ = { 240.0f,240.0f };
}

void Slash::Update()
{

	if (obj_.isAlive_) {
		switch (dir_)
		{
		case Slash::LEFT:
			obj_.pos_ = { boss->x - 70.0f,boss->y };
			isSlash = true;
			break;
		case Slash::RIGHT:
			obj_.pos_ = { boss->x + 70.0f,boss->y };
			isSlash = false;
			break;
		}

		attackCounter_++;

		// エフェクトを時間分表示
		if (attackCounter_ > ATTACK_DRAW_TIME) {
			obj_.isDraw_ = false;
		}
		
		// 攻撃終了処理
		if (attackCounter_ > ATTACK_TIME) {
		
			obj_.isAlive_ = false;
			end_ = true;
		}
	}

	AttackBase::Update();
}

void Slash::Draw()
{
	if (obj_.isAlive_)
	{
		if (obj_.isDraw_) {
			DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, 1.0f, 0.0f, image_, true, isSlash);
		}
	}
}

void Slash::Release()
{
	DeleteGraph(image_);
}

void Slash::SetTarget(const AttackBase::DIR dir)
{
	dir_ = dir;
}
