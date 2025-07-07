#pragma once

#include"PlayerAttackBase.h"

class BPAttack : public PlayerAttackBase
{
public:
	static constexpr float DEFAULT_RADIUS = 30.0f;

	static constexpr float DEFAULT_SIZE_X = 85;
	static constexpr float DEFAULT_SIZE_Y = 24;


	static constexpr int DEFAULT_DAMAGE = 5;

	static constexpr float DEFAULT_SPEED = 30.0f;

	static constexpr int ALIVE_TIME = 600;
	static constexpr int ALIVE_HIT = 10;

	BPAttack();
	~BPAttack();

	void Init(int image);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(Vector2F pPos, Vector2F vec);
	void Off(void) { obj_.isAlive_ = false; }

	int GetBp(void) { return bp_; }

	int GetDamage(void) { return DEFAULT_DAMAGE * bp_; }

	void Hit(void) { aliveHit_--; }

private:

	int image_;
	int bp_;
	int aliveCounter_;
	int aliveHit_;

	Vector2F vec_;

};

