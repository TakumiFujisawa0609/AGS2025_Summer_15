#include"Blast.h"
#include"../../../Manager/Camera.h"
#include"../BossTutorial.h"
#include"../../../Manager/SceneManager.h"

Blast::Blast()
{
	reticleImg_ = LoadGraph("Data/Image/Boss/Reticle.png");

	LoadDivGraph("Data/Image/Effect/Blast.png", BLAST_NUM_MAX, BLAST_NUM_X, BLAST_NUM_Y, BLAST_SIZE, BLAST_SIZE, blastImg_);
}

Blast::~Blast()
{
}

void Blast::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);

	obj_.isAlive_ = false;
	end_ = false;
	attackCounter_ = 0;

	obj_.radius_ = 15.0f;
	obj_.size_ = { obj_.radius_,obj_.radius_ };

	obj_.speed_ = 5.0f;

	target_ = { 0.0f,0.0f };
	blast_ = false;

	angle_ = 0.0f;
	expansion_ = 1.0f;

	lookOn_ = false;
}

void Blast::Update(void)
{
	if (!obj_.isAlive_) {
		if (lookOn_) {
			obj_.pos_ = *boss;

			if (boss->x < target_.x)obj_.pos_.x + BossTutorial::SIZE_X / 2;
			else					obj_.pos_.x - BossTutorial::SIZE_X / 2;

			attackCounter_++;
			if (attackCounter_ > 100) { On(); attackCounter_ = 0; }
		}
	}
	else {

		Vector2F vec = { target_.x - obj_.pos_.x,target_.y - obj_.pos_.y };
		float dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

		if (dis < obj_.speed_) {
			obj_.size_ = { (float)BLAST_SIZE,(float)BLAST_SIZE };
			lookOn_ = false;
			blast_ = true;
		}
		else {
			vec = { vec.x / dis,vec.y / dis };

			obj_.pos_.x += vec.x * obj_.speed_;
			obj_.pos_.y += vec.y * obj_.speed_;



			vec = { target_.x - obj_.pos_.x,target_.y - obj_.pos_.y };
			dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

			if (dis < obj_.speed_) SceneManager::GetInstance().SHAKE();
		}


		if (blast_) {
			attackCounter_++;
			if (attackCounter_ > BLAST_NUM_MAX) {
				obj_.isAlive_ = false;
				end_ = true;
			}
		}
	}

	if (lookOn_) {
		angle_ += 0.1f;
		expansion_ = 2 * (std::sin(angle_));
	}

	AttackBase::Update();
}

void Blast::Draw(void)
{
	if (obj_.isAlive_) {
		if (blast_) 
		{
			DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, 1, 0, blastImg_[attackCounter_], true);
		}
		else
		{
			DrawCircleAA(obj_.disppos_.x, obj_.disppos_.y, obj_.radius_, 30, RGB(0, 0, 0));
		}
	}
	auto& camera = Camera::GetInstance();
	Vector2F disp = { target_.x - camera.GetPos().x,target_.y - camera.GetPos().y };

	if (lookOn_) {
		DrawRotaGraph(disp.x, disp.y, expansion_, angle_, reticleImg_, true);
	}

}

void Blast::Release(void)
{
	for (int i = 0; i < BLAST_NUM_MAX; i++) {
		DeleteGraph(blastImg_[i]);
	}
	DeleteGraph(reticleImg_);

}
