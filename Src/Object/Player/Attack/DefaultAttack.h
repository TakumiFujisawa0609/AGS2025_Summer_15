#pragma once

#include"../../Common/Base.h"

#include"../../../Utility/AsoUtility.h"

class DefaultAttack
{
public:
	enum UpdateRet
	{
		Nothing,	//何もされませんでした
		Action,		//発動!
		Already,	//発動しようとしたけどすでに発動中だった
		AttackEnd,	//今攻撃が終了した
		Recast,		//リキャストタイム中
	};

	static constexpr int RECAST_TIME = 20;

	static constexpr int ATTACK_NUM = 6;

	static constexpr int LOAD_SIZE_X = 1225 / ATTACK_NUM;

	static constexpr int LOAD_SIZE_Y = 280;

	static constexpr int SCALE = 0.5f;

	static constexpr int SIZE_X = LOAD_SIZE_X * SCALE;
	static constexpr int SIZE_Y = LOAD_SIZE_Y * SCALE;




	DefaultAttack();
	~DefaultAttack();
	
	void Init(Vector2F* plPos, AsoUtility::DIRECTION* dir);
	UpdateRet Update(void);
	void Draw(void);
	void Release(void);
	
	Base GetObj(void)const { return obj_; }

	void Hit();

private:

	Vector2F* plPos_;
	AsoUtility::DIRECTION* dir_;


	Base obj_;

	int img[ATTACK_NUM];


	int recastTime_;

	int attackCount_;

	void ChangeDispPos(void);
};

