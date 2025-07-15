#include<cmath>
#include "Wavemboo.h"
#include"../../../../../Utility/ShapesPosition.h"
#include"../Attack/Takenoko.h"
#include"../../../../../Application.h"


Wavemboo::Wavemboo()
{
    image_ = LoadGraph("Data/Image/Boss/Nokopy/happa.png");
}

Wavemboo::~Wavemboo()
{
}

void Wavemboo::Init(const Vector2F* pos)
{
    AttackBase::Init(pos);
    obj_.resize(MAX_NUM);
    for (auto& o : obj_) {
        o.radius_ = 10;
        o.isAlive_ = true;
        o.isCircle_ = true;
    }
        isParry_ = true;
}

void Wavemboo::Update(void)
{
    Create();
    UpdatePositionTakenokos();
}

void Wavemboo::Draw(void)
{
    for (int i = 0; i < obj_.size(); i++) {
        if (!obj_[i].isAlive_)continue;
        DrawRotaGraph(obj_[i].pos_.x, obj_[i].pos_.y, 0.1, AsoUtility::Deg2RadF(90), image_, true);

    }
}

void Wavemboo::Release(void)
{
    DeleteGraph(image_);
}  


void Wavemboo::Off(void)
{
    for (auto& o : obj_) {
        o.isAlive_ = false;
        o.pos_ = { 0,0 };
    }
}

void Wavemboo::Create(void)
{
    static float timer = 0.0f;
    static int phase = 0;
    const float interval = 15.0f;
    static int counter = 0;

    if (!lookOn_) {
        timer = 0.0f;
        phase = 0;
        counter = 0;
        return;
    }
    // 基点座標を取得
    Vector2F basePos = *boss;
    dir_ = (basePos.x > target_.x) ? LEFT : RIGHT;

    timer += 1.0f;
    if (timer >= interval) {
        timer = 0.0f;

        // 位相を変えて配置
        float angle = static_cast<float>(phase) * (2.0f * 3.14159265f /AsoUtility::Deg2RadF(45));
        float radius = 100.0f; // 任意の半径
        Vector2F spawnPos(
            basePos.x + std::cos(angle) * radius,
            basePos.y + std::sin(angle) * radius
        );

        obj_[counter].pos_ = spawnPos;
        obj_[counter].isAlive_ = true;
        counter++;
        if (counter > 12) {
            counter = 0;
        }
    }

    phase++;
}

void Wavemboo::UpdatePositionTakenokos(void)
{
    const float moveSpeed = 15.0f;   // 移動速度
  
    for (size_t i = 0; i < obj_.size(); ++i) {
        // dir_の向きで左右移動
        float dirSign = (dir_ == LEFT) ? -1.0f : 1.0f;
        float x = obj_[i].pos_.x;
        x+=dirSign * moveSpeed ;
        float y = obj_[i].pos_.y;
        Vector2F newPos(x, y);
        obj_[i].pos_ = newPos;
    }
}
