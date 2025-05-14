#pragma once
#include "../UnitBase.h"
class EnemyBamboo : public UnitBase
{
public:
    EnemyBamboo();
    ~EnemyBamboo();

    void Init()override;
    void Update()override;
    void Draw()override;
    void Release()override;

    Base GetBase() { return enemy_; }

private:
    Base enemy_;
};

