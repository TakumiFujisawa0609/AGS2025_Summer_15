#include"Kakashi3.h"

#include"../../../../../../Utility/AsoUtility.h"

Kakashi3::Kakashi3() :
	image_(-1)
{
}

Kakashi3::~Kakashi3()
{
}

void Kakashi3::Load(void)
{
	AsoUtility::LoadImg(image_, "Data/Image/Tutorial/Task/’|.png");

	unit_.size_ = { 75.0f,372.0f };
}

void Kakashi3::Init(void)
{
	unit_.pos_ = { 800.0f,470.0f };

	unit_.isAlive_ = true;
}

void Kakashi3::Update(void)
{
	if (unit_.inviCounter_ > 0) { unit_.inviCounter_--; }
}

void Kakashi3::Draw(void)
{
	if (!unit_.isAlive_) { return; }

	if (unit_.inviCounter_ > 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); }
	DrawRotaGraphF(unit_.pos_.x + sinf(unit_.inviCounter_), unit_.pos_.y - sinf(unit_.inviCounter_), 1, 0, image_, true);
	if (unit_.inviCounter_ > 0) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
}

void Kakashi3::Release(void)
{
	DeleteGraph(image_);
}

void Kakashi3::Action(void)
{
	unit_.inviCounter_ = 10;
}