#include"BlastEffect.h"

#include<DxLib.h>

#include"../../../Manager/Camera.h"

BlastEffect::BlastEffect()
{
}

BlastEffect::~BlastEffect()
{
}

void BlastEffect::Load(std::vector<int> image)
{
	this->image_ = image;
}

void BlastEffect::On(Vector2F pos)
{
	this->pos_ = pos;
	this->isAlive_ = true;
	this->animeCounter_ = 0;
	this->animeInterval_ = 0;
}

void BlastEffect::Update(void)
{
	if (++animeInterval_ > ANIME_SPEED) {
		animeInterval_ = 0;
		if (++animeCounter_ > image_.size()) {
			isAlive_ = false;
			animeCounter_ = 0;
		}
	}
}

void BlastEffect::Draw(void)
{
	auto& camera = Camera::GetInstance();
	Vector2F point = pos_ - camera.GetPos();
	DrawRotaGraph(point.x, point.y, 0.5, 0, image_[animeCounter_], true);
}

void BlastEffect::Release(void)
{
}
