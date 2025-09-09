#include "Spiral.h"
#include"../../../../../Manager/Camera.h"

Spiral::Spiral(float moveSpeed)
{
    arrayIndex_ = 0;
    angleOffset_ = 0;
}

Spiral::~Spiral()
{
}

void Spiral::Init(const Vector2F* pos)
{
    startPos_ = *pos;
    arrayIndex_ = 0;
    angleOffset_ = 0;
    fireCount_ = 0;

    //LoadDivGraph(
    //    (Application::PATH_IMAGE + "Boss/Runboo/Bullet.png").c_str(),
    //    IMAGE_NUM, IMAGE_NUM, 1,
    //    SIZE_X, SIZE_Y,
    //    imageArray_
    //);

    obj_.clear();
    obj_.resize(BULLET_NUM);

    for (auto& sp : obj_)
    {
        sp.isAlive_ = false;
        sp.isDraw_ = false;
        sp.size_ = { SIZE_X, SIZE_Y };
        sp.radius_ = RADIUS_SIZE;
        sp.pos_ = startPos_;
    }

    end_ = false;
}

void Spiral::Update(Vector2F boss, float moveSpeed)
{
    if (end_) return;

    shootTimer_++;
    // 発射間隔（必要なら定数 INTERVAL を作る）
    if (shootTimer_ >= 10 && fireCount_ < BULLET_NUM)
    {
        // 空いている弾を発射
        for (int i = 0; i < BULLET_NUM; i++)
        {
            Base& sp = obj_[i];
            if (!sp.isAlive_)
            {
                sp.isAlive_ = true;
                sp.isDraw_ = true;
                sp.pos_ = boss;

                float angle = (2.0f * DX_PI_F / BULLET_NUM) * i + angleOffset_;
                sp.xAccel_ = cosf(angle);
                sp.yAccel_ = sinf(angle);

                fireCount_++;
                shootTimer_ = 0;
                break;
            }
        }
    }

    angleOffset_ += 0.05f;

    // 弾の移動
    for (auto& sp : obj_)
    {
        if (!sp.isAlive_) continue;

        sp.pos_.x += sp.xAccel_ * BULLET_SPEED * ((moveSpeed == 5) ? 2 : 1);
        sp.pos_.y += sp.yAccel_ * BULLET_SPEED * ((moveSpeed == 5) ? 2 : 1);

        // 画面外チェック
        if (sp.pos_.x < Camera::GetInstance().GetPos().x || sp.pos_.x > Camera::GetInstance().GetPos().x + Application::SCREEN_SIZE_X ||
            sp.pos_.y < 0 || sp.pos_.y > Application::SCREEN_SIZE_Y)
        {
            sp.isAlive_ = false;
            sp.isDraw_ = false;
        }

        sp.disppos_ = sp.pos_ - Camera::GetInstance().GetPos();
    }

    // 発射済みが20発で終了
    if (fireCount_ >= BULLET_NUM && std::all_of(obj_.begin(), obj_.end(), [](const Base& b) { return !b.isAlive_; }))
    {
        end_ = true;
    }

    ChangeDispPos();
}

void Spiral::Draw()
{
    for (auto& sp : obj_)
    {
        if (!sp.isAlive_) continue;

        //DrawRotaGraph(
        //    b.disppos_.x,
        //    b.disppos_.y,
        //    IMAGE_BIG_RATE, 0.0f,
        //    imageArray_[arrayIndex_],
        //    TRUE
        //);

        DrawCircle(sp.disppos_.x, sp.disppos_.y,sp.radius_, 0xffffff, true);
    }
}

void Spiral::Release()
{
    for (int i = 0; i < IMAGE_NUM; i++)
        DeleteGraph(imageArray_[i]);

    obj_.clear();
}

const std::vector<Base> Spiral::Get() const
{
    return obj_;
}

void Spiral::Hit(int i)
{
    if (i < 0 || i >= obj_.size()) return;
    obj_[i].isAlive_ = false;
    obj_[i].isDraw_ = false;
}

void Spiral::SetIsAlive(bool isAlive)
{
    //for (auto& b : obj_)
    //{
    //    b.isAlive_ = isAlive;
    //    b.isDraw_ = isAlive;
    //    b.pos_ = startPos_;
    //}
}

void Spiral::ChangeDispPos()
{
    auto& camera = Camera::GetInstance();
    for (auto& sp : obj_)
        sp.disppos_ = sp.pos_ - camera.GetPos();
}