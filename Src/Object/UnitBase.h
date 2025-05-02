#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"

class UnitBase
{
public:

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
	const Vector2F& GetPos(void)const { return pos_; }

	const Vector2F& GetSize(void)const { return size_; }

	//半径
	const float GetRadius(void)const { return radius_; }

	//セッター
	//----------------------

	//位置
	void SetPos(const Vector2F& _pos) { pos_ = _pos; }

protected:

		Vector2F pos_;		//座標
		float radius_;		//半径
		Vector2F size_;		//大きさ

		int modelId_;		//ハンドル番号

		float speed_;		//移動速度


};
