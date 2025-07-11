#pragma once

#include"../../../Tutorial/Attack/AttackBase.h"


class BammoonBlast : public AttackBase
{
public:
	static constexpr int BammoonBlast_NUM_X = 6;
	static constexpr int BammoonBlast_NUM_Y = 4;
	static constexpr int BammoonBlast_NUM_MAX = BammoonBlast_NUM_X * BammoonBlast_NUM_Y;

	static constexpr int BammoonBlast_SIZE = 480;

	static constexpr int MAX_NUM = 10;

	BammoonBlast();
	~BammoonBlast();

	void Init(const Vector2F* pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	const std::vector<Base> Get(void)const { return obj_; }

	void On(int i, Vector2F pPos);

	void Hit(int i);

private:
	int reticleImg_;
	int BammoonBlastImg_[BammoonBlast_NUM_MAX];
	int img;

	int BammoonBlastCount_;

	std::vector<Base> obj_;

	struct BammoonBlastData {
		float angle_;
		float expansion_;
		Vector2F vec_;
		Vector2F target_;
		bool BammoonBlast_;
		int animeCounter_;
	};

	std::vector<BammoonBlastData> bList;
};

