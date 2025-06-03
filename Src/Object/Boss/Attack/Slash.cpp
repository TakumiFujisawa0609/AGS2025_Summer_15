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
	LoadDivGraph("Data/Image/Boss/SlashAnim.png", ANIM_ALL,
		X_NUM, Y_NUM, X_SIZE, Y_SIZE, img);
	

	AttackBase::Init(pos);
	obj_.radius_ = 120.0f;
	obj_.size_ = { 240.0f,240.0f };
	animCounter_ = 0;
}

void Slash::Update()
{

	if (obj_.isAlive_) {
		switch (dir_)
		{
		case Slash::LEFT:
			obj_.pos_ = { boss->x - 70.0f,boss->y };
			isTurn = true;
			break;
		case Slash::RIGHT:
			obj_.pos_ = { boss->x + 70.0f,boss->y };
			isTurn = false;
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
			animCounter_ = 0;
			end_ = true;
		}
	}

	AttackBase::Update();
}

void Slash::Draw()
{
	if (obj_.isAlive_)
	{
		if (obj_.isDraw_ && animCounter_ <= ANIM_ALL) {
			animCounter_++;
			DrawRotaGraph(obj_.disppos_.x += isTurn ? -(X_SIZE / 2) :  X_SIZE / 2, obj_.disppos_.y, 1.0f, 0.0f, img[animCounter_], true, isTurn);
			//DrawGraph(obj_.disppos_.x, obj_.disppos_.y - Y_SIZE / 2, img[animCounter_], true);
		}
		
	}
}

void Slash::Release()
{
	for (int ii = 0; ii < ANIM_ALL; ii++) {
		DeleteGraph(img[ii]);
	}
	DeleteGraph(image_);
}

void Slash::SetTarget(const AttackBase::DIR dir)
{
	dir_ = dir;
}
