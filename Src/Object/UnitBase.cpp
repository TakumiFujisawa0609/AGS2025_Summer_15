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

	gravity_ = GRAVITY;
}

UnitBase::~UnitBase()
{

}

void UnitBase::Update()
{

	UpdatePos();

	ChangeDispPos();
}


void UnitBase::UpdatePos(void)
{
	UpdatePosX();
	UpdatePosY();
}


void UnitBase::UpdatePosX(void)
{
	MoveX();
	unit_.pos_.x += unit_.xAccel_;
	CollisionStageX();
}


void UnitBase::UpdatePosY(void)
{
	unit_.isGravity_ = true;
	MoveY();
	unit_.pos_.y += unit_.yAccel_;
	CollisionStageY();
}



void UnitBase::Gravity(void)
{
	//Y軸加速度に重力を加える
	if (!unit_.isGravity_)return;
	unit_.yAccel_ = (unit_.yAccel_ < MAX_GRAVITY) ? unit_.yAccel_ + gravity_ : unit_.yAccel_;
}


void UnitBase::CollisionStageY(void)
{
	Collision& ins = Collision::GetInstance();

	////天井
	if ((unit_.pos_.y - unit_.size_.y / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP)) {
		unit_.pos_.y = ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP) + unit_.size_.y / 2;
		IsGround(Collision::DIR::UP);
	}

	//空中にいるなら重力を加える
	if (unit_.pos_.y + unit_.size_.y / 2 >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) {
		//地面に接地
		unit_.pos_.y = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) - unit_.size_.y / 2;
		IsGround(Collision::DIR::DOWN);
	}
	else {
		Gravity();
	}
}


void UnitBase::CollisionStageX(void)
{
	Collision& ins = Collision::GetInstance();

	//左
	if ((unit_.pos_.x - unit_.size_.x / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::LEFT)) {
		unit_.pos_.x = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::LEFT)) + unit_.size_.x / 2;
		IsGround(Collision::DIR::LEFT);
	}

	//右
	if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT)) {
		unit_.pos_.x = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::RIGHT)) - unit_.size_.x / 2;
		IsGround(Collision::DIR::RIGHT);
	}
}


void UnitBase::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:
		//天井に衝突していたら行う処理
		break;
	case Collision::DOWN:
		//地面に接地していたら行う処理
		unit_.yAccel_ = 0;
		unit_.isGround_ = true;
		unit_.isGravity_ = false;
		break;
	case Collision::LEFT:
		//左側の壁に衝突していたら行う処理
		break;
	case Collision::RIGHT:
		//右側の壁に衝突していたら行う処理
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
	//こっちのがよくない？-------------------------------------------------------------------------------------
	// <.hの定義>
	// 
	// (変更前)
	// const Vector2F GetMoveVec(const Vector2F _start, const Vector2F _goal,  const float _speed = 1.0f)const;
	// (変更後)
	// const Vector2F GetMoveVec(const Vector2F _start, const Vector2F _goal,  const float _speed = 0.0f)const;
	//																								↑変更
	// <.cppの関数の中身>
	// 
	// (追加)
	// スピードの設定
	// float s = (_speed == 0.0f) ? unit_.speed_ : _speed;
	// 
	// (変更前)
	// //移動量を求める
	// Vector2F ret = { targetVec.x * _speed,targetVec.y * _speed };
	// (変更後)
	// //移動量を求める
	// Vector2F ret = { targetVec.x * s , targetVec.y * s };
	//----------------------------------------------------------------------------------------------------------
	
	//標的への方向ベクトルを取得
	Vector2F targetVec = { _goal.x- _start.x ,_goal.y-_start.y  };

	//正規化
	float len = std::sqrtf(targetVec.x * targetVec.x+targetVec.y * targetVec.y);
	if (len == 0.0f)return Vector2F(0.0f, 0.0f);
	targetVec = { targetVec.x / len, targetVec.y / len };

	//移動量を求める
	Vector2F ret = { targetVec.x * _speed,targetVec.y * _speed };

	return ret;
}