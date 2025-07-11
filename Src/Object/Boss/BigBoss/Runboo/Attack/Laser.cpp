#include "Laser.h"
#include"../../../../../Application.h"
#include"../../../../../Manager/Camera.h"

Laser::Laser(float moveSpeed)
{

}

Laser::~Laser()
{
}

void Laser::Init(const Vector2F* pos)
{
	//image_ = LoadGraph();

	attackStartPos_ = *pos;

	obj_.resize(MAX_NUM);

	for (auto& laser : obj_)
	{
		laser.isAlive_ = true;
		laser.isDraw_ = false;
		laser.size_ = { SIZE_X, SIZE_Y };
		laser.pos_ = attackStartPos_;
	}

	cnt_ = 0;
}

void Laser::Update(Vector2F boss)
{
    attackStartPos_ = boss;
	attackStartPos_.x += 1.0f;

    for (auto& laser : obj_)
    {
        if (!laser.isAlive_) continue;

        if (!laser.isDraw_)
        {
            laser.pos_ = attackStartPos_;  // © C³‚±‚±
            laser.isDraw_ = true;
        }
        else
        {
            laser.pos_.x += ATTACK_SPEED;
            if (laser.pos_.x > Application::SCREEN_SIZE_X)
            {
                laser.isDraw_ = false;
            }
        }
    }

    ChangeDispPos();

}

void Laser::Update(void) {}

void Laser::Draw(void)
{
	for (auto& laser : obj_)
	{
		if (laser.isDraw_)
		{
			DrawFormatString(0, 0, GetColor(255, 255, 255), "x: %.1f y: %.1f", laser.disppos_.x, laser.disppos_.y);
			DrawBox(
				laser.disppos_.x - SIZE_X / 2,
				laser.disppos_.y - SIZE_Y / 2,
				laser.disppos_.x + SIZE_X / 2,
				laser.disppos_.y + SIZE_Y / 2,
				RGB(255, 0, 0), true
			);
		}

	}
}

void Laser::Release(void)
{
	//DeleteGraph(image_);
}

const std::vector<Base> Laser::Get() const
{
	return obj_;
}

void Laser::Hit(int i)
{
	obj_[i].isAlive_ = false;
}

bool Laser::End(void)
{

	return false;
}

void Laser::SetIsAlive(bool isAlive)
{

}


void Laser::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	for (int i = 0; i < MAX_NUM; i++) {
		obj_[i].disppos_ = obj_[i].pos_ - camera.GetPos();
	}
}