#pragma once
#include "../UnitBase.h"

class EnemyBamboo : public UnitBase
{
public:

    static constexpr float EX_SIZE = 0.25f;                 // 画像サイズの操作用

    static constexpr int HP_MAX = 50;                       // HP
    static constexpr float MOVE_SPEED = 2.0f;               // 移動速度

    static constexpr float IMAGE_SIZE_X = 180.0f;           // 画像の横サイズ
    static constexpr float IMAGE_SIZE_Y = 358.0F;           // 画像のtateサイズ

    static constexpr float RADIUS_SIZE_X = IMAGE_SIZE_X / 2;    // 横の半径
    static constexpr float RADIUS_SIZE_Y = IMAGE_SIZE_Y / 2;    // tateの半径

    static constexpr float All_SIZE_X = IMAGE_SIZE_X * EX_SIZE;     // bambooの横サイズ
    static constexpr float All_SIZE_Y = IMAGE_SIZE_Y * EX_SIZE;     // bambooのtateサイズ

    EnemyBamboo();
    ~EnemyBamboo();

    void Init()override;
    void Update()override;
    void Draw()override;
    void Release()override;

    bool DeathProcess();
    

    void SetStartPos(int ii);

    //damage == 与えられたダメージ
    void SetDmg(int damage);

    void SetTargetPos(Base target) { targetPos_ = target.pos_; }

private:

    MOVE move_;
    int modelId_;

    float rotate_;

    bool isMove_;
    
    Vector2F targetPos_;

    void Move();
    void MoveX()override;
    void MoveY()override;

    // 接地している時の数値の代入などをまとめた関数
    void IsGround(Collision::DIR dir)override;
};
