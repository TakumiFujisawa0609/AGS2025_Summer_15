#pragma once
#include "../../../Tutorial/Attack/AttackBase.h"
class BamBeam :
    public AttackBase
{
public:
    BamBeam();
    virtual ~BamBeam();

    virtual void Init(const Vector2F* pos) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;
    virtual void Release(void) override;

    virtual const std::vector<Base> Get(void) const override;
    virtual void On(void) override;
    virtual void Off(void) override;

    void LookOn(Vector2F pos) { target_ = pos; lookOn_ = true; }
    void Hit(void) { obj_.isAlive_ = false; }
private:
    bool lookOn_;
    Vector2F target_;
    Vector2F drawPos_;
    int img_;

};

