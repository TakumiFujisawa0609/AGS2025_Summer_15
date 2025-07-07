#pragma once

#include"../../../Tutorial/Attack/AttackBase.h"


class Pbullet : AttackBase
{
public:
	static constexpr int NUM = 10;

	static constexpr int PBULLET_ANIME_NUM = 4;

	static constexpr int HIT_ANIME_NUM = 5;


	static constexpr float SPEED = 5.0f;

	static constexpr float RAD = 10.0f * (DX_PI_F / 180.0f);

	Pbullet();
	~Pbullet();

	void Init(const Vector2F* pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	const std::vector<Base> Get(void)const { return obj_; }

	void On(int i, Vector2F pPos);
	void Hit(int i);

private:
	std::vector<Base> obj_;

	std::vector<Vector2F> move_;
	std::vector<int> animeCou_;

	int pBulletImg_[PBULLET_ANIME_NUM];
	int hitImg_[HIT_ANIME_NUM];

	std::vector<bool>hit_;

};

