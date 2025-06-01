#pragma once
#include"../../Common/Base.h"


class AttackBase
{
public:

	enum DIR {
		LEFT,
		RIGHT
	};


	AttackBase();
	~AttackBase();

	virtual void Init(const Vector2F* pos);
	virtual void Update(void);
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	const Base Get(void)const { return obj_; }

	const bool End(void)const { return end_; }

	virtual void On(void) { obj_.isAlive_ = true; }


protected:
	int image_;
	Base obj_;
	const Vector2F* boss;

	AttackBase::DIR dir_;

	int attackCounter_;

	bool end_;

	void ChangeDispPos(void);

};

