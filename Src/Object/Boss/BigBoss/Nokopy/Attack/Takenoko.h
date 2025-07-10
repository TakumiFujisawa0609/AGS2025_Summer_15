#pragma once
#include "../../../../UnitBase.h"
class Takenoko :
    public UnitBase
{
public:
    Takenoko();
    virtual ~Takenoko() override;

     void Init(Vector2F pos) ;
     void Update(void) override;
     void Draw(void) override;
     void Release(void) override;
     void IsGround(Collision::DIR dir) override;
};

