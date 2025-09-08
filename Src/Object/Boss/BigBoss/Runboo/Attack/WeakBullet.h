#pragma once
#include<DxLib.h>
#include<vector>
#include"../../../Tutorial/Attack/AttackBase.h"
#include"Bullet.h"
#include <map>


class WeakBullet : public AttackBase
{
public:
	static constexpr int BULLET_NUM = 10;
	static constexpr float BULLET_SPEED = 6.0f;

	static constexpr float SIZE_X = 32.0f;
	static constexpr float SIZE_Y = 32.0f;

	static constexpr int NUM_MAX = 8;
	static constexpr int NUM_X = 8;
	static constexpr int NUM_Y = 1;

	static constexpr float IMAGE_BIG_RATE = 2.0f;

	static constexpr int IMAGE_SIZE_X = 32;
	static constexpr int IMAGE_SIZE_Y = 32;


	WeakBullet(float moveSpeed);
	~WeakBullet();

	void Init(const Vector2F* pos)override;
	void Update(Vector2F boss, float moveSpeed);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const std::vector<Base> Get() const override;

	void Hit(int i);

	bool End(void);

	void SetIsAlive(bool isAlive);

private:

	std::vector<Base> obj_;

	//Base bullets_[BULLET_NUM];
	int endCnt_;

	int imageArray[NUM_MAX];
	int arrayIndex_;

	float moveSpeed_;

	/*int imageArray_[IMAGE_ALL_NUM];*/ // 弾の画像配列

	float radius_;
	float stAngle_;
	int shotTimer_ = 0;                 // 発射間隔カウント用
	const int SHOT_INTERVAL = 320;      // 発射間隔（フレーム数）
	bool canShot_ = true;               // 発射可能かどうか

	float rotate_;

	void ChangeDispPos() override;
};