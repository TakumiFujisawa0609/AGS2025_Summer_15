#pragma once

#include"PlayerAttackBase.h"

class BPAttack : public PlayerAttackBase
{
public:
	static constexpr float DEFAULT_SIZE = 30.0f;

	static constexpr int DEFAULT_DAMAGE = 3;

	static constexpr float DEFAULT_SPEED = 60.0f;

	BPAttack();
	~BPAttack();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(Vector2F pPos, AsoUtility::DIRECTION dir, int bp);
	void Off(void) { obj_.isAlive_ = false; }

	int GetBp(void) { return bp_; }

	int GetDamage(void) { return (int)((float)DEFAULT_DAMAGE * ((float)bp_ / 10.0f)); }

private:
	int bp_;

	AsoUtility::DIRECTION dir_;
};

