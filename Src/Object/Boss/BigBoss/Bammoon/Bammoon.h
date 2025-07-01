#pragma once

#include"../BossBase.h"

class Bammoon : public BossBase
{
public:
	Bammoon();
	~Bammoon();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


private:
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
};

