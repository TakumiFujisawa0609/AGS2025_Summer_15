#pragma once
#include <vector>
#include"../../Common/Base.h"

#include"../../../Utility/AsoUtility.h"

class PlayerAttackBase
{
public:
	PlayerAttackBase();
	PlayerAttackBase(Vector2F* pPos,AsoUtility::DIRECTION* dir);
	~PlayerAttackBase();

	virtual void Init(void);
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	const Base GetObj(void) { return obj_; }


protected:

	Base obj_;

	Vector2F* pPos_;

	AsoUtility::DIRECTION* dir_;

	void ChangeDispPos(void);

};

