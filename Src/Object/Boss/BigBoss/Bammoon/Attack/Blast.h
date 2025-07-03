#pragma once

#include"../../../Tutorial/Attack/AttackBase.h"


class Blast : public AttackBase
{
public:
	Blast();
	~Blast();

	void Init(const Vector2F* pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	const std::vector<Base> Get(void)const;

	void On(int i, Vector2F pPos);


private:
	std::vector<Base> obj_;

	Vector2F vec_;

	Vector2F target_;

};

