#include "Stage.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

#include"../../Utility/AsoUtility.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"

Stage::Stage()
{

}

Stage::~Stage()
{
}

bool Stage::Load(void)
{
	if (LoadMapData() == false)return false;

	int err = LoadDivGraph("Data/Image/block.png", STAGE_CHIP_ALL,
		STAGE_CHIP_WIDTH, STAGE_CHIP_HEIGHT,
		STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, stageArrayId);
	if (err == -1)return false;

	return true;
}

//初期化処理
void Stage::Init()
{
	Camera::CreateInstance();
	Camera& camera = Camera::GetInstance();

	Load();
	LoadMapData();

}

//更新処理
void Stage::Update()
{

}
//描画処理
void Stage::Draw()
{
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 0), true);
	
	//マップチップ画像を表示
	for (int yy = 0; yy < STAGE_NUM_Y; yy++) {
		for (int xx = 0; xx < STAGE_NUM_X; xx++) {

			int chip = mapDataArray[yy][xx];

			int dx = STAGE_CHIP_SIZE * xx - Camera::GetInstance().GetPos().x;
			int dy = STAGE_CHIP_SIZE * yy - Camera::GetInstance().GetPos().y;

			DrawGraph(dx, dy, stageArrayId[chip], true);
		}
	}
}

//解放処理
bool Stage::Release()
{
	for (int ii = STAGE_CHIP_ALL; ii > 0; ii--) {
		if (DeleteGraph(stageArrayId[ii - 1]) == -1)return false;
	}

	return true;
}

float Stage::Getfoot(Vector2F pos)
{
	float ret = 0.0f;

	//足元座標の作成
	Vector2F foot = pos;
	foot.y += 10.0f/*(Player::SIZE / 2.0f)*/;

	//足元の座標を配列の要素数に直します
	int pX = static_cast<int>(foot.x / STAGE_CHIP_SIZE);
	int pY = static_cast<int>(foot.y / STAGE_CHIP_SIZE);

	//白色ブロックが続く間は行う
	while (mapDataArray[pY][pX] == static_cast<int>(TILE::WHITE)) {
		//一つ下のブロックに移動
		pY++;
	}

	//要素指数＊チップ一つの大きさが床の位置
	return static_cast<float>(pY * STAGE_CHIP_SIZE);
}

bool Stage::LoadMapData()
{
	memset((int*)&mapDataArray[0], -1, sizeof(int) * STAGE_NUM_MAX);

	//ファイストリームの取得
	std::ifstream ifs = std::ifstream("Data/CSV/Stage.csv");
	if (!ifs)return false;

	std::string line;
	std::vector<std::string> strrSplit;
	int chipNo = 0;
	int yy = 0;

	while (getline(ifs, line))
	{
		strrSplit = AsoUtility::Split(line, ',');
		for (int xx = 0; xx < strrSplit.size(); xx++) {
			chipNo = stoi(strrSplit[xx]);

			mapDataArray[yy][xx] = chipNo;
		}
		yy++;
	}
}