#include "Weakness.h"
#include"../../../UnitBase.h"
#include"../../../../Manager/Camera.h"

Weakness::Weakness()
{
}

Weakness::~Weakness()
{
}

//èâä˙âª
void Weakness::Init(Vector2F disppos)
{

	Camera::CreateInstance();

	unit_.disppos_ = disppos;
	unit_.size_ = { SIZE_X,SIZE_Y };

	//âÊñ ÇÃç∂í[Çå©ÇÈ
	Vector2F start_;
	start_.x = Camera::GetInstance().GetPos().x;
	start_.y = Camera::GetInstance().GetPos().y;
	unit_.disppos_ + start_;

	unit_.isAlive_ = true;

}

void Weakness::Update()
{
	cnt_ += 0.1f;

	float move = sinf(cnt_) * AMPLITUDE; //è„â∫Ç…ìÆÇ≠
	unit_.disppos_.y += move;

}

void Weakness::Draw()
{
	DrawBox(
		unit_.disppos_.x,
		unit_.disppos_.y,
		unit_.disppos_.x + unit_.size_.x,
		unit_.disppos_.y + unit_.size_.y,
		RGB(255, 0, 255),
		true
	);

	DrawString(100, 100, "asiodhfaposh", RGB(0, 0, 0));
}

void Weakness::Release()
{
	Camera::DeleteInstance();
}
