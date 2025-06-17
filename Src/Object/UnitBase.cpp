#include<cmath>
#include "UnitBase.h"
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"


UnitBase::UnitBase()
{
	unit_.pos_ = { 0.0f,0.0f };
	unit_.size_ = { 0.0f,0.f };

	unit_.radius_ = 0.0f;
	unit_.speed_ = 0.0f;

	unit_.hp_ = 0;

	unit_.xAccel_ = 0.0f;
	unit_.yAccel_ = 0.0f;

	unit_.isGravity_ = true;

	unit_.isStageCollision_ = true;

	gravity_ = GRAVITY;

	unit_.isInvincible_=false;		//無敵
	unit_.inviCounter_ = 0;

}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{
	Accel();

	StageCollision();

	// 実際に座標を更新
	unit_.pos_ = unit_.nextpos_;

	ChangeDispPos();
}

void UnitBase::Accel(void)
{
	unit_.nextpos_.y += unit_.yAccel_;
	unit_.nextpos_.x += unit_.xAccel_;

	// 横向きの加速度を減速させる

	//減速度
	const float decel = gravity_;

	if (unit_.xAccel_ > decel) {
		unit_.xAccel_-= decel;
	}
	else if (unit_.xAccel_ < -decel) {
		unit_.xAccel_+= decel;
	}
	else {
		unit_.xAccel_ = 0;
	}
}


void UnitBase::StageCollision(void)
{
	if (!unit_.isStageCollision_)return;


	Vector2F y = { unit_.pos_.x,unit_.nextpos_.y };

	// 衝突判定・補正
	Collision& col = Collision::GetInstance();

	// 上方向
	float upLine = col.GetStageLine(y, unit_.size_, Collision::UP);
	if (unit_.nextpos_.y - unit_.size_.y / 2 <= upLine) {
		unit_.nextpos_.y = upLine + unit_.size_.y / 2;
		unit_.yAccel_ = 0.0f;
		IsGround(Collision::UP);
	}

	// 下方向
	float downLine = col.GetStageLine(y, unit_.size_, Collision::DOWN);
	if (unit_.nextpos_.y + unit_.size_.y / 2 >= downLine) {
		unit_.nextpos_.y = downLine - unit_.size_.y / 2;
		unit_.yAccel_ = 0;
		IsGround(Collision::DOWN);
	}
	else {
		// 空中なら重力を加える
		//unit_.isGravity_ = true;
		unit_.isGround_ = false;
		Gravity();
	}

	// 左方向
	float leftLine = col.GetStageLine(unit_.nextpos_, unit_.size_, Collision::LEFT);
	if (unit_.nextpos_.x - unit_.size_.x / 2 <= leftLine) {
		unit_.nextpos_.x = leftLine + unit_.size_.x / 2;
		unit_.xAccel_ = 0;
		IsGround(Collision::LEFT);
	}

	// 右方向
	float rightLine = col.GetStageLine(unit_.nextpos_, unit_.size_, Collision::RIGHT);
	if (unit_.nextpos_.x + unit_.size_.x / 2 >= rightLine) {
		unit_.nextpos_.x = rightLine - unit_.size_.x / 2;
		unit_.xAccel_ = 0;
		IsGround(Collision::RIGHT);
	}
}

void UnitBase::Gravity(void)
{
	//Y軸加速度に重力を加える
	if (!unit_.isGravity_)return;
	unit_.yAccel_ = (unit_.yAccel_ < MAX_GRAVITY) ? unit_.yAccel_ + gravity_ : unit_.yAccel_;
}


void UnitBase::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:
		//天井に衝突していたら行う処理
		unit_.yAccel_ = 0.0f;
		break;
	case Collision::DOWN:
		//地面に接地していたら行う処理
		unit_.yAccel_ = 0.0f;
		unit_.isGround_ = true;
		unit_.isGravity_ = false;
		break;
	case Collision::LEFT:
		//左側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0.0f;
		break;
	case Collision::RIGHT:
		//右側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0.0f;
		break;
	}
}

void UnitBase::ChangeDispPos(void)
{
	unit_.disppos_.x = unit_.pos_.x - Camera::GetInstance().GetPos().x;
	unit_.disppos_.y = unit_.pos_.y - Camera::GetInstance().GetPos().y;
}


const Vector2F UnitBase::GetMoveVec(const Vector2F _start, const Vector2F _goal, const float _speed)const
{
	//スピードの設定
	float s = (_speed == 0.0f) ? unit_.speed_ : _speed;
	
	//標的への方向ベクトルを取得
	Vector2F targetVec = { _goal.x- _start.x ,_goal.y-_start.y  };

	//正規化
	float len = std::sqrtf(targetVec.x * targetVec.x+targetVec.y * targetVec.y);
	if (len == 0.0f)return Vector2F(0.0f, 0.0f);
	targetVec = { targetVec.x / len, targetVec.y / len };

	//移動量を求める
	Vector2F ret = { targetVec.x * s , targetVec.y * s };

	return ret;
}

const float UnitBase::GetDis(const Vector2F _start, const Vector2F _goal) const
{
	Vector2F targetVec = { _goal.x - _start.x ,_goal.y - _start.y };

	float dis = std::sqrtf(targetVec.x * targetVec.x + targetVec.y * targetVec.y);

	return dis;
}

/// <summary>
/// HPバーの表示
/// </summary>
/// <param name="x1">左上X座標</param>
/// <param name="y1">左上Y座標</param>
/// <param name="x2">右下X座標</param>
/// <param name="y2">右下Y座標</param>
/// <param name="hp">現在のHP/MP</param>
/// <param name="maxHp">最大HP/MP</param>
/// <param name="color">バーの色</param>
/// <param name="frameColor"></param>
/// <param name="backColor"></param>
void UnitBase::DrawBar(
	int x1, int y1,               
	int x2, int y2,               
	int hp, int maxHp,            
	COLORREF color,               
	COLORREF frameColor,
	COLORREF backColor)
{
	int barX = x2 - x1;
	int barY = y2 - y1;

	if (maxHp <= 0) return; 

	float block = static_cast<float>(barX) / maxHp;

	//外枠を描画
	DrawBox(x1 - 1, y1 - 1, x2 + 1, y2 + 1, frameColor, false);

	//背景バー（空HP）
	for (int i = 0; i < maxHp; ++i) {
		int left = static_cast<int>(x1 + block * i);
		int right = static_cast<int>(x1 + block * (i + 1));
		DrawBox(left, y1, right - 1, y2, backColor, true);
	}

	//現在HPの表示
	for (int i = 0; i < hp; ++i) {
		int left = static_cast<int>(x1 + block * i);
		int right = static_cast<int>(x1 + block * (i + 1));
		DrawBox(left, y1, right - 1, y2, color, true);
	}
}