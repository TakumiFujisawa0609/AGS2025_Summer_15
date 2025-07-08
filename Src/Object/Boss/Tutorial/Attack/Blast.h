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

	void On(void)override { obj_.isAlive_ = true; obj_.inviCounter_ = 0; }

	void Hit(void) {
		obj_.size_ = { (float)BLAST_SIZE,(float)BLAST_SIZE };
		obj_.radius_ = (float)(BLAST_SIZE / 2);
		lookOn_ = false;
		blast_ = true;
		obj_.inviCounter_ = 1;
	}



private:
	int reticleImg_;
	int blastImg_[BLAST_NUM_MAX];
	int img;

	Vector2F target_;

	float angle_;
	float expansion_;

	bool lookOn_;

	bool blast_;
};


