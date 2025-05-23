#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"
#include"Common/Base.h"

class UnitBase
{
public:

	static constexpr float MAX_JUMP_POWER = -12.0f;	//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;	//ジャンプ入力受付フレーム数

	static constexpr float GRAVITY = 0.98f;			//重力
	static constexpr float MAX_GRAVITY = 31.0f;

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

	void StageCollisionUpdate(void);

	//重力
	void Gravity(void);

	//ジャンプ
	void Jump(void);

	//Y座標の変更
	void UpdatePositionY(void);

	//ステージとの当たり判定
	void CollisionStageY(void);
	void CollisionStageX(void);

	void ChangeDispPos(void);


	//重力
	float gravity_;

	bool isJump_;				//true=ジャンプ中/false=非ジャンプ
	float jumpPower_;			//ジャンプパワー
	float verticalAcceleration_;//縦方向の加速度
};