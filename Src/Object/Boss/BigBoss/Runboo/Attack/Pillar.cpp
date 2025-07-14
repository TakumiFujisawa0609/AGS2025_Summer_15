#include "Pillar.h"
#include<DxLib.h>
#include"../../../../../Manager/Camera.h"

Pillar::Pillar(float moveSpeed)
{
	moveSpeed_ = moveSpeed;
}

Pillar::~Pillar()
{
}

void Pillar::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Pillar.png").c_str());

	obj_.resize(PILLAR_MAX);

	for (auto& pil : obj_)
	{
		pil.isAlive_ = true;
		pil.pos_ = { target_->x, -SIZE_Y * 2 }; // 画面外の上から開始
		pil.size_ = { SIZE_X, SIZE_Y };
		pil.isDraw_ = false;

		ySpeed_ = 0.0f;
		isFalling_ = false;
	}

	cnt_ = 0;
	end_ = false;
}

void Pillar::Update(Vector2F boss)
{
	cnt_++;

	for (auto& pil : obj_)
	{
		if (cnt_ == 60) // 警告終了タイミング
		{
			isFalling_ = true;
		   	ySpeed_ = 0.0f;

			// ターゲット位置を記録（予告位置として）
			warnPos_ = *target_;
		}

		if (cnt_ < 60)
		{
			// 警告中（落下予告）：ターゲットに合わせる
			pil.pos_.x = target_->x;
			isFalling_ = false;
		}
		else if (cnt_ == 60)
		{
			// 落下開始
			isFalling_ = true;
			ySpeed_ = 0.0f;
		}
		else if (isFalling_)
		{
			// 落下中
			ySpeed_ += 1.5f; // 加速度（重力風）
			pil.pos_.y += ySpeed_;

			// 地面に着いたら着弾
			if (pil.pos_.y >= target_->y)
			{
				pil.pos_.y = target_->y;
				pil.isDraw_ = true;     // 攻撃判定ON
				isFalling_ = false; // 落下終了
			}
		}
		else
		{
			// 着弾後の待機
			if (cnt_ > 180) {
				end_ = true;
			}
		}

		if (end_)pil.isAlive_ = false;
	}

	ChangeDispPos();

}

void Pillar::Update()
{
}

void Pillar::Draw(void)
{
	for (auto& pil : obj_)
	{
		if (!pil.isAlive_) return;

		if (!pil.isDraw_)
		{
			if ((cnt_ / 10) % 2 == 0 && !isFalling_) {
				DrawBox(
					(target_->x - Camera::GetInstance().GetPos().x) - 50,
					(target_->y - Camera::GetInstance().GetPos().y) - pil.size_.y,
					(target_->x - Camera::GetInstance().GetPos().x) + 50,
					(target_->y - Camera::GetInstance().GetPos().y) + pil.size_.y,
					RGB(0, 0, 255), true
				);
			}
			else if (isFalling_) {
				DrawRotaGraph(
					pil.disppos_.x,
					pil.disppos_.y,
					1.0f, 0.0f,
					image_,
					true
				);
			}
		}
		else
		{
			DrawRotaGraph(
				pil.disppos_.x,
				pil.disppos_.y,
				1.0f, 0.0f,
				image_,
				true
			);
		}
	}
}

void Pillar::Release(void)
{
	DeleteGraph(image_);
}

const std::vector<Base> Pillar::Get() const
{
	return obj_;
}

void Pillar::Hit(int i)
{
}

bool Pillar::End(void)
{
	return end_;
}

void Pillar::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	for (int i = 0; i < PILLAR_MAX; i++) {
		obj_[i].disppos_ = obj_[i].pos_ - camera.GetPos();
	}
}