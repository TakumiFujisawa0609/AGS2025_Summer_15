#pragma once
#include "../Enemy/EnemyBamboo.h"

class EnemyManager
{
public:
    static constexpr int ENEMY_MAX = 5;

    EnemyManager();
    ~EnemyManager();

    void Init(int ii);
    void Update(int ii);
    void Draw(int ii);
    void Relese(int ii);

    void Collision(Base& a, Base b);

    EnemyBamboo* GetBamboo(int ii) { return bamboo_[ii]; }

private:
    EnemyBamboo* bamboo_[ENEMY_MAX];

};

const Vector2F START_POS[EnemyManager::ENEMY_MAX] =
{
  {500.0f, 250.0f},
  {200.0f, 200.0f},
  {700.0f, 200.0f},
  {1000.0f, 200.0f},
  {1200.0f, 100.0f}
};
