#include "WeakBullet.h"
#include"../../../../../Manager/Camera.h"
#include"../../../../../Application.h"
#include"../../../../../Manager/Camera.h"

WeakBullet::WeakBullet(float moveSpeed)
{
    moveSpeed_ = moveSpeed;
}

WeakBullet::~WeakBullet()
{
}

void WeakBullet::Init(const Vector2F* pos)
{
    shotTimer_ = 0;
    canShot_ = true;

    obj_.pos_ = *pos;

    for (int i = 0; i < BULLET_NUM; i++) {
        bullets_[i].isAlive_ = false;
        bullets_[i].isDraw_ = false;
        bullets_[i].pos_ = *pos;
        bullets_[i].radius_ = 30;
        bullets_[i].size_ = {SIZE_X, SIZE_Y};
    }

    endCnt_ = 0;
}

void WeakBullet::Update(Vector2F boss)
{
    obj_.pos_.x = boss.x;

    if (!canShot_) {
        // 発射不可ならタイマー減算
        if (shotTimer_ > 0) {
            shotTimer_--;
        }
        else {
            // タイマー切れたら再発射可能にする
            canShot_ = true;
        }
    }

    if (canShot_) {
        // 発射処理（すべての弾が非アクティブなら発射）
        bool allDead = true;
        for (int i = 0; i < BULLET_NUM; i++) {
            if (bullets_[i].isAlive_) {
                allDead = false;
                break;
            }
        }

        if (allDead) {
            // 弾を初期位置にセットして速度を付ける（発射）
            for (int i = 0; i < BULLET_NUM; i++) {
                bullets_[i].pos_ = obj_.pos_;
                bullets_[i].isAlive_ = true;
                bullets_[i].isDraw_ = true;
                bullets_[i].xAccel_ = MOVE_SPEED;
                bullets_[i].yAccel_ = (i - BULLET_NUM / 2) * 0.2f;  // 少し上下散らし
            }
            // 発射後はタイマー開始、発射不可にする
            shotTimer_ = SHOT_INTERVAL;
            canShot_ = false;
            endCnt_++;
        }
    }

    // 弾の移動処理
    for (int i = 0; i < BULLET_NUM; i++) {
        if (!bullets_[i].isAlive_) continue;

        bullets_[i].pos_.x += bullets_[i].xAccel_;
        bullets_[i].pos_.y += bullets_[i].yAccel_;

        if (bullets_[i].pos_.x > Camera::GetInstance().GetPos().x + Application::SCREEN_SIZE_X || bullets_[i].pos_.y < 0 || bullets_[i].pos_.y > 720) {
            bullets_[i].isAlive_ = false;
            bullets_[i].isDraw_ = false;
        }

        bullets_[i].disppos_ = bullets_[i].pos_;
    }

    ChangeDispPos();

    AttackBase::Update();
}

void WeakBullet::Update()
{
 
}

void WeakBullet::Draw(void)
{
    for (int i = 0; i < BULLET_NUM; i++) {
        if (!bullets_[i].isAlive_) continue;
        DrawCircle((int)bullets_[i].disppos_.x, (int)bullets_[i].disppos_.y, (int)bullets_[i].radius_, GetColor(255, 255, 0), true);
    }
}

void WeakBullet::Release(void)
{
}

const std::vector<Base> WeakBullet::Get() const
{
    std::vector<Base> ret;
    for (int i = 0; i < BULLET_NUM; i++) {
        ret.emplace_back(bullets_[i]);
    }
    return ret;
}

void WeakBullet::Hit(void)
{

}

bool WeakBullet::End(void)
{
    if (endCnt_ >= 3)
    {
        return true;
    }
    return false;
}

void WeakBullet::ChangeDispPos()
{
    auto& camera = Camera::GetInstance();
    for (int i = 0; i < BULLET_NUM; i++) {
        bullets_[i].disppos_ = bullets_[i].pos_ - camera.GetPos();
    }
}