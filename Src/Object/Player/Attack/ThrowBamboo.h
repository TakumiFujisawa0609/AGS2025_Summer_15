#pragma once
#include "PlayerAttackBase.h"
class ThrowBamboo :
    public PlayerAttackBase
{
public:
    ThrowBamboo();
    ThrowBamboo(Vector2F* pPos, AsoUtility::DIRECTION* dir);
    ~ThrowBamboo();

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
};

