#include"Stripe.h"

#include<DxLib.h>

#include"../../../../../Manager/Camera.h"
#include"../../../../../Manager/SceneManager.h"
#include"../../../../../Manager/SoundManager.h"

Stripe::Stripe()
{
}

Stripe::~Stripe()
{
}

void Stripe::Init(const Vector2F* pos) 
{
	bossPos_ = pos;

	image_ = LoadGraph("Data/Image/Boss/Bammoon/AttackEffect/Stripe/Stripe.png");
	nokoImg_ = LoadGraph("Data/Image/Boss/Bammoon/AttackEffect/Stripe/takenoko.png");

	obj_.resize(NUM);

	int i = 0;
	for (auto& o : obj_) {
		o.size_ = { SIZE_X,SIZE_Y };

		o.isAlive_ = false;
		o.inviCounter_ = 0;
		i++;
	}

	end_ = 0;

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::BAMMOONLANDING);
}

void Stripe::Update(void) 
{
	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_) {
			if (o.isDraw_) {
				if (--o.inviCounter_ <= 0) {
					o.inviCounter_ = 0;
					o.isDraw_ = false;
					o.isAlive_ = true;
					SoundManager::GetIns().Play(SoundManager::SOUND::BAMMOONLANDING, true, 200);
				}
			}

		}
		else {
			if (o.inviCounter_ > 0) {
				o.inviCounter_ -= 5;
				if (o.inviCounter_ <= 0) { o.isAlive_ = false; }
			}
			else {
				o.pos_.y -= SPEED;
				o.disppos_ = o.pos_ - Camera::GetInstance().GetPos();

				if (o.pos_.y <= SIZE_Y / 2) {
					o.inviCounter_ = 250;
					end_++;
					SceneManager::GetIns().Shake();
				}
			}
		}
	}
}

void Stripe::Draw(void)
{
	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_) {
			if (o.isDraw_) {
				DrawRotaGraph(((side_) ? SIZE_X * (i + 1) : Application::SCREEN_SIZE_X - (SIZE_X * (i + 1))), Application::SCREEN_SIZE_Y - 128, 1, 0, nokoImg_, true);
			}
		}
		else {
			if (o.inviCounter_ > 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, o.inviCounter_);
			DrawRotaGraph(o.disppos_.x, o.disppos_.y, 1, 0, image_, true);
			if (o.inviCounter_ > 0)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

void Stripe::Release(void) 
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BAMMOONLANDING);

	obj_.clear();

	DeleteGraph(nokoImg_);
	DeleteGraph(image_);
}

void Stripe::On(int i)
{
	if (i >= obj_.size())return;

	if (i == 0) {
		side_ = (bool)GetRand(1);
		end_ = 0;
	}
	obj_[i].pos_ = { ((side_) ? SIZE_X * (i + 1) : Application::SCREEN_SIZE_X - (SIZE_X * (i + 1)))  , POS_Y };
	obj_[i].disppos_ = obj_[i].pos_ - Camera::GetInstance().GetPos();

	obj_[i].inviCounter_ = 50;

	obj_[i].isDraw_ = true;
}
