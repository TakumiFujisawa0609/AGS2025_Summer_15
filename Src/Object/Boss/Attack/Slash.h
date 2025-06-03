#pragma once
#include"AttackBase.h"

class Slash : public AttackBase
{
public:
	static constexpr int CHARGE = 200;

	static constexpr int ATTACK_TIME = 60;

	static constexpr int ATTACK_DRAW_TIME = 30;		// 攻撃のエフェクト表示時間

	static constexpr int ANIM_ALL = 6;

	static constexpr int X_NUM = 6;

	static constexpr int Y_NUM = 1;

	static constexpr int X_SIZE = 1225 / X_NUM;

	static constexpr int Y_SIZE = 280;

	

	Slash();
	~Slash();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


	void SetTarget(const AttackBase::DIR dir) { dir_ = dir; }

private:

	bool isTurn;

	int img[ANIM_ALL];

	int animCounter_;


};

