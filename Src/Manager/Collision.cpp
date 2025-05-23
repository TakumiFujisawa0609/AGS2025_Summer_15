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

const float Collision::GetStageLine(const Vector2F pos, const Vector2F size , const DIR dir) const
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

