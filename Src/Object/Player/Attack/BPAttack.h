#pragma once
#include"PlayerAttackBase.h"

class ThrowBamboo;
class GrowBamboo;
class Firecracker;

class BPAttack : public PlayerAttackBase
{
public:
	enum class BP_ATTACK_TYPE {
		THROW_BAMBOO,
		GROW_BAMBOO,
		FIRECRACKER
	};
	static constexpr float DEFAULT_RADIUS = 30.0f;

	static constexpr float DEFAULT_SIZE_X = 85;
	static constexpr float DEFAULT_SIZE_Y = 24;


	static constexpr int DEFAULT_DAMAGE = 10;

	static constexpr float DEFAULT_SPEED = 30.0f;

	static constexpr int ALIVE_TIME = 600;
	static constexpr int BOUNCE_MAX = 5;
	static constexpr int POWER_MAX = 6;

	BPAttack();
	~BPAttack();

	void Init(int image);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(Vector2F pPos, Vector2F vec);
	void Off(void) { obj_.isAlive_ = false; }

	int GetPower(void) { return power_; }

	void Hit(void) {
		if (power_ < POWER_MAX) { power_++; }
		 bounce_++; 
	}

	void Parry(Vector2F pos);

	int GetDamage(void) { return DEFAULT_DAMAGE * power_; }

private:
	BP_ATTACK_TYPE bpAttackType_; 
	PlayerAttackBase* attack_;    
	int image_;
	int aliveCounter_;

	Vector2F vec_;

	int power_;
	int bounce_;
};

