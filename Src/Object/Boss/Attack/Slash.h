#pragma once
#include"AttackBase.h"

class Slash : public AttackBase
{
public:
	static constexpr int CHARGE = 200;

	static constexpr int ATTACK_TIME = 60;

	Slash();
	~Slash();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


	void SetTarget(const AttackBase::DIR dir);

private:




};

