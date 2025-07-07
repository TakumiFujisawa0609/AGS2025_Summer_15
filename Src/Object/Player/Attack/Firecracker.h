#pragma once
#include "PlayerAttackBase.h"
class Firecracker :
    public PlayerAttackBase
{
public:
    Firecracker();
    Firecracker(Vector2F* pPos, AsoUtility::DIRECTION* dir);
    ~Firecracker() ;

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
};

