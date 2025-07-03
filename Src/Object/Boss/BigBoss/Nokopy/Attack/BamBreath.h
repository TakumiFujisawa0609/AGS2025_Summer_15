#pragma once
#include "../../../Tutorial/Attack/AttackBase.h"
class BamBreath :
    public AttackBase
{
public:
    BamBreath();
    virtual ~BamBreath();

    virtual void Init(const Vector2F* pos) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;
    virtual void Release(void) override;

    virtual const std::vector<Base> Get(void) const override;
    virtual void On(void) override;
    virtual void Off(void) override;
private:
};

