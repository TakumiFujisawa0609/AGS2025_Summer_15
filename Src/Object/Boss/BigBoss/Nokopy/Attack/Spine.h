#pragma once
#include "../../../Tutorial/Attack/AttackBase.h"

class Spine :
    public AttackBase
{
public:
    static constexpr int MAX_NUM = 13;

    Spine();
    virtual ~Spine();

    void Init(const Vector2F* pos) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    std::vector<Base>Get(void) { return obj_; }
    void Hit(int i) { obj_[i].isAlive_ = false; }
    void Off(void);
    void Create(void);

private:

    std::vector<Base>obj_;

};

