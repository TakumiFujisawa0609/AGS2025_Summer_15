#pragma once

#include"AttackBase.h"

class Blast : public AttackBase
{
public:
	static constexpr int BLAST_NUM_X = 6;
	static constexpr int BLAST_NUM_Y = 4;
	static constexpr int BLAST_NUM_MAX = BLAST_NUM_X * BLAST_NUM_Y;

	static constexpr int BLAST_SIZE = 480;

	Blast();
	~Blast();

	void Init(const Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void LookOn(Vector2F pos) { target_ = pos; lookOn_ = true; }

	void Hit(void) {
		obj_.size_ = { (float)BLAST_SIZE,(float)BLAST_SIZE };
		obj_.radius_ = (float)(BLAST_SIZE / 2);
		lookOn_ = false;
		blast_ = true;
	}

private:
	int reticleImg_;
	int blastImg_[BLAST_NUM_MAX];

	Vector2F target_;

	float angle_;
	float expansion_;

	bool lookOn_;

	bool blast_;
};


