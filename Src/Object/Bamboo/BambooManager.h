#pragma once

#include"Bamboo.h"

class BambooManager
{
public:
	BambooManager();
	~BambooManager();

	void Init(Vector2F* pPos,int* bp);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Create(Vector2F pos, int num, int probability = 100);

	std::vector<Bamboo*>GetBamboos(void) { return bamboos_; }

private:
	std::vector<Bamboo*> bamboos_;

	int image_;

	Vector2F* pPos_;
	int* playerBp_;
};

