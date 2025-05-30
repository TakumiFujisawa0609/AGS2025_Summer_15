#include<cmath>
#include "UnitBase.h"
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/Collision.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"


UnitBase::UnitBase()
{
	unit_.modelId_ = -1;
	unit_.pos_ = { 0.0f,0.0f };
	unit_.size_ = { 0.0f,0.f };

	unit_.radius_ = 0.0f;
	unit_.speed_ = 0.0f;

	unit_.hp_ = 0;

	verticalAcceleration_ = 0.0f;

	gravity_ = GRAVITY;
}

UnitBase::~UnitBase()
{

}

void UnitBase::UpdatePositionY(void)
{
	unit_.pos_.y += verticalAcceleration_;
}

void UnitBase::StageCollisionUpdate()
{

	UpdatePositionY();

	CollisionStageY();
	
	CollisionStageX();

	ChangeDispPos();
}

void UnitBase::Jump(void)
{
	//Y軸加速度にジャンプ力を加える
	verticalAcceleration_ += jumpPower_;
	//Y軸加速度が最大ジャンプ力を超えたら最大ジャンプ量に設定
	verticalAcceleration_ = (verticalAcceleration_ < MAX_JUMP_POWER) ? MAX_JUMP_POWER : verticalAcceleration_;
}

void UnitBase::Gravity(void)
{
	//Y軸加速度に重力を加える
	verticalAcceleration_ = (verticalAcceleration_ < MAX_GRAVITY) ? verticalAcceleration_ += gravity_ : verticalAcceleration_;
}

void UnitBase::CollisionStageY(void)
{
	Collision& ins = Collision::GetInstance();

	////天井
	if ((unit_.pos_.y - unit_.size_.y / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP)) {
		unit_.pos_.y = ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP) + unit_.size_.y / 2;
	}

	//空中にいるなら重力を加える
	if (unit_.pos_.y + unit_.size_.y / 2 >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) {
		//地面に接地
		unit_.pos_.y = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) - unit_.size_.y / 2;
		verticalAcceleration_ = 0;
		jumpPower_ = 0;
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
	}

	//右
	if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT)) {
		unit_.pos_.x = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::RIGHT)) - unit_.size_.x / 2;
	}
}

void UnitBase::ChangeDispPos(void)
{
	unit_.disppos_.x = unit_.pos_.x - Camera::GetInstance().GetPos().x;
	unit_.disppos_.y = unit_.pos_.y - Camera::GetInstance().GetPos().y;


}


const Vector2F UnitBase::GetMoveVec(const Vector2F _start, const Vector2F _goal, const float _speed)const
{
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