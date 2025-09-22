#pragma once
#include<DxLib.h>
#include<vector>
#include"../../../Tutorial/Attack/AttackBase.h"
#include"Bullet.h"
#include <map>

class Bound : public AttackBase
{
public:

	static constexpr float MOVE_SPEED = 10.0f;

	static constexpr float RADIUS_SIZE = 60.0f;

	static constexpr float SIZE_X = RADIUS_SIZE * 2;
	static constexpr float SIZE_Y = RADIUS_SIZE * 2;

	static constexpr int BOUND_BALL_MAX = 1;

	Bound(float moveSpeed);
	~Bound();

	void Init(const Vector2F* pos)override;
	void Update(Vector2F boss);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const std::vector<Base> Get() const override;

	void Hit(int i);

	bool End(void);

	void SetTarget(const Vector2F* target) { target_ = target; }

	void SetIsAlive(bool isAlive);

private:
	std::vector<Base> obj_;

	const Vector2F* target_;

	Vector2F attackStartPos_;

	int image_;
	int moveSpeed_;

	int boundCnt_;

	void ChangeDispPos() override;

};