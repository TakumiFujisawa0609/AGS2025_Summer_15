#pragma once

#include"PlayerAttackBase.h"

class BPAttack : public PlayerAttackBase
{
public:
	static constexpr float DEFAULT_RADIUS = 30.0f;

	static constexpr float DEFAULT_SIZE_X = 85;
	static constexpr float DEFAULT_SIZE_Y = 24;


	static constexpr int DEFAULT_DAMAGE = 3;

	static constexpr float DEFAULT_SPEED = 30.0f;

	BPAttack();
	~BPAttack();

	void Init(int image);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(Vector2F pPos, AsoUtility::DIRECTION dir, float bp);
	void Off(void) { obj_.isAlive_ = false; }

	int GetBp(void) { return bp_; }

	int GetDamage(void) { return (int)((float)DEFAULT_DAMAGE * ((float)bp_ / 10.0f)); }

private:

	int image_;
	float bp_;

	AsoUtility::DIRECTION dir_;
};

