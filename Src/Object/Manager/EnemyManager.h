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
private:
    EnemyBamboo* bamboo_;

};

