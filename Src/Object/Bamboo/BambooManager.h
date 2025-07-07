#pragma once

#include"Bamboo.h"

class BambooManager
{
public:
	BambooManager();
	~BambooManager();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Create(Vector2F pos, int num, int probability = 100);

	std::vector<Bamboo*>GetBamboos(void) { return bamboos_; }

private:
	std::vector<Bamboo*> bamboos_;

	int image_;
};

