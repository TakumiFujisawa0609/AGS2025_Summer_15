#pragma once
#include"AttackBase.h"
#include"../../../UnitBase.h"
#include"../../../../Application.h"
#include<DxLib.h>

class Tackle : public AttackBase
{
public:

	static constexpr float TACKLE_SPEED = 20.0f;
	static constexpr int TACKLE_START = 180;

	enum class DIR
	{
		NON,
		JUMP,
		STANDBY,
		TACKLE_LEFT,
		TACKLE_RIGHT,
		END,
	};

	Tackle();
	~Tackle();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	DIR GetDir(void) { return dir_; }

	void SetEndPos(Vector2F end) { endPos = end; }
	Vector2F GetEndPos(void) { return endPos; }
	int GetCounter(void) { return counter_; }
	void SetStandBy(bool flg) { isStandby_ = flg; }

private:

	DIR dir_;
	int counter_;
	bool isStandby_;

	Vector2F endPos;
};