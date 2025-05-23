#pragma once
#include "../UnitBase.h"
class EnemyBamboo : public UnitBase
{
public:
    static constexpr int HP_MAX = 50;
    static constexpr float MOVE_SPEED = 2.0f;
    static constexpr float RADIUS_SIZE = 10.0F;	
    static constexpr int ENEMYBAMBOO_RADIUS = 20;

    EnemyBamboo();
    ~EnemyBamboo();

    void Init()override;
    void Update()override;
    void Draw()override;
    void Release()override;

    Base GetBase() { return enemy_; }

    //damage == 与えられたダメージ
    void SetDmg(int damage) { enemy_.hp_ -= damage; }

    void SetTargetPos(Base target) { targetPos_ = target.pos_; }

private:
    Base enemy_;

    //true : 右移動 / false : 左移動
    bool isMove_;
    Vector2F targetPos_;

    void Move();
    void ProcessJump(void);
};
