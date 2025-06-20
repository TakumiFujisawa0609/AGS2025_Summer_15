#include "UiManager.h"
UiManager* UiManager::instance_ = nullptr;

UiManager::UiManager(void) {}
UiManager::~UiManager(void) {}

void UiManager::AddEffect(std::unique_ptr<UiBase> ui, const Vector2F* generatePos)
{
	ui->SetPos(*generatePos);
	uis_.emplace_back(std::move(ui));

}

void UiManager::Init(void)
{
	for (auto& ui : uis_)
	{
		ui->Init();
	}
}

void UiManager::Update(void)
{
	for (auto& ui : uis_)
	{
		ui->Update();
	}
	uis_.erase(
		std::remove_if(uis_.begin(), uis_.end(),
			[](const std::unique_ptr<UiBase>& ui)
			{
				return !ui->GetUnit().isAlive_;
			}),
		uis_.end()
	);
}

void UiManager::Draw(void)
{
	for (auto& ui : uis_)
	{
		ui->Draw();
	}
}

void UiManager::Release(void)
{
	for (auto& ui : uis_)
	{
		ui->Release();
	}
	uis_.clear();
}

void UiManager::ChangeSceneUi(void)
{
    // SceneManagerのインスタンスとSceneId取得を仮定
    // SceneIdによってuis_を切り替える
    // 例: SceneIdはenumで定義されていると仮定
    // 必要に応じてUiBase派生クラスをinclude

    // 既存UIを解放
    for (auto& ui : uis_) {
        ui->Release();
    }
    uis_.clear();

    // SceneId取得
    auto sceneId = SceneManager::GetInstance().GetSceneID();

    switch (sceneId)
    {
    case SceneManager::SCENE_ID::TITLE:
        // タイトル用UI追加
        // uis_.emplace_back(std::make_unique<UiTitle>());
        break;
    case SceneManager::SCENE_ID::MODESELECT:
        //モードセレクト用UI追加
        //uis_.emplace_back(std::make_unique<UiModeSelect>());
        break;
    case SceneManager::SCENE_ID::TUTORIAL:
        // ゲーム用UI追加
        // uis_.emplace_back(std::make_unique<UiGame>());
        break;
    case SceneManager::SCENE_ID::BATTLEDONE:
        //バトルドーム用Ui追加
        //uis_.emplace_back(std::make_unique<UiBattleDome>());
        break;
    case SceneManager::SCENE_ID::GAMEOVER:
        //ゲームオーバー用Ui追加
        //uis_.emplace_back(std::make_unique<UiGameOver>());
        break;
    case SceneManager::SCENE_ID::CLEAR:
        //ゲームクリア用Ui追加
        //uis_.emplace_back(std::make_unique<UiGameClear>());
        break;
    }

    // 必要ならInit呼び出し
    for (auto& ui : uis_) {
        ui->Init();
    }
}
