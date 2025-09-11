#pragma once

#include<DxLib.h>
#include<vector>
#include"../BossBase.h"
#include"Weakness.h"

class Weakness;
class Pillar;

class Runboo : public BossBase
{
public:

	static constexpr int WEAK_MAX = 3;
	static constexpr float MOVE_SPEED = 1.0f;
	static constexpr int INVI_COUNTER = 60;

	static constexpr int SMOKE_IMAGE_NUM = 8;
	static constexpr int SMOKE_IMAGE_NUM_X = 3;
	static constexpr int SMOKE_IMAGE_NUM_Y = 3;
	static constexpr int SMOKE_IMAGE_SIZE_X = 3072 / 3;
	static constexpr int SMOKE_IMAGE_SIZE_Y = 3072 / 3;

	static constexpr int HALF_X = 70;
	static constexpr int HALF_Y = Application::SCREEN_SIZE_Y / 2;

	static constexpr int HP_MAX = Weakness::HP_MAX * WEAK_MAX;

	Runboo();
	~Runboo();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	void DrawHp();

	//std::vector<Base*>GetObj(void)override;

	AttackBase* GetAttackIns(void)override;
	std::vector<Base>GetObj(void)override { return std::vector<Base>{}; };
	void ObjHit(int i)override;
	void SetDamage(int dmg)override;
	bool IsInvici(void) { return unit_.inviCounter_ > 0; }

	float GetMoveSpeed(void) { return moveSpeed_; }
	bool GetWeakAllAlive(void)
	{
		return (weak_[0]->GetUnit().isAlive_ &&
			weak_[1]->GetUnit().isAlive_ &&
			weak_[2]->GetUnit().isAlive_);
	}



	std::vector<Weakness*> GetWeakness(void) { return weak_; }

private:
	//インスタンス
	std::vector<Weakness*> weak_;

	Pillar* pillar_;

	float moveSpeed_;

	int image_;
	int smokeImg_[SMOKE_IMAGE_NUM];

	int maxHp_;

	float smokeAnimIndex_;
	
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

	void IsGround(Collision::DIR dir)override {};
};