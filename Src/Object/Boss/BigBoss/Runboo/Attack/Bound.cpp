#include "Bound.h"
#include<DxLib.h>
#include"../../../../../Application.h"
#include"../../../../../Manager/Camera.h"

Bound::Bound(float moveSpeed)
{
	image_ = -1;

	moveSpeed_ = moveSpeed;
}

Bound::~Bound()
{
}

void Bound::Init(const Vector2F* pos)
{
	attackStartPos_ = *pos;

	image_ = LoadGraph("Data/Image/Boss/Runboo/Laser.png");

	obj_.resize(BOUND_BALL_MAX);

	for (auto& bound : obj_)
	{
		bound.isAlive_ = true;
		bound.size_ = { SIZE_X, SIZE_Y };
		bound.radius_ = RADIUS_SIZE;
		bound.pos_ = attackStartPos_;     // ボス座標から発射
		bound.xAccel_ = 10.0f;
		bound.yAccel_ = -15.0f;
	}

	boundCnt_ = 0;

	end_ = false;
}

void Bound::Update(Vector2F boss)
{

	for (auto& bound : obj_)
	{
		if (!bound.isAlive_) continue;

		bound.pos_.x += bound.xAccel_;
		bound.pos_.y += bound.yAccel_;

		bound.yAccel_ += 0.6f;

		if (bound.pos_.y + bound.radius_ > Application::SCREEN_SIZE_Y)
		{
			bound.pos_.y = Application::SCREEN_SIZE_Y - bound.radius_;
			bound.yAccel_ *= -1.0f;
		}

		int screenX = Camera::GetInstance().GetPos().x + Application::SCREEN_SIZE_X;
		int screenY = Camera::GetInstance().GetPos().x + 0;

		// 左右の壁
		if (bound.pos_.x + bound.radius_ > screenX)
		{
			bound.xAccel_ *= -1.0f;
		}

		if (bound.pos_.x - bound.radius_ < screenY)
		{
			bound.isAlive_ = false;
			end_ = true;
		}
	}

	ChangeDispPos();
}

void Bound::Update(void)
{
}

void Bound::Draw(void)
{
	if (end_) return;

	for (auto& bound : obj_)
	{
		if (bound.isAlive_)
		{
			//DrawCircle(bound.disppos_.x, bound.disppos_.y, bound.radius_, 0xffffff);
			DrawRotaGraph(bound.disppos_.x, bound.disppos_.y, 2.0f, 0.0f, image_, true);

			/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawCircleAA(bound.disppos_.x, bound.disppos_.y, bound.radius_, 30, 0xffffff);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
		}
	}
}

void Bound::Release(void)
{
	DeleteGraph(image_);
}

const std::vector<Base> Bound::Get() const
{
	return obj_;
}

void Bound::Hit(int i)
{
	obj_[i].isAlive_ = false;
	end_ = true;
}

bool Bound::End(void)
{
	return end_;
}

void Bound::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	for (int i = 0; i < BOUND_BALL_MAX; i++) {
		obj_[i].disppos_ = obj_[i].pos_ - camera.GetPos();
	}
}