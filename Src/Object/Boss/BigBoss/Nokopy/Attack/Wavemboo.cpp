#include<cmath>
#include "Wavemboo.h"
#include"../../../../../Utility/ShapesPosition.h"
#include"../Attack/Takenoko.h"
#include"../../../../../Application.h"


Wavemboo::Wavemboo()
{
}

Wavemboo::~Wavemboo()
{
}

void Wavemboo::Init(const Vector2F* pos)
{
        Takenoko* t = nullptr;
    AttackBase::Init(pos);
    for (int i = 0; i < MAX_NUM; i++) {
        t = new Takenoko();
    }
}

void Wavemboo::Update(void)
{
    Create();
    UpdatePositionTakenokos();
    for (auto& t : takenokos_) {
        t->Update();
    }
}

void Wavemboo::Draw(void)
{
    for (auto& t : takenokos_) {
        t->Draw();
    }
}

void Wavemboo::Release(void)
{
    for (auto& t : takenokos_) {
        t->Release();
    }
}

std::vector<Base> Wavemboo::Get(void)  
{  
    std::vector<Base> ret;  
    for (auto* t : takenokos_) {  
        if (t) {  
            ret.push_back(t->GetBase()); 
        }  
    }  
    return ret;  
}       


void Wavemboo::Create(void)
{
    static float timer = 0.0f;
    static int phase = 0;
    const float interval = 15.0f;

    if (!lookOn_) {
        timer = 0.0f;
        phase = 0;
        return;
    }
    // 基点座標を取得
    Vector2F basePos = *boss;
    dir_ = (basePos.x > target_.x) ? LEFT : RIGHT;

    timer += 1.0f;
    if (timer >= interval) {
        timer = 0.0f;

        // 位相を変えて配置
        float angle = static_cast<float>(phase) * (2.0f * 3.14159265f / 7); 
        float radius = 100.0f; // 任意の半径
        Vector2F spawnPos(
            basePos.x + std::cos(angle) * radius,
            basePos.y + std::sin(angle) * radius
        );

        // 画面外のTakenokoを再利用
        Takenoko* t = nullptr;
        for (auto& tk : takenokos_) {
            Base b = tk->GetBase();
            // 存在していないインスタンスを再利用
            if (!b.isAlive_) {
                t = tk;
                break;
            }
        }
        if (t) {   
            t->Init(spawnPos);
        } else {
            t->Init(spawnPos);
            takenokos_.push_back(t);
        }

        phase = (phase + 1) % MAX_NUM; // 位相を進める
    }
}

void Wavemboo::UpdatePositionTakenokos(void)
{
    static float phaseTimer = 0.0f;
    static float phaseOffset = 0.0f;
    const float phaseSpeed = 0.01f; // 位相の進む速さ
    const float moveSpeed = 10.0f;   // 移動速度
    const float radius = 5.0f;     // 半径
    // boss（親）の座標
    Vector2F basePos = *boss;

    // 時間経過で位相を進める
    phaseTimer += 1.0f;
    phaseOffset += phaseSpeed;

    for (size_t i = 0; i < takenokos_.size(); ++i) {
        Takenoko* t = takenokos_[i];
        if (!t) continue;

        // dir_の向きで左右移動
        float dirSign = (dir_ == LEFT) ? -1.0f : 1.0f;

        // 各Takenokoの位相を計算
        float angle = phaseOffset + static_cast<float>(i) * (2.0f * 3.14159265f / MAX_NUM);
        float x = takenokos_[i]->GetBase().pos_.x;
        x+=dirSign * moveSpeed ;
        /*float y = takenokos_[i]->GetBase().pos_.y;
        y+=std::sin(angle) * radius;*/
        float y = takenokos_[i]->GetBase().pos_.y;
        Vector2F newPos(x, y);
        t->SetPos(newPos);
    }
}
