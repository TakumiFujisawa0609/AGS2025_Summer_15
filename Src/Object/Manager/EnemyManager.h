#pragma once
#include "../Enemy/EnemyBamboo.h"

class EnemyManager
{
public:

    EnemyManager();
    ~EnemyManager();

    void Init();
    void Update();
    void Draw();
    void Relese();

    EnemyBamboo* GetBamboo(int ii) { return bamboo_[ii]; }

private:

    EnemyBamboo* bamboo_[EnemyBamboo::ENEMY_MAX];

};

const Vector2F START_POS[EnemyBamboo::ENEMY_MAX] =
{
  {2000.0f, 250.0f},
  {2500.0f, 200.0f},
  {3300.0f, 200.0f},
  {4000.0f, 200.0f},
  {5000.0f, 100.0f}
};
