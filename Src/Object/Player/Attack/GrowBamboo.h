#pragma once
#include "PlayerAttackBase.h"
class GrowBamboo :
    public PlayerAttackBase
{
public:
    GrowBamboo();
    GrowBamboo(Vector2F* pPos, AsoUtility::DIRECTION* dir);
    ~GrowBamboo();

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
};

