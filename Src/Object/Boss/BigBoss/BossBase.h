#pragma once
#include"../../UnitBase.h"
#include "../Tutorial/Attack/AttackBase.h"


class BossBase : public UnitBase
{
public:

	enum class STATE
	{
		IDLE,
		MOVE,
		ATTACK,
		DAMAGE,
		DEATH,
	};

	BossBase();
	~BossBase();

	//virtual void Init(Vector2F disppos, float moveSpeed) {};
	//virtual void Update(Vector2F boss) {};

	virtual void Init(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override = 0;
	virtual void Release(void)override = 0;

	virtual AttackBase* GetAttackIns(void) = 0;
	virtual std::vector<Base>GetObj(void) = 0;

	virtual void ObjHit(int i) = 0;

	virtual void SetDamage(int dmg) = 0;

	virtual bool IsInvici(void) { return unit_.inviCounter_ > 0; }

	void SetPlayerPosPtr(const Vector2F* pos);

	virtual int GetAttackState(void) { return 0; };

	virtual void SetDown(Vector2F pos);

	//virtual std::vector<BossBase*> GetWeakness(void) { return std::vector<BossBase*>{}; };

	virtual void DrawHp(void) {};

protected:
	//状態ごとの関数を呼ぶための関数ポインタ
	void(BossBase::*stateFuncPtr)(void);

	//待機状態
	virtual void Idle(void) = 0;

	//移動状態
	virtual void Move(void) = 0;

	//攻撃状態
	virtual void Attack(void) = 0;

	//ダメージ状態
	virtual void Damage(void) = 0;

	//死亡状態
	virtual void Death(void) = 0;


	//状態管理
	void ChangeState(STATE s);

	STATE state_;


	const Vector2F* playerPosPtr_ = nullptr;



	AttackBase::DIR bossDir_;







	// 接地している時の数値の代入などをまとめた関数
	virtual void IsGround(Collision::DIR dir)override;
};

