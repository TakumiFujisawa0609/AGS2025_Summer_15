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
	if (sounds_[s].id_ != -1) return;

	// 読み込み
	sounds_[s].id_ = LoadSoundMem(("Data/Sound" + sounds_[s].path_).c_str());
	sounds_[s].type_ = s;
}

void SoundManager::Play(SOUND s, bool loop,bool topPlay)
{
	// 読み込まれていなかったら再生しない
	if (sounds_[s].id_ == -1) return;

	// 再生中だったら再生しない
	if (CheckSoundMem(sounds_[s].id_) == 1)return;

	// 情報を記録
	sounds_[s].loop_ = loop;
	sounds_[s].paused_ = false;

	// 再生
	PlaySoundMem(sounds_[s].id_, (sounds_[s].loop_) ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, topPlay);
}

void SoundManager::Stop(SOUND s)
{
	// 読み込まれていなかったら再生しない
	if (sounds_[s].id_ == -1) return;

	// 再生中じゃなかったら早期リターン
	if (CheckSoundMem(sounds_[s].id_) == 0)return;

	// 停止
	DeleteSoundMem(sounds_[s].id_);
}

void SoundManager::AllStop(void)
{
	for (auto& sound : sounds_) {
		if (CheckSoundMem(sound.id_) == 0)continue;

		sound.paused_ = true;
		StopSoundMem(sound.id_);
	}
}

void SoundManager::PausePlay(void)
{
	for (auto& sound : sounds_) {
		if (!sound.paused_)continue;

		Play(sound.type_, sound.loop_, false);
	}
}

void SoundManager::Delete(SOUND s)
{
	// 中身がなかったら早期リターン
	if (sounds_[s].id_ == -1) return;

	// 中身を消去して-1を入れとく
	DeleteSoundMem(sounds_[s].id_);
	sounds_[s].id_ = -1;
}

void SoundManager::Init(void)
{
	// ハンドルIDの変数内をすべて-1で初期化
	// 一時停止判定を初期化
	for (auto& sound : sounds_) {
		sound.id_ = -1;
		sound.paused_ = false;
	}

	// 使用するデータのパスを入れておく("Data/Sound/～～"←ここから先のパス)
	sounds_[SOUND::TEST].path_ = "test.mp3";
}

void SoundManager:: Release(void)
{
	// 消去されていないものをすべて解放する
	for (auto& id : ids_) {
		if (id != -1) { DeleteSoundMem(id); }
	}
}