#pragma once
#include "../../../Tutorial/Attack/AttackBase.h"
class Takenoko;

class Wavemboo :
    public AttackBase
{
public:
    Wavemboo();
    virtual ~Wavemboo();

    virtual void Init(const Vector2F* pos) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;
    virtual void Release(void) override;

    virtual const std::vector<Base> Get(void) const override;
    virtual void On(void) override;
    virtual void Off(void) override;
    void Hit(void) { obj_.isAlive_ = false; }
private:
    std::vector<Takenoko*>takenokos_;

};

