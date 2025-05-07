#pragma once
#include "../UnitBase.h"
class EnemyBamboo :
    public UnitBase
{
public:
    EnemyBamboo();
    ~EnemyBamboo();

    void Init();
    void Update();
    void Draw();
    void Relese();

private:
};

