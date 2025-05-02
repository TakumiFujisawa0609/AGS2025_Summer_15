#include "Stage.h"

Stage::Stage()
{

}

Stage::~Stage()
{
}

//初期化処理
bool Stage::Init()
{
	// ステージの初期化処理
	int err = LoadDivGraph("Data/Image/block.png", STAGE_CHIP_ALL,
		STAGE_CHIP_WIDTH, STAGE_CHIP_HEIGHT,
		STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, stageArrayId);
	if (err == -1) {
		return false;
	}

	return true;
}

//更新処理
void Stage::Update()
{
	// ステージの更新処理
	// ここにステージの更新コードを追加
}

//描画処理
void Stage::Draw()
{
	// ステージの描画処理
	// ここにステージの描画コードを追加
}

//解放処理
bool Stage::Release()
{
	// ステージの解放処理
	// ここにステージの解放コードを追加
	return true;
}
