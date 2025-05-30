#pragma once
#include"../UnitBase.h"

class EnemyBase : public UnitBase
{
public:

    static enum MOVE
    {
        RIGHT,
        LEFT,
        IDOL
    };

    EnemyBase();
    ~EnemyBase();

    void Init()override;
    void Update()override;
    void Draw()override;
    void Release()override;

protected:

    void Move(Vector2F targetpos, float moveSpeed);

    MOVE move_;

};