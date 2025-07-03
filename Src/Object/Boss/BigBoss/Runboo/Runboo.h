#pragma once

#include<DxLib.h>
#include<vector>
#include"../BossBase.h"

class Weakness;

class Runboo : public BossBase
{
public:

	static constexpr int WEAK_MAX = 3;

	Runboo();
	~Runboo();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	//std::vector<Base*>GetObj(void)override;

	AttackBase* GetAttackIns(void)override;
	std::vector<Base>GetObj(void)override;
	void ObjHit(int i)override;
	void SetDamage(int dmg)override;
	bool IsInvici(void) { return unit_.inviCounter_ > 0; }

private:
	//インスタンス
	std::vector<Weakness*> weak_;
	
	//待機状態
	void Idle(void) override;

	//移動状態
	void Move(void) override;

	//攻撃状態
	void Attack(void) override;

	//ダメージ状態
	void Damage(void) override;

	//死亡状態
	void Death(void) override;

	void HpUpdate(void);

	void IsGround(Collision::DIR dir)override {}
};