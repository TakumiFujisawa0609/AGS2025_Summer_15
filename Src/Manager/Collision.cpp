#include"Collision.h"

#include<DxLib.h>

#include"../Application.h"

Collision* Collision::instance = nullptr;

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init()
{
	this->Release();
}


const float Collision::GetStageLine(const Vector2F& pos, const Vector2F& size , const DIR dir) const
{
	// 探索方向に合わせて初期位置を調整
	Vector2F work = pos;
	if (dir == UP) {
		work.y -= size.y / 2;
		work.x -= size.x / 2;
	}
	else if (dir == DOWN) {
		work.y += size.y / 2;
		work.x -= size.x / 2;
	}
	else if (dir == LEFT) {
		work.x -= size.x / 2;
		work.y -= size.y / 2;
	}
	else if (dir == RIGHT) {
		work.x += size.x / 2;
		work.y -= size.y / 2;
	}

	// 座標をチップ配列番号に変換
	int pX = static_cast<int>(work.x / TutorialStage::STAGE_CHIP_SIZE);
	int pY = static_cast<int>(work.y / TutorialStage::STAGE_CHIP_SIZE);

	int searchRange = 1;
	int sizePix = (dir == UP || dir == DOWN) ? (int)size.x : (int)size.y;
	int offsetPix = (dir == UP || dir == DOWN) ? (int)work.x : (int)work.y;

	searchRange += sizePix / TutorialStage::STAGE_CHIP_SIZE;
	if (sizePix % TutorialStage::STAGE_CHIP_SIZE == 0) searchRange--;
	if (offsetPix % TutorialStage::STAGE_CHIP_SIZE > TutorialStage::STAGE_CHIP_SIZE - (sizePix % TutorialStage::STAGE_CHIP_SIZE)) searchRange++;
	if (sizePix % TutorialStage::STAGE_CHIP_SIZE == 0 && offsetPix % TutorialStage::STAGE_CHIP_SIZE > 0) searchRange++;

	int line = (dir == UP || dir == DOWN) ? pY : pX;
	int step = (dir == UP || dir == LEFT) ? -1 : 1;
	bool bre = false;

	while (true) {
		for (int i = 0; i < searchRange; ++i) {
			int x = (dir == UP || dir == DOWN) ? pX + i : line;
			int y = (dir == LEFT || dir == RIGHT) ? pY + i : line;

			if (x < 0 || x >= mapData.at(0).size() || y < 0 || y >= mapData.size()) {
				if (x < 0 || x >= mapData.at(0).size() || y < 0 || y >= mapData.size() + 5)bre = true;
				break;
			}

			if (mapData.at(y).at(x) != -1) {
				bre = true;
				break;
			}
		}

		if (bre) break;

		// ステージの端に到達してたら終了
		if (step == -1 && line <= 0) break;

		int limit = (dir == UP || dir == DOWN) ? mapData.size() + 5 : mapData.at(0).size();
		if (step == 1 && line >= limit) break;

		// 到達していなかったら1つ先をチェックしにいく
		line += step;
	}

	// 1つ手前に戻る（UP/LEFT時）(ただし、ステージの端に到達していた場合戻らない)
	if (step == -1 && line > 0) line++;

	return static_cast<float>(line * TutorialStage::STAGE_CHIP_SIZE);
}

const bool Collision::StageCollision(const Vector2F& pos, const Vector2F& size) const
{
	for (int dir = 0; dir < DIR::MAX; dir++) {
		float point = 0.0f;

		switch (dir)
		{
		case Collision::UP:
			point = pos.y - (size.y / 2);
			break;
		case Collision::DOWN:
			point = pos.y + (size.y / 2);
			break;
		case Collision::LEFT:
			point = pos.x - (size.x / 2);
			break;
		case Collision::RIGHT:
			point = pos.x + (size.x / 2);
			break;
		}

		float line = GetStageLine(pos, size, (DIR)dir);

		int step = (dir == UP || dir == LEFT) ? -1 : 1;

		if (step == -1) {
			if (point <= line)return true;
		}
		else {
			if (point >= line)return true;
		}

	}
	return false;
}



const bool Collision::Circle(const Base& u1, const Base& u2, bool invici) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;
	if (invici) {
		if (u1.inviCounter_ > 0 || u2.inviCounter_ > 0)return false;
	}

	//2点間のベクトルを作成
	Vector2F vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//作成したベクトルの大きさを計算
	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	//衝突判定
	if (distance < u1.radius_ + u2.radius_)return true;


	return false;
}

const bool Collision::Rect(const Base& u1, const Base& u2, bool invici) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;
	if (invici) {
		if (u1.inviCounter_ > 0 || u2.inviCounter_ > 0)return false;
	}

	//衝突判定に必要な情報をまとめる
	struct rec
	{
		float up;
		float down;
		float left;
		float right;
	};

	rec r1, r2;
	r1 = { u1.pos_.y - u1.size_.y / 2,		u1.pos_.y + u1.size_.y / 2,		u1.pos_.x - u1.size_.x / 2,		u1.pos_.x + u1.size_.x / 2 };
	r2 = { u2.pos_.y - u2.size_.y / 2,		u2.pos_.y + u2.size_.y / 2,		u2.pos_.x - u2.size_.x / 2,		u2.pos_.x + u2.size_.x / 2 };


	//衝突判定
	if (r1.up	 < r2.down	&&
		r1.down  > r2.up	&&
		r1.left	 < r2.right &&
		r1.right > r2.left	) {
		return true;
	}

	return false;
}

const bool Collision::Ellipse(const Base& u1, const Base& u2, bool invici) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;
	if (invici) {
		if (u1.inviCounter_ > 0 || u2.inviCounter_ > 0)return false;
	}
	//2点間のベクトルを作成
	Vector2F vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//各方向の半径の和を計算
	Vector2F radius = { (u1.size_.x + u2.size_.x) / 2,	(u1.size_.y + u2.size_.y) / 2 };


	// 正規化された距離での楕円衝突判定（楕円空間での距離が1以下なら衝突）
	float norm = ((vec.x * vec.x) / (radius.x * radius.x)) + ((vec.y * vec.y) / (radius.y * radius.y));

	return norm <= 1.0f;
}



const bool Collision::CircleAndRect(const Base& circle, const Base& rect, bool invici) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!circle.isAlive_ || !rect.isAlive_) return false;
	if (invici) {
		if (circle.inviCounter_ > 0 || rect.inviCounter_ > 0)return false;
	}


	//衝突判定

	RECT work;

	work = { rect.pos_,{rect.size_.x,rect.size_.y + (circle.radius_ * 2)} };
	if (RectAndPixel(work, circle.pos_))return true;

	work = { rect.pos_,{rect.size_.x + (circle.radius_ * 2),rect.size_.y} };
	if (RectAndPixel(work, circle.pos_))return true;

	Vector2F top = { 0.0f,0.0f };
	Vector2F vec = { rect.pos_.x - circle.pos_.x,	rect.pos_.y - circle.pos_.y };
	if (vec.x > 0 && vec.y > 0) top = { rect.pos_.x - (rect.size_.x / 2),	rect.pos_.y - (rect.size_.y / 2) };

	if (vec.x < 0 && vec.y > 0) top = { rect.pos_.x + (rect.size_.x / 2),	rect.pos_.y - (rect.size_.y / 2) };

	if (vec.x > 0 && vec.y < 0) top = { rect.pos_.x - (rect.size_.x / 2),	rect.pos_.y + (rect.size_.y / 2) };

	if (vec.x < 0 && vec.y < 0) top = { rect.pos_.x + (rect.size_.x / 2),	rect.pos_.y + (rect.size_.y / 2) };

	CIRCLE topcircle = { top,circle.radius_ };

	if (CircleAndPixel(topcircle, circle.pos_))return true;

	return false;
}


	// 円とカプセルの当たり判定
	const bool Collision::CircleAndCapsule(const Base& circle, const Base& capsule, bool invici) const
	{
		// カプセルの中心線ベクトルを計算
		Vector2F seg = { capsule.capsuleEndPos_.x - capsule.capsuleStartPos_.x,
					capsule.capsuleEndPos_.y - capsule.capsuleStartPos_.y };
		// カプセル始点から円中心へのベクトル
		Vector2F toCircle = { circle.pos_.x - capsule.capsuleStartPos_.x,
			circle.pos_.y - capsule.capsuleStartPos_.y };
		// 中心線の長さの2乗
		float segLen = seg.x * seg.x + seg.y * seg.y;
		float t = 0.0f;
		if (segLen > 0.0f) {
			// 円中心からカプセル中心線への射影係数（0～1にクランプ）
			t = (toCircle.x * seg.x + toCircle.y * seg.y) / segLen;
			t = (t < 0.0f) ? 0.0f : (t > 1.0f ? 1.0f : t);
		}
		// カプセル中心線上の最近点
		Vector2F closest = { capsule.capsuleStartPos_.x + seg.x * t,
			capsule.capsuleStartPos_.y + seg.y * t };

		// 最近点と円中心の距離の2乗
		float dx = closest.x - circle.pos_.x;
		float dy = closest.y - circle.pos_.y;
		float dis = dx * dx + dy * dy;
		// 半径の和
		float r = capsule.radius_ + circle.radius_;
		// 距離が半径の和以下なら衝突
		return dis <= r * r;
	}


//private-----------------------------------------------------------------------------------------------------------




const bool Collision::CircleAndPixel(const CIRCLE& circle, const Vector2F& pixel) const
{
	Vector2F vec = { circle.pos.x - pixel.x,	circle.pos.y - pixel.y };

	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (distance < circle.radius)return true;

	return false;
}

const bool Collision::RectAndPixel(const RECT& rect, const Vector2F& pixel) const
{
	if (rect.pos.x - rect.size.x / 2 < pixel.x &&
		rect.pos.y - rect.size.y / 2 < pixel.y &&
		rect.pos.x + rect.size.x / 2 > pixel.x &&
		rect.pos.y + rect.size.y / 2 > pixel.y) {
		return true;
	}
	return false;
}



void Collision::Release(void)
{
	for (auto& map : mapData) {
		map.second.clear();
	}
	mapData.clear();
}