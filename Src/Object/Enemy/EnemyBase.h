#pragma once
#include"../UnitBase.h"

class EnemyBase : public UnitBase
{
public:

    static enum MOVE
    {
        RIGHT,
        LEFT,
        IDOL
    };

    EnemyBase();
    ~EnemyBase();

    virtual void Init()override;
    virtual void Update()override;
    virtual void Draw()override;
    virtual void Release()override;

    void SetPlayer(UnitBase* p) { player_ = p; }

protected:
    UnitBase* player_;

    void Move(Vector2F targetpos, float moveSpeed);

    MOVE move_;

    // Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
    virtual void IsGround(Collision::DIR dir)override = 0;
};