#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"
#include"Common/Base.h"
#include"../Manager/Collision.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"

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

	Vector2F GetStartPos(void)
	{
		startPos_.x = Camera::GetInstance().GetPos().x;
		startPos_.y = Camera::GetInstance().GetPos().y;

		return startPos_; 
	}

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
	void StageCollision(void);

	// 座標に加速度を加える関数
	void Accel(void);

	// ワールド座標情報をマップ座標に変換する関数
	void ChangeDispPos(void);

	// 重力
	void Gravity(void);

	// 接地している時の数値の代入などをまとめた関数
	// (それぞれの派生クラスで必要に応じてoverride)
	virtual void IsGround(Collision::DIR dir);

	//----------------------------------------------------------------------------------------------


	//重力
	float gravity_;
	Vector2F startPos_;


	/// <summary>
	/// とある点からとある点までの移動ベクトルを返す
	/// </summary>
	/// <param name="_start">狙う側</param>
	/// <param name="_goal">向かう先</param>
	/// <param name="_speed">設定速度(未設定だと、方向ベクトルのみを返す)</param>
	/// <returns>向かう先までの移動ベクトル</returns>
	const Vector2F GetMoveVec(const Vector2F _start, const Vector2F _goal, const float _speed = 0.0f)const;

	/// <summary>
	/// 2つの座標間の距離を計算します。
	/// </summary>
	/// <param name="_start">始点</param>
	/// <param name="_goal">終点</param>
	/// <returns>始点と終点の間の距離（float型）。</returns>
	const float GetDis(const Vector2F _start, const Vector2F _goal)const;

	/// <summary>
	/// HPなどのバーの表示
	/// </summary>
	/// <param name="x1">左上X座標</param>
	/// <param name="y1">左上Y座標</param>
	/// <param name="x2">右下X座標</param>
	/// <param name="y2">右下Y座標</param>
	/// <param name="hp">現在のHP</param>
	/// <param name="maxHp">最大体力</param>
	/// <param name="color">バーの色</param>
	/// <param name="frameColor"></param>
	/// <param name="backColor"></param>
	void DrawBar(
		int x1, int y1,                   // 左上座標
		int x2, int y2,                   // 右下座標
		int hp, int maxHp,               // 現在HP / 最大HP
		COLORREF color,                 // HP色
		COLORREF frameColor = RGB(255, 255, 255),
		COLORREF backColor = RGB(80, 80, 80)
	);
};

