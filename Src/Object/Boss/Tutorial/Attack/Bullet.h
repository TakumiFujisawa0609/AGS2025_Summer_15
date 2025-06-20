#pragma once
#include"AttackBase.h"


class Bullet : public AttackBase
{
public:
	static constexpr int BULLET_NUM = 20;
	
	static constexpr float CHARGE_RADIUS = 150.0f;

	static constexpr float RADIUS_MAX = 2000.0f;

	Bullet();
	~Bullet();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const std::vector<Base> Get(void)const override;

	void Hit(int i) { bullets[i].isAlive_ = false; }

private:
	Base bullets[BULLET_NUM];

	float radius_;
	float stAngle_;

	void ChangeDispPos(void)override;
};

