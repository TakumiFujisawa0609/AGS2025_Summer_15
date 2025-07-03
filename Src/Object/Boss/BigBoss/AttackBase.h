#pragma once

#include"../../Common/Base.h"
#include"../../../Common/Vector2.h"
#include <vector>


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

	Base& GetObj(void) { return obj_; }

	const bool End(void)const { return end_; }

	virtual void On(void) { obj_.isAlive_ = true; }

	virtual void Off() { obj_.isAlive_ = false; }

	virtual bool IsCircle(void) { return isCircle_; }
	virtual bool IsParry(void) { return isParry_; }
protected:
	//画像ハンドル
	int image_;

	//構造体
	Base obj_;

	//ボス座標のポインター
	const Vector2F* boss;

	//攻撃を行う方向
	AttackBase::DIR dir_;

	//更新処理に使うカウンター
	int attackCounter_;

	bool isParry_;

	//攻撃終了
	bool end_;

	//ワールド座標をマップ座標に変換
	void ChangeDispPos(void);
	bool isCircle_ = true;	//true=当たり判定は円形 false=矩形

};
