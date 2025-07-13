#include "Spine.h"

Spine::Spine()
{
}

Spine::~Spine()
{
}

void Spine::Init(const Vector2F* pos)
{
}

void Spine::Update(void)
{
    // 棘の出現間隔（フレーム数）
    static const int kInterval = 60;
    // 棘の最大数
    static const int kMaxSpines = 5;
    // 棘のY座標（下から出てくる）
    static const float kStartY = 480.0f; // 画面下端（仮）
    static const float kEndY = 400.0f;   // 棘が出現しきるY座標（仮）
    // 棘のX座標の等間隔配置
    static const float kStartX = 100.0f;
    static const float kSpacing = 80.0f;

    struct SpineData {
        Vector2F pos;
        bool active;
        int timer;
    };
    static SpineData spines[kMaxSpines];
    static int frame = 0;

    // 初期化
    if (frame == 0) {
        for (int i = 0; i < kMaxSpines; ++i) {
            spines[i].pos = Vector2F(kStartX + i * kSpacing, kStartY);
            spines[i].active = false;
            spines[i].timer = 0;
        }
    }

    // 棘の出現管理
    if (frame % kInterval == 0) {
        for (int i = 0; i < kMaxSpines; ++i) {
            if (!spines[i].active) {
                spines[i].active = true;
                spines[i].timer = 0;
                break;
            }
        }
    }

    // 棘の更新
    for (int i = 0; i < kMaxSpines; ++i) {
        if (spines[i].active) {
            // 下から上に移動
            float t = spines[i].timer / 30.0f; // 30フレームで出現
            if (t > 1.0f) t = 1.0f;
            spines[i].pos.y = kStartY + (kEndY - kStartY) * t;
            spines[i].timer++;
            // 一定時間後に非アクティブ化
            if (spines[i].timer > 60) {
                spines[i].active = false;
                spines[i].pos.y = kStartY;
            }
        }
    }

    frame++;
}

void Spine::Draw(void)
{
}

void Spine::Release(void)
{
}
