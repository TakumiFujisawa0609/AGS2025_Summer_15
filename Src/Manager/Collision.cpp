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

const float Collision::GetStageFoot(const Vector2F pos, const Vector2F size , const DIR dir) const
{
	Vector2F work = pos;

	int pX, pY;
	int serchrange;

	pX = pY = 0;
	serchrange = 1;

	bool bre = false;

	switch (dir)
	{
	case Collision::UP:
		work.y -= size.y / 2;
		work.x -= size.x / 2;
		serchrange += (int)size.x / Stage::STAGE_CHIP_SIZE;
		if ((int)work.x % Stage::STAGE_CHIP_SIZE > (int)size.x%Stage::STAGE_CHIP_SIZE  ) {
			serchrange++;
		}

		//足元の座標を配列の要素数に直す
		pX = static_cast<int>(work.x / Stage::STAGE_CHIP_SIZE);
		pY = static_cast<int>(work.y / Stage::STAGE_CHIP_SIZE);


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
		break;

	case Collision::DOWN:
		//足元座標を作成
		work.y += size.y / 2;

		//足元の座標を配列の要素数に直す
		pX = static_cast<int>(work.x / Stage::STAGE_CHIP_SIZE);
		pY = static_cast<int>(work.y / Stage::STAGE_CHIP_SIZE);

		//白色ブロックが続く間は行う
		while (mapData_[pY][pX] == static_cast<int>(Stage::TILE::WHITE)) {
			//一つ下のブロックに移動
			pY++;
		}
		break;

	case Collision::LEFT:
		break;
	case Collision::RIGHT:
		break;
	}

	//要素指数＊チップ一つの大きさが床の位置
	return static_cast<float>(pY * Stage::STAGE_CHIP_SIZE);
}

