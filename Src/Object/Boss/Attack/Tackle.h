#pragma once
#include"AttackBase.h"
#include"../../UnitBase.h"
#include"../../../Application.h"
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
		JUMP,
		STANDBY,
		TACKLE_RIGHT,
		TACKLE_LEFT,
		END,
	};

	Tackle();
	~Tackle();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void SetTarget(Base target) { target_ = target; }
	DIR GetDir() { return dir_; }

	void CollisionLenDraw(Vector2F startPos, float radius);

private:
	Base target_;

	DIR dir_;
};