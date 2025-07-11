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
     std::vector<Base>Get(void);

     void Off(void) { lookOn_ = false; }
     void Create(void);
    void LookOn(Vector2F pos) { target_ = pos; lookOn_ = true; }
    
private:
    std::vector<Takenoko*>takenokos_;
    std::vector<Base>obj_;
    Vector2F target_;
    bool lookOn_;
    void UpdatePositionTakenokos(void);
    DIR dir_;
};

