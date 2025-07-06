#pragma once

#include"../../../Tutorial/Attack/AttackBase.h"


class BamBlast : public AttackBase
{
public:
	static constexpr int BLAST_NUM_X = 6;
	static constexpr int BLAST_NUM_Y = 4;
	static constexpr int BLAST_NUM_MAX = BLAST_NUM_X * BLAST_NUM_Y;

	static constexpr int BLAST_SIZE = 480;

	static constexpr int MAX_NUM = 10;

	BamBlast();
	~BamBlast();

	void Init(const Vector2F* pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	const std::vector<Base> Get(void)const { return obj_; }

	void On(int i, Vector2F pPos);

	void Hit(int i);

private:
	int reticleImg_;
	int blastImg_[BLAST_NUM_MAX];
	int img;

	int blastCount_;

	std::vector<Base> obj_;

	struct BlastData {
		float angle_;
		float expansion_;
		Vector2F vec_;
		Vector2F target_;
		bool blast_;
		int animeCounter_;
	};

	std::vector<BlastData> bList;
};

