#pragma once
#include "../../../Tutorial/Attack/AttackBase.h"
class Takenoko;

class Wavemboo :
    public AttackBase
{
public:
    static constexpr int MAX_NUM = 13;

    Wavemboo();
    virtual ~Wavemboo();

     void Init(const Vector2F* pos) override;
     void Update(void) override;
     void Draw(void) override;
     void Release(void) override;
     std::vector<Base>Get(void) { return obj_; }
     void Hit(int i) { obj_[i].isAlive_ = false; }
     void Off(void);
     void Create(void);
    void LookOn(Vector2F pos) { target_ = pos; lookOn_ = true; }
    
private:
    std::vector<Base>obj_;
    Vector2F target_;
    bool lookOn_;
    void UpdatePositionTakenokos(void);
    DIR dir_;
    int image_;
};

