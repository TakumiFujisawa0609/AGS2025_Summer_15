#pragma once

#include<vector>

#include"../../../Common/Vector2.h"

class BlastEffect;

class BlastEffectManager
{
public:
	static constexpr int BLAST_NUM_X = 6;
	static constexpr int BLAST_NUM_Y = 4;
	static constexpr int BLAST_NUM_MAX = BLAST_NUM_X * BLAST_NUM_Y;

	static constexpr int BLAST_SIZE = 480;
	BlastEffectManager();
	~BlastEffectManager();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(Vector2F pos);
private:
	std::vector<int>image_;
	std::vector<BlastEffect*> blast_;
};