#pragma once
#include"../Enemy/EnemyBamboo.h"

class EnemyBamboo;

class EnemyManager
{
public:
    EnemyManager();
    ~EnemyManager();

    void Init();
    void Update();
    void Draw();
    void Relese();

    EnemyBamboo* GetBamboo() { return bamboo_; }

private:
    EnemyBamboo* bamboo_;

};

