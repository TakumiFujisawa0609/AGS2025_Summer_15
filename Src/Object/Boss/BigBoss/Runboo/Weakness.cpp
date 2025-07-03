#include "Weakness.h"
#include"../../../UnitBase.h"
#include"../../../../Manager/Camera.h"

Weakness::Weakness()
{
}

Weakness::~Weakness()
{
}

//初期化
void Weakness::Init(Vector2F disppos)
{
	Camera::CreateInstance();

	unit_.disppos_ = disppos;
	unit_.size_ = { SIZE_X,SIZE_Y };

	//画面の左端を見る
	start_.x = Camera::GetInstance().GetPos().x;
	start_.y = Camera::GetInstance().GetPos().y;

	cnt_ = GetRand(100);

	unit_.disppos_ + start_;
	unit_.hp_ = HP_MAX;
	unit_.isAlive_ = true;

}

void Weakness::Update()
{
	cnt_ += 0.1f;

	float move = sinf(cnt_) * AMPLITUDE; //上下に動く
	unit_.disppos_.x += move;
	unit_.disppos_.y += move;

}

void Weakness::Draw()
{
	//ボス描画（とりあえずDrawBox）
	DrawBox(
		unit_.disppos_.x,
		unit_.disppos_.y,
		unit_.disppos_.x + unit_.size_.x,
		unit_.disppos_.y + unit_.size_.y,
		RGB(255, 0, 255),
		true
	);

	HpDraw();
}

void Weakness::Release()
{
	Camera::DeleteInstance();
}

void Weakness::Init()
{
}

void Weakness::Idle(void)
{
}

void Weakness::Move(void)
{
}

void Weakness::Attack(void)
{
}

void Weakness::Damage(void)
{
}

void Weakness::Death(void)
{
}

std::vector<Base*> Weakness::GetObj(void)
{
	return std::vector<Base*>();
}

void Weakness::HpDraw(void)
{
	DrawBar(
		unit_.disppos_.x - HP_POS_X,
		unit_.disppos_.y - HP_POS_Y,
		unit_.disppos_.x + unit_.size_.x + 10,
		unit_.disppos_.y - HP_POS_Y / 2,
		unit_.hp_,HP_MAX,
		RGB(0, 0, 200)
	);
}
