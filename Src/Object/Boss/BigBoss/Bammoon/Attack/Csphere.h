#pragma once

#include<vector>

#include"../../../../../Common/Vector2.h"
#include"../../../../Common/Base.h"
#include"../../../../../Application.h"

class Csphere
{
public:
	Csphere();
	~Csphere();

	void Init(const Vector2F* pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	Base& GetObj(void) { return obj_; }

	void CorceChange(Vector2F pPos);

private:
	Base obj_;

	const Vector2F* bossPos_;

	Vector2F moveVec_;
};
