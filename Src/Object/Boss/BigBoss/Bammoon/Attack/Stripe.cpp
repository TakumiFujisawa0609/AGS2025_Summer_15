#include"Stripe.h"

#include<DxLib.h>

#include"../../../../../Manager/Camera.h"
#include"../../../../../Manager/SceneManager.h"

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
		o.pos_ = S_POS[i];

		i++;
	}

	end_ = 0;
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
				}
			}

		}
		else {
			if (o.inviCounter_ > 0) {
				if (--o.inviCounter_ <= 0) { o.isAlive_ = false; }
			}
			else {
				o.pos_.y -= SPEED;
				o.disppos_ = o.pos_ - Camera::GetInstance().GetPos();

				if (o.pos_.y <= SIZE_Y / 2) {
					o.inviCounter_ = 250;
					end_++;
					SceneManager::GetInstance().SHAKE();
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
				DrawRotaGraph(S_POS[i].x, Application::SCREEN_SIZE_Y - 128, 1, 0, nokoImg_, true);
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
	obj_.clear();

	DeleteGraph(nokoImg_);
	DeleteGraph(image_);
}

void Stripe::On(int i)
{
	if (i >= obj_.size())return;

	if (i == 0) { end_ = 0; }

	obj_[i].pos_ = S_POS[i];
	obj_[i].disppos_ = obj_[i].pos_ - Camera::GetInstance().GetPos();

	obj_[i].inviCounter_ = 50;

	obj_[i].isDraw_ = true;
}
