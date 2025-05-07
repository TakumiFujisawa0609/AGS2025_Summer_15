#pragma once
#include "../UnitBase.h"
class EnemyBambooShoot :
    public UnitBase
{
public:
    EnemyBambooShoot();
    ~EnemyBambooShoot();

    void Init();
    void Update();
    void Draw();
    void Relese();


};

