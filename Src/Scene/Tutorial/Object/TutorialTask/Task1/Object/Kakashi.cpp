#include"Kakashi.h"

#include"../../../../../../Utility/AsoUtility.h"

Kakashi::Kakashi():
	image_(-1)
{
}

Kakashi::~Kakashi()
{
}

void Kakashi::Load(void)
{
	AsoUtility::LoadImg(image_, "Data/Image/Tutorial/Task/’|.png");

	unit_.size_ = { 75.0f,372.0f };
}

void Kakashi::Init(void)
{
	unit_.pos_ = { 800.0f,470.0f };

	unit_.isAlive_ = true;

	unit_.hp_ = HP_MAX;
}

void Kakashi::Update(void)
{
	if (unit_.inviCounter_ > 0) { unit_.inviCounter_--; }
}

void Kakashi::Draw(void)
{
	if (!unit_.isAlive_) { return; }

	if (unit_.inviCounter_ > 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); }
	DrawRotaGraphF(unit_.pos_.x + sinf(unit_.inviCounter_), unit_.pos_.y - sinf(unit_.inviCounter_), 1, 0, image_, true);
	if (unit_.inviCounter_ > 0) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }

	int sX = unit_.pos_.x - unit_.size_.x / 1.5f;
	int sY = unit_.pos_.y - (unit_.size_.y / 2) - 10;
	int eX = unit_.pos_.x + unit_.size_.x / 1.5f;
	int eY = sY + 10;

	DrawBox(sX, sY, eX, eY, 0xffffff, true);

	sX += 1; sY += 1; eX -= 1; eY -= 1;
	DrawBox(sX, sY, eX, eY, 0x000000, true);

	float size = eX - sX;
	float oneSize = (float)(size / HP_MAX);

	DrawBox(sX, sY, sX + (oneSize * unit_.hp_), eY, 0x00ff00, true);
}

void Kakashi::Release(void)
{
	DeleteGraph(image_);
}

void Kakashi::Action(void)
{
	if (--unit_.hp_ <= 0) { unit_.hp_ = 0; unit_.isAlive_ = false; }
	unit_.inviCounter_ = 10;
}