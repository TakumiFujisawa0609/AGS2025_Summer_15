#pragma once
#include<memory>
#include"../Object/Ui/UiBase.h"
#include"SceneManager.h"

class UiBase;

class UiManager
{
public:
    // シングルトン（生成・取得・削除）
    static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new UiManager(); } };
    static UiManager* GetInstance(void) { return instance_; };
    static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

    // エフェクト追加（ID指定）
    void AddUi(std::unique_ptr<UiBase>ui);

    // 全エフェクトの更新・描画・解放
    void Init(void);
    void Update(void);
    void Draw(void);
    void Release(void);

private:
    // デフォルトコンストラクタをprivateにして、外部から生成できない様にする
    UiManager(void);
    // デストラクタも同様
    ~UiManager(void);

    // コピー・ムーブ操作を禁止
    UiManager(const UiManager&) = delete;
    UiManager& operator=(const UiManager&) = delete;
    UiManager(UiManager&&) = delete;
    UiManager& operator=(UiManager&&) = delete;
    static UiManager* instance_;
    std::vector<std::unique_ptr<UiBase>>uis_;

    Vector2F generatePos_;      //生成用座標
};