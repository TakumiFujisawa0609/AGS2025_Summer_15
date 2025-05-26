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
    
    Base GetBase() { return unit_; }

    void SetStartPos(int ii);

    //damage == ó^Ç¶ÇÁÇÍÇΩÉ_ÉÅÅ[ÉW
    void SetDmg(int damage);

    void SetTargetPos(Base target) { targetPos_ = target.pos_; }

private:

    MOVE move_;
    
    Vector2F targetPos_;

    void Move();

};
