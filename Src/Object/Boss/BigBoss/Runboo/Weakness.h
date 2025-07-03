#pragma once
#include<DxLib.h>
#include"../../../Common/Base.h"
#include"../BossBase.h"

class Weakness : BossBase
{
public:
	static constexpr float SIZE_X = 100;
	static constexpr float SIZE_Y = 100;

	static constexpr float AMPLITUDE = 2.0f;          // 振幅（上下の幅）
	static constexpr float MOVE_Y_SPEED = 0.05f;              // 動く速さ（角度の進み）

	static constexpr int HP_MAX = 30;
	static constexpr int HP_POS_X = 10;
	static constexpr int HP_POS_Y = 15;

	Weakness();
	~Weakness();

	void Init(Vector2F disppos);
	void Update()override;
	void Draw()override;
	void Release()override;

private:
	Base unit_;

	float cnt_;
	Vector2F start_;

	//継承-------------------------------------------
	void Init()override;

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

	std::vector<Base*>GetObj(void)override;
	//-------------------------------------------

	void HpDraw(void);
};