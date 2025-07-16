#include "SoundManager.h"

#include<DxLib.h>

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Load(SOUND s)
{
	// すでに読み込まれていたら読み込まない
	if (ids_[s] != -1) return;

	// 読み込み
	ids_[s] = LoadSoundMem(("Data/Sound" + path[s]).c_str());
}

void SoundManager::Play(SOUND s, bool loop,bool topPlay)
{
	// 読み込まれていなかったら再生しない
	if (ids_[s] == -1) return;

	// 再生
	PlaySoundMem(ids_[s], (loop) ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, topPlay);
}

void SoundManager::Delete(SOUND s)
{
	// 中身がなかったら早期リターン
	if (ids_[s] == -1) return;

	// 中身を消去して-1を入れとく
	DeleteSoundMem(ids_[s]);
	ids_[s] = -1;
}

void SoundManager::Init(void)
{
	// ハンドルIDの変数内をすべて-1で初期化
	for (auto& id : ids_) { id = -1; }

	// 使用するデータのパスを入れておく("Data/Sound/～～"←ここから先のパス)
	path[SOUND::TEST] = "test.mp3";
}

void SoundManager:: Release(void)
{
	// 消去されていないものをすべて解放する
	for (auto& id : ids_) {
		if (id != -1) { DeleteSoundMem(id); }
	}
}