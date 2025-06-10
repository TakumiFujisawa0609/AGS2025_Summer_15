#pragma once
#include"AttackBase.h"
#include<DxLib.h>

class Tackle : public AttackBase
{
public:

	static constexpr float TACKLE_SPEED = 20.0f;
	static constexpr int NON_TIME = 180;
	static constexpr int TACKLE_START = 180;

	enum class DIR
	{
		NON,
		STANDBY,
		TACKLE_MODE,
		END,
	};

	Tackle();
	~Tackle();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void SetTarget(Vector2F target) { target_ = target; }
	DIR GetDir() { return dir_; }

private:
	VECTOR bPos_;
	Vector2F target_;

	DIR dir_;
};