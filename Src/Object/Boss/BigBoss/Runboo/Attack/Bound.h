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

	Bound();
	~Bound();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	int image_;
};