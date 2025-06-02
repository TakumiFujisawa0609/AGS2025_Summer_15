#pragma once
#include"AttackBase.h"
#include<DxLib.h>

class Tackle : public AttackBase
{
public:

	static constexpr float TACKLE_SPEED = 20.0f;

	Tackle();
	~Tackle();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	VECTOR bPos_;
};