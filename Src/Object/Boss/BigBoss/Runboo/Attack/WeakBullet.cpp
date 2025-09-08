#include "WeakBullet.h"
#include"../../../../../Manager/Camera.h"
#include"../../../../../Application.h"

WeakBullet::WeakBullet(float moveSpeed)
{
    moveSpeed_ = moveSpeed;
}

WeakBullet::~WeakBullet()
{
}

void WeakBullet::Init(const Vector2F* pos)
{
    LoadDivGraph(
        (Application::PATH_IMAGE + "Boss/Runboo/Bullet.png").c_str(),
        NUM_MAX, NUM_X, NUM_Y,
        IMAGE_SIZE_X, IMAGE_SIZE_Y,
        imageArray
    );

    shotTimer_ = 0;
    canShot_ = true;
    rotate_ = 0;
    arrayIndex_ = 0;
    endCnt_ = 0;

    obj_.clear();
    obj_.resize(BULLET_NUM); // Åöå≈íËí∑Ç≈ämï€

    for (auto& b : obj_) {
        b.isAlive_ = false;
        b.isDraw_ = false;
    }
}

void WeakBullet::Update(Vector2F boss, float moveSpeed)
{
    moveSpeed_ = moveSpeed;
    rotate_ += 0.05f;

    if (!canShot_) {
        if (shotTimer_ > 0) {
            shotTimer_--;
        }
        else {
            canShot_ = true;
        }
    }

    if (canShot_) {
        // Ç±Ç±Ç≈íeÇàÍêƒÇ…î≠éÀÅiêVãKê∂ê¨Åj
        for (int i = 0; i < BULLET_NUM; i++) {
            obj_[i].isAlive_ = true;
            obj_[i].isDraw_ = true;
            obj_[i].pos_ = boss;
            obj_[i].radius_ = 30;
            obj_[i].size_ = { SIZE_X, SIZE_Y };
            obj_[i].xAccel_ = BULLET_SPEED;
            obj_[i].yAccel_ = (i - BULLET_NUM / 2) * 0.2f;
        }
        shotTimer_ = SHOT_INTERVAL;
        canShot_ = false;
        endCnt_++;
    }

    // íeÇÃà⁄ìÆ
    for (auto& b : obj_) {
        if (!b.isAlive_) continue;

        b.pos_.x += b.xAccel_ * ((moveSpeed_ == 5) ? 2 : 1);
        b.pos_.y += b.yAccel_ * 2;

        if (b.pos_.x > Camera::GetInstance().GetPos().x + Application::SCREEN_SIZE_X ||
            b.pos_.y < 0 || b.pos_.y > Application::SCREEN_SIZE_Y)
        {
            b.isAlive_ = false;
            b.isDraw_ = false;
        }

        b.disppos_ = b.pos_ - Camera::GetInstance().GetPos();
    }

    arrayIndex_++;
    if (arrayIndex_ >= NUM_MAX - 1) arrayIndex_ = 0;
}

void WeakBullet::Update() {}

void WeakBullet::Draw(void)
{
    for (auto& b : obj_) {
        if (!b.isAlive_) continue;
        DrawRotaGraph(
            b.disppos_.x,
            b.disppos_.y,
            IMAGE_BIG_RATE, 0.0f,
            imageArray[arrayIndex_],
            true
        );
    }
}

void WeakBullet::Release(void)
{
    for (int i = 0; i < NUM_MAX; i++) {
        DeleteGraph(imageArray[i]);
    }
    obj_.clear();
}

const std::vector<Base> WeakBullet::Get() const
{
    return obj_;
}

void WeakBullet::Hit(int i)
{
    if (i < 0 || i >= obj_.size()) return;
    obj_[i].isAlive_ = false;
    obj_[i].isDraw_ = false;
}

bool WeakBullet::End(void)
{
    return (endCnt_ >= 3);
}

void WeakBullet::SetIsAlive(bool isAlive)
{
    for (auto& b : obj_) {
        b.isAlive_ = isAlive;
        b.isDraw_ = isAlive;
    }
    endCnt_ = 0;
}

void WeakBullet::ChangeDispPos()
{
    auto& camera = Camera::GetInstance();
    for (auto& b : obj_) {
        b.disppos_ = b.pos_ - camera.GetPos();
    }
}
