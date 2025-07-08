#pragma once

#include<vector>

#include"../../../Common/Vector2.h"

class BlastEffect
{
public:
	static constexpr int ANIME_SPEED = 0;

	BlastEffect();
	~BlastEffect();

	void Load(std::vector<int> image);
	void On(Vector2F pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	const bool GetAlive(void)const { return isAlive_; }

private:
	std::vector<int> image_;
	bool isAlive_;
	Vector2F pos_;
	int animeCounter_;
	int animeInterval_;
};

