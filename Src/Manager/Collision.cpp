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

float Collision::GetStageFoot(Vector2F pos,float size)
{
	//足元座標の作成
	Vector2F foot = pos;
	foot.y += size / 2;

	//足元の座標を配列の要素数に直す
	int pX = static_cast<int>(foot.x / Stage::STAGE_CHIP_SIZE);
	int pY = static_cast<int>(foot.y / Stage::STAGE_CHIP_SIZE);

	//白色ブロックが続く間は行う
	while (mapData_[pY][pX] == static_cast<int>(Stage::TILE::WHITE)) {
		//一つ下のブロックに移動
		pY++;
	}

	//要素指数＊チップ一つの大きさが床の位置
	return static_cast<float>(pY * Stage::STAGE_CHIP_SIZE);
}

