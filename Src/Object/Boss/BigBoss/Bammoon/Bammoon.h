#pragma once

#include"../BossBase.h"

class Bammoon : public BossBase
{
public:
	enum class ATTACK
	{
		NON = -1,



		MAX,
	};

	Bammoon();
	~Bammoon();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	std::vector<Base*>GetObj(void)override;

private:

	ATTACK attackStage_;


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


	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;
};

