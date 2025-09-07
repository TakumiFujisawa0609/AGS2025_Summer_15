#pragma once
#include<DxLib.h>
#include<vector>
#include"../../../Tutorial/Attack/AttackBase.h"
#include"Bullet.h"
#include <map>

class Bound : public AttackBase
{
public:

	static constexpr float RADIUS_SIZE = 128.0f;
	static constexpr float MOVE_SPEED = 10.0f;

	static constexpr int BOUND_BALL_MAX = 3;

	Bound(float moveSpeed);
	~Bound();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	std::vector<Base> obj_;

	int image_;
	int moveSpeed_;
};