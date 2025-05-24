#include"Collision.h"

#include<DxLib.h>

Collision* Collision::instance = nullptr;

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init()
{
}


const float Collision::GetStageLine(const Vector2F& pos, const Vector2F& size , const DIR dir) const
{
	Vector2F work = pos;

	int pX, pY, serchrange;

	pX = pY = 0;
	serchrange = 1;

	bool bre = false;

	switch (dir)
	{
	case Collision::UP:
		work.y -= size.y / 2;
		work.x -= size.x / 2;
		break;
	case Collision::DOWN:
		work.y += size.y / 2;
		work.x -= size.x / 2;
		break;
	case Collision::LEFT:
		work.x -= size.x / 2;
		work.y -= size.y / 2;
		break;
	case Collision::RIGHT:
		work.x += size.x / 2;
		work.y -= size.y / 2;
		break;
	}

	//座標を配列の要素数に直す
	pX = static_cast<int>(work.x / Stage::STAGE_CHIP_SIZE);
	pY = static_cast<int>(work.y / Stage::STAGE_CHIP_SIZE);

	int ret = 0;

	switch (dir)
	{
	case Collision::UP:

		serchrange += (int)size.x / Stage::STAGE_CHIP_SIZE;
		if ((int)size.x % Stage::STAGE_CHIP_SIZE == 0)serchrange--;
		if ((int)work.x % Stage::STAGE_CHIP_SIZE > Stage::STAGE_CHIP_SIZE - ((int)size.x % Stage::STAGE_CHIP_SIZE)) serchrange++;
		if ((int)size.x % Stage::STAGE_CHIP_SIZE == 0 && (int)work.x % Stage::STAGE_CHIP_SIZE > 0)serchrange++;

		while (mapData_[pY][pX] == (int)Stage::TILE::WHITE)
		{
			for (int x = pX; x < pX + serchrange; x++) {
				if (!(mapData_[pY][x] == (int)Stage::TILE::WHITE)) {
					bre = true;
					break;
				}
			}
			if (bre == true || pY <= 0) break;
			pY--;
		}
		pY++;
		ret = pY;
		break;

	case Collision::DOWN:
		serchrange += (int)size.x / Stage::STAGE_CHIP_SIZE;
		if ((int)size.x % Stage::STAGE_CHIP_SIZE == 0)serchrange--;
		if ((int)work.x % Stage::STAGE_CHIP_SIZE > Stage::STAGE_CHIP_SIZE - ((int)size.x % Stage::STAGE_CHIP_SIZE)) serchrange++;
		if ((int)size.x % Stage::STAGE_CHIP_SIZE == 0 && (int)work.x % Stage::STAGE_CHIP_SIZE > 0)serchrange++;

		while (mapData_[pY][pX] == (int)Stage::TILE::WHITE)
		{
			for (int x = pX; x < pX + serchrange; x++) {
				if (!(mapData_[pY][x] == (int)Stage::TILE::WHITE)) {
					bre = true;
					break;
				}
			}
			if (bre == true || pY >= Stage::STAGE_NUM_Y) break;
			pY++;
		}
		ret = pY;
		break;

	case Collision::LEFT:

		serchrange += (int)size.y / Stage::STAGE_CHIP_SIZE;
		if ((int)size.y % Stage::STAGE_CHIP_SIZE == 0)serchrange--;
		if ((int)work.y % Stage::STAGE_CHIP_SIZE > Stage::STAGE_CHIP_SIZE - ((int)size.y % Stage::STAGE_CHIP_SIZE)) serchrange++;
		if ((int)size.y % Stage::STAGE_CHIP_SIZE == 0 && (int)work.y % Stage::STAGE_CHIP_SIZE > 0)serchrange++;

		while (mapData_[pY][pX] == (int)Stage::TILE::WHITE)
		{
			for (int y = pY; y < pY + serchrange; y++) {
				if (!(mapData_[y][pX] == (int)Stage::TILE::WHITE)) {
					bre = true;
					break;
				}
			}
			if (bre == true || pX <= 0) break;
			pX--;
		}
		pX++;
		ret = pX;
		break;

	case Collision::RIGHT:		

		serchrange += (int)size.y / Stage::STAGE_CHIP_SIZE;
		if ((int)size.y % Stage::STAGE_CHIP_SIZE == 0)serchrange--;
		if ((int)work.y % Stage::STAGE_CHIP_SIZE > Stage::STAGE_CHIP_SIZE - ((int)size.y % Stage::STAGE_CHIP_SIZE)) serchrange++;
		if ((int)size.y % Stage::STAGE_CHIP_SIZE == 0 && (int)work.y % Stage::STAGE_CHIP_SIZE > 0)serchrange++;

		while (mapData_[pY][pX] == (int)Stage::TILE::WHITE)
		{
			for (int y = pY; y < pY + serchrange; y++) {
				if (!(mapData_[y][pX] == (int)Stage::TILE::WHITE)) {
					bre = true;
					break;
				}
			}
			if (bre == true || pX >= Stage::STAGE_NUM_X)break;
			pX++;
		}
		ret = pX;
		break;

	}
	//要素指数＊チップ一つの大きさが床の位置
	return static_cast<float>(ret * Stage::STAGE_CHIP_SIZE);
}



const bool Collision::Circle(const Base& u1, const Base& u2) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;

	//2点間のベクトルを作成
	Vector2F vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//作成したベクトルの大きさを計算
	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	//衝突判定
	if (distance < u1.radius_ + u2.radius_)return true;


	return false;
}

const bool Collision::Rect(const Base& u1, const Base& u2) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;


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

const bool Collision::Ellipse(const Base& u1, const Base& u2) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!u1.isAlive_ || !u2.isAlive_) return false;

	//2点間のベクトルを作成
	Vector2F vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//各方向の半径の和を計算
	Vector2F radius = { (u1.size_.x + u2.size_.x) / 2,	(u1.size_.y + u2.size_.y) / 2 };



	// 正規化された距離での楕円衝突判定（楕円空間での距離が1以下なら衝突）
	float norm = ((vec.x * vec.x) / (radius.x * radius.x)) + ((vec.y * vec.y) / (radius.y * radius.y));

	return norm <= 1.0f;
}



const bool Collision::CircleAndRect(const Base& circle, const Base& rect) const
{
	//どちらかが生存していなければ、当たっていない(false)を返し終了
	if (!circle.isAlive_ || !rect.isAlive_) return false;

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



