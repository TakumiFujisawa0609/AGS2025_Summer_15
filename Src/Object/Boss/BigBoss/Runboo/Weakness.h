#pragma once
#include<DxLib.h>
#include"../../../Common/Base.h"
#include"../../../UnitBase.h"
#include"../../Tutorial/Attack/AttackBase.h"
#include"../BossBase.h"

class WeakBullet;
class Laser;

class Weakness : public BossBase
{
public:
	static constexpr float SIZE_X = 100;
	static constexpr float SIZE_Y = 100;

	static constexpr float AMPLITUDE = 1.0f;          
	static constexpr float MOVE_Y_SPEED = 0.05f;

	static constexpr int HP_MAX = 10;
	static constexpr int HP_POS_X = 10;
	static constexpr int HP_POS_Y = 15;

	static constexpr int INVI_COUNTER = 180;

	enum ATTACK
	{
		NON,
		LASER,
		BOUND,
		MAX,
	};

	Weakness();
	~Weakness();

	void Init(Vector2F disppos, float moveSpeed);
	void Init(void)override;
	void Update(Vector2F boss);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	AttackBase* GetAttackIns(void)override;
	std::vector<Base>GetObj(void)override;
	void ObjHit(int i);
	void SetDamage(int dmg)override;
	void ChengeAttack(ATTACK attack)
	{
		attack_ = attack;
	}

	int GetCnt(void) { return cnt_; }

private:

	WeakBullet* bullet_;
	Laser* laser_;

	ATTACK attack_;

	float moveSpeed_;

	float cnt_;
	Vector2F start_;

	int image_;
	int attackCounter_;

	void AttackManager(void);

	//待機状態
	void Idle(void)override;
	//移動状態
	void Move(void)override;
	//攻撃状態
	void Attack(void)override;
	//ダメージ状態
	void Damage(void)override;
	//死亡状態
	void Death(void)override;

	void IsGround(Collision::DIR dir)override {}

};