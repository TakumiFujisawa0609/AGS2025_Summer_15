#pragma once
#include"../../../Common/Vector2.h"

class BamBlastEffect
{
public:
	BamBlastEffect(void);
	~BamBlastEffect(void);

	static constexpr int BP_LV = 5;
	static constexpr int DRAW_COUNTER = 60;

	void Init(void);
	void Update(void);
	void Draw(void);
	void Relese(void);

	void On(Vector2F pos,int bp,int img);

	bool IsAlive(void) { return isAlive_; }
private:
	Vector2F pos_;
	bool isAlive_;
	int bpLv_;
	int img_;
	int counter_;
};

