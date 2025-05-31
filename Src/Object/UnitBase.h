#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"
#include"Common/Base.h"
#include"../Manager/Collision.h"

class UnitBase
{
public:

	static constexpr float GRAVITY = 0.98f;			//重力
	static constexpr float MAX_GRAVITY = 31.0f;




	//コンストラクタ
	UnitBase(void);
	//デストラクタ
	virtual ~UnitBase(void) = 0;

	//初期化
	virtual void Init(void) = 0;
	//更新
	virtual void Update(void);
	//描画
	virtual void Draw(void) = 0;
	//解放
	virtual void Release(void) = 0;



	//ゲッター関数
	const Base& GetUnit(void)const { return unit_; }

	//セッタ関数ー---------------------------------------------------

	//位置
	void SetPos(const Vector2F& _pos) { unit_.pos_ = _pos; }

	//生存フラグ
	void SetAliveOff(void) { unit_.isAlive_ = false; }
	void SetAliveOn(void) { unit_.isAlive_ = true; }

	//---------------------------------------------------------------

protected:
	Base unit_;

	// <UnitBase::Update()のなかに入っている関数>-----------------------------------------------------
	
	// 座標の更新に関する処理をまとめる関数
	void UpdatePos(void);
	void UpdatePosX(void);
	void UpdatePosY(void);

	// 移動に関する更新処理をまとめて書く場所
	// (それぞれの派生クラスでoverrideする必要がある)
	virtual void MoveX(void) = 0;
	virtual void MoveY(void) = 0;

	// ステージとの当たり判定
	void CollisionStageY(void);
	void CollisionStageX(void);

	// 接地している時の数値の代入などをまとめた関数
	// (それぞれの派生クラスでoverrideする必要がある)
	virtual void IsGround(Collision::DIR dir);

	// 重力
	void Gravity(void);

	// ワールド座標情報をマップ座標に変換する関数
	void ChangeDispPos(void);
	//----------------------------------------------------------------------------------------------


	//重力
	float gravity_;


	/// <summary>
	/// とある点からとある点までの移動ベクトルを返す
	/// </summary>
	/// <param name="_start">狙う側</param>
	/// <param name="_goal">向かう先</param>
	/// <param name="_speed">設定速度(未設定だと、方向ベクトルのみを返す)</param>
	/// <returns>向かう先までの移動ベクトル</returns>
	const Vector2F GetMoveVec(const Vector2F _start, const Vector2F _goal,  const float _speed = 1.0f)const;
};