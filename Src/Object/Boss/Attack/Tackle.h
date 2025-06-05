#pragma once
#include"AttackBase.h"
#include<DxLib.h>

class Tackle : public AttackBase
{
public:

	static constexpr float TACKLE_SPEED = 20.0f;
	static constexpr int WAIT_TIME = 60;
	static constexpr int TACKLE_START = 180;

	enum MODE
	{
		NON_MODE,
		STANP_MODE,
		TACKLE_MODE,
	};

	Tackle();
	~Tackle();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void SetTarget(Vector2F target) { target_ = target; }

private:
	VECTOR bPos_;
	Vector2F target_;
};