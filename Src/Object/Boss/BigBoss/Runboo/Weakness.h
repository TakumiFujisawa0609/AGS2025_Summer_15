#pragma once
#include<DxLib.h>
#include"../../../Common/Base.h"
#include"../../../UnitBase.h"
#include"../../Tutorial/Attack/AttackBase.h"
#include"../BossBase.h"

class WeakBullet;
class Laser;
class Pillar;
class Bound;
class Spiral;

class Weakness : public BossBase
{
public:
	static constexpr float SIZE_X = 100;
	static constexpr float SIZE_Y = 100;

	static constexpr float AMPLITUDE = 1.0f;          
	static constexpr float MOVE_Y_SPEED = 0.05f;
	static constexpr float RADIUS_SIZE = 64.0f;

	static constexpr int HP_MAX = 300;
	static constexpr int HP_POS_X = 10;
	static constexpr int HP_POS_Y = 15;

	static constexpr int IMAGE_EX_RATE_X = 1.0f;
	static constexpr int IMAGE_EX_RATE_Y = 1.0f;

	static constexpr int INVI_COUNTER = 30;

	enum ATTACK
	{
		NON,
		SPIRAL,
		PILLAR,
		BOUND,
		LASER,
		MAX,
	};

	enum MODE
	{
		NORMAL,
		HARD,
	};

	Weakness();
	~Weakness();

	void Init(Vector2F disppos, float moveSpeed);
	void Init(void)override;
	void Update(Vector2F boss, float moveSpeed);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	AttackBase* GetAttackIns(void)override;
	std::vector<Base>GetObj(void)override;

	std::vector<Base> GetBulletObj(void);

	void BulltHit(int i);
	void SetHardMode();

	void ObjHit(int i);
	void SetDamage(int dmg)override;
	void ChengeAttack(ATTACK attack)
	{
		attack_ = attack;
	}

	ATTACK GetAttack(void) { return attack_; }

	int GetCnt(void) { return cnt_; }

	void AttackManager(bool isHard);


private:

	WeakBullet* bullet_;
	Laser* laser_;
	Pillar* pillar_;
	Bound* bound_;
	Spiral* spiral_;

	ATTACK attack_;
	MODE mode_;

	float moveSpeed_;

	float cnt_;
	Vector2F start_;

	int exRateX_;
	int exRateY_;

	int image_;
	int attackCounter_;



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