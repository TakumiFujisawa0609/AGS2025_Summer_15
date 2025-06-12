#pragma once

#include"PlayerAttackBase.h"

class BPAttack : public PlayerAttackBase
{
public:
	BPAttack(Vector2F* pPos, AsoUtility::DIRECTION* dir);
	~BPAttack();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(void);
	void Off(void) { obj_.isAlive_ = false; }


private:

};

