#include"DefaultAttack.h"

#include<DxLib.h>

#include"../Player.h"
#include"../../../Manager/InputManager.h"
#include"../../../Manager/Camera.h"

DefaultAttack::DefaultAttack()
{
	LoadDivGraph("Data/Image/Boss/SlashAnim.png", ATTACK_NUM,
		ATTACK_NUM, 1, LOAD_SIZE_X, LOAD_SIZE_Y, img);
}

DefaultAttack::~DefaultAttack()
{
}

void DefaultAttack::Init(Vector2F* plPos, AsoUtility::DIRECTION* dir)
{
	plPos_ = plPos;
	dir_ = dir;

	obj_.isAlive_ = false;
	obj_.pos_ = { plPos_->x + Player::SIZE_X,plPos_->y };
	obj_.size_ = { SIZE_X,SIZE_Y };
	obj_.radius_ = SIZE_X;

	attackCount_ = 0;

}

DefaultAttack::UpdateRet DefaultAttack::Update(void)
{
	UpdateRet ret = UpdateRet::Nothing;

	//リキャストタイム中だった
	if (recastTime_ > 0) {
		recastTime_--;
		return UpdateRet::Recast;
	}
	auto& ins = InputManager::GetInstance();
	
	if (ins.IsClickMouseLeft()) {
		if (obj_.isAlive_) {
			ret = UpdateRet::Already;
		}
		else {
			obj_.isAlive_ = true;
			ret = UpdateRet::Action;
		}
	}

	if (obj_.isAlive_) {
		obj_.pos_ = *plPos_;
		obj_.pos_.x += (*dir_ == AsoUtility::DIRECTION::E_DIR_LEFT) ? -(Player::SIZE_X *4) : Player::SIZE_X*4 ;

		attackCount_++;
		if (attackCount_ > ATTACK_NUM) {
			attackCount_ = 0;
			obj_.isAlive_ = false;
			recastTime_ = RECAST_TIME;
			return UpdateRet::AttackEnd;
		}
	}

	return ret;
}

void DefaultAttack::Draw(void)
{
	ChangeDispPos();

	if (obj_.isAlive_) {
		bool isTurn = (*dir_ == AsoUtility::DIRECTION::E_DIR_LEFT) ? true : false;
		DrawRotaGraph(obj_.disppos_.x , obj_.disppos_.y, 0.5f, 0.0f, img[attackCount_], true, isTurn);
	}

}

void DefaultAttack::Release(void)
{
}

void DefaultAttack::Hit()
{
}


void DefaultAttack::ChangeDispPos(void) 
{
	auto& ins = Camera::GetInstance();
	obj_.disppos_ = obj_.pos_ - ins.GetPos();
}