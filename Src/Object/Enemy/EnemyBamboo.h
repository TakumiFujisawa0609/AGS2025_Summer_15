#pragma once
#include "../UnitBase.h"

class EnemyBamboo : public UnitBase
{
public:
    static constexpr int HP_MAX = 50;
    static constexpr float MOVE_SPEED = 2.0f;
    static constexpr float SIZE_X = 320.0f;
    static constexpr float SIZE_Y = 358.0F;
    static constexpr float RADIUS_SIZE_X = SIZE_X / 2;
    static constexpr float RADIUS_SIZE_Y = SIZE_Y / 2;
    static constexpr float EX_SIZE = 0.3;               // 画像サイズの操作用
    static constexpr float All_SIZE_X = RADIUS_SIZE_X * EX_SIZE;
    static constexpr float All_SIZE_Y = RADIUS_SIZE_Y * EX_SIZE;
    static constexpr int ENEMYBAMBOO_RADIUS = 20;


    EnemyBamboo();
    ~EnemyBamboo();

    void Init()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    
    Base GetBase() { return unit_; }

    void SetStartPos(int ii);

    //damage == 与えられたダメージ
    void SetDmg(int damage);

    void SetTargetPos(Base target) { targetPos_ = target.pos_; }

private:

    MOVE move_;
    
    Vector2F targetPos_;

    void Move();

};
