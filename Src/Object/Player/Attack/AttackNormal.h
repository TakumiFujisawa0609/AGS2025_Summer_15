#pragma once
#include "PlayerAttackBase.h"
class AttackNormal :
    public PlayerAttackBase
{
public:
	AttackNormal();
	~AttackNormal()override;

	void Init(void)override;
	void Init(Vector2F* movePos, Vector2F* drawPos,AsoUtility::DIRECTION*dir);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;
private:

};

