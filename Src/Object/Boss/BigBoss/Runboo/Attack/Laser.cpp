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
    attackStartPos_ = *pos;

    obj_.resize(MAX_NUM);

    for (auto& laser : obj_)
    {
        laser.isAlive_ = false;
        laser.size_ = { SIZE_X, SIZE_Y };
        laser.pos_ = attackStartPos_;
        laser.isDraw_ = false;
    }

    cnt_ = 0;
    shootTimer_ = 0;
    nextIndex_ = 0;
    fireCount_ = 0;
    end_ = false;  // ‰Šú‰»
}

void Laser::Update(Vector2F boss)
{
    shootTimer_++;
    if (shootTimer_ >= INTERVAL && nextIndex_ < MAX_NUM)
    {
        if (!obj_[nextIndex_].isAlive_)
        {
            obj_[nextIndex_].isAlive_ = true;
            obj_[nextIndex_].pos_ = boss;

            Vector2F dir = *target_ - boss;
            float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
            if (len != 0)
            {
                dir.x /= len;
                dir.y /= len;
            }

            obj_[nextIndex_].xAccel_ = dir.x * LASER_SPEED;
            obj_[nextIndex_].yAccel_ = dir.y * LASER_SPEED;

            nextIndex_++;
            shootTimer_ = 0;
        }

        if (nextIndex_ >= MAX_NUM)
        {
            fireCount_++;
        }
    }

    for (auto& laser : obj_)
    {
        if (!laser.isAlive_) continue;

        laser.pos_.x += laser.xAccel_;
        laser.pos_.y += laser.yAccel_;

        if (laser.pos_.y < UPPER_BOUND)
        {
            laser.pos_.y = UPPER_BOUND;
            laser.yAccel_ *= -1;
        }
        else if (laser.pos_.y > LOWER_BOUND)
        {
            laser.pos_.y = LOWER_BOUND;
            laser.yAccel_ *= -1;
        }

        if (laser.pos_.x > Camera::GetInstance().GetPos().x + Application::SCREEN_SIZE_X)
        {
            laser.isAlive_ = false;
            if (fireCount_ >= 2)
            {
                end_ = true;
            }
        }

        if (end_)
        {
            for (int i = 0; i < obj_.size(); i++)
            {
                laser.isAlive_ = false;
            }
        }
    }

    bool allInactive = true;
    for (const auto& laser : obj_)
    {
        if (laser.isAlive_)
        {
            allInactive = false;
            break;
        }
    }

    if (allInactive)
    {
        nextIndex_ = 0;
    }

    ChangeDispPos();

    
}

void Laser::Update(void) {}

void Laser::Draw(void)
{
	for (auto& laser : obj_)
	{
		if (laser.isAlive_)
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
	return end_;
}

void Laser::SetIsAlive(bool isAlive)
{
    for (auto laser : obj_)
    {
        laser.isAlive_ = isAlive;
    }
}


void Laser::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	for (int i = 0; i < MAX_NUM; i++) {
		obj_[i].disppos_ = obj_[i].pos_ - camera.GetPos();
	}
}