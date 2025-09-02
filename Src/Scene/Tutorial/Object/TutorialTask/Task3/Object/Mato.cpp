#include"Mato.h"

#include"../../../../../../Utility/AsoUtility.h"

Mato::Mato()
{
}

Mato::~Mato()
{
}

void Mato::Load(void)
{
	AsoUtility::LoadImg(image_, "Data/Image/Tutorial/Task/“I.png");

	unit_.radius_ = 64.0f;
}

void Mato::Init(void)
{
	unit_.isAlive_ = true;
}

void Mato::Update(void)
{

}


void Mato::Draw(void)
{
	if (!unit_.isAlive_) { return; }
	DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 1, 0, image_, true);
}


void Mato::Release(void)
{
	DeleteGraph(image_);
}