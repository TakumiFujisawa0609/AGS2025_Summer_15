#pragma once
#include<DxLib.h>
#include<vector>
#include"../../../Tutorial/Attack/AttackBase.h"
#include"Bullet.h"
#include <map>


class WeakBullet : public AttackBase
{
public:
	static constexpr int BULLET_NUM = 20;
	static constexpr float MOVE_SPEED = 5.0f;


	WeakBullet(float moveSpeed);
	~WeakBullet();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const std::vector<Base> Get() const override;

	void Hit(int i) { bullets_[i].isAlive_ = false; }

private:

	Base bullets_[BULLET_NUM];

	float moveSpeed_;

	float radius_;
	float stAngle_;
	int shotTimer_ = 0;                 // 発射間隔カウント用
	const int SHOT_INTERVAL = 120;      // 発射間隔（フレーム数）
	bool canShot_ = true;               // 発射可能かどうか

	void ChangeDispPos() override;
};