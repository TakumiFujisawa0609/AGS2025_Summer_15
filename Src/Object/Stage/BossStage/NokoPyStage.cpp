#include "NokoPyStage.h"

#include<DxLib.h>
#include <string>
#include<fstream>

#include"../../../Application.h"
#include"../../../Manager/Camera.h"

NokoPyStage::NokoPyStage()
{
}

NokoPyStage::~NokoPyStage()
{
}

void NokoPyStage::BackDraw(void)
{
    int num = (STAGE_CHIP_SIZE * mapData_[0].size()) / HAIKEI_SIZE_X + 1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < num; j++) {
            Vector2 d =
            {
                Application::SCREEN_SIZE_X / 2,
                Application::SCREEN_SIZE_Y / 2
            };

            d.x += HAIKEI_SIZE_X * j;

            Vector2 c =
            {
                (int)Camera::GetInstance().GetPos().x / (8 - i),
                (int)Camera::GetInstance().GetPos().y
            };

            d.x -= c.x;
            d.y -= c.y;

            DrawRotaGraph(d.x, d.y, 1, 0, backImg_[i], true);
        }
    }
}

void NokoPyStage::Load(void)
{
    int load[STAGE_CHIP_ALL];

    int err = LoadDivGraph("Data/Image/Stage/ForestTile.png", STAGE_CHIP_ALL,
        STAGE_CHIP_X, STAGE_CHIP_Y,
        STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, load);
    if (err == -1) {
        return;
    }

    chipId_.insert(chipId_.end(), load, load + STAGE_CHIP_ALL);

    haikei_ = LoadGraph("Data/Image/Stage/BackGround.png");

    for (int i = 0; i < 8; i++) {
        std::string filePath = "Data/Image/Stage/Tutorial/TutorialBack" + std::to_string(i) + ".png";
        backImg_[i] = LoadGraph(_T(filePath.c_str()));
    }

}

bool NokoPyStage::LoadMapData(void)
{
    std::ifstream ifs = std::ifstream("Data/CSV/BombooShoot.csv");
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

            mapData_[yy][xx] = chipNo;
        }
        yy++;
    }

    return true;
}

void NokoPyStage::AddRelease(void)
{
    for (auto& id : backImg_) {
        DeleteGraph(id);
    }
}