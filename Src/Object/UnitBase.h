#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"
#include"Common/Base.h"

class UnitBase
{
public:

	static constexpr int ENEMYBAMBOO_RADIUS = 32;

	//コンストラクタ
	UnitBase(void);
	//デストラクタ
	virtual ~UnitBase(void);

	//初期化
	virtual void Init(void) = 0;
	//更新
	virtual void Update(void) = 0;
	//描画
	virtual void Draw(void) = 0;
	//解放
	virtual void Release(void) = 0;

	//ゲッター関数
	//---------------------------------------
	//座標
		//位置
	const Vector2F& GetPos(void)const { return unit_.pos_; }

	const Vector2F& GetSize(void)const { return unit_.size_; }

	//半径
	const float GetRadius(void)const { return unit_.radius_; }

	const int GetHp(void)const { return unit_.hp_; }

	const Base& GetUnit(void)const { return unit_; }

	//セッター
	//----------------------

	//位置
	void SetPos(const Vector2F& _pos) { unit_.pos_ = _pos; }

protected:

	Base unit_;
};