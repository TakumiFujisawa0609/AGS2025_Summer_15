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


	static constexpr int DEFAULT_DAMAGE = 5;

	static constexpr float DEFAULT_SPEED = 30.0f;

	static constexpr int ALIVE_TIME = 300;

	BPAttack();
	~BPAttack();

	void Init(int image);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(Vector2F pPos, AsoUtility::DIRECTION dir, int bp);
	void Off(void) { obj_.isAlive_ = false; }

	int GetBp(void) { return bp_; }

	int GetDamage(void) { return DEFAULT_DAMAGE * bp_; }

	void Hit(void) { aliveHit_--; }
	// 攻撃タイプを切り替えるメソッド
	void SetAttackType(BP_ATTACK_TYPE type);
private:
	BP_ATTACK_TYPE bpAttackType_; 
	PlayerAttackBase* attack_;    
	int image_;
	int bp_;
	int aliveCounter_;
	int aliveHit_;


	AsoUtility::DIRECTION dir_;
};

