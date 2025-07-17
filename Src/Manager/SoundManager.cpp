#include "SoundManager.h"

#include<DxLib.h>

SoundManager* SoundManager::ins_ = nullptr;

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
	sounds_[s].id_ = LoadSoundMem(("Data/Sound/" + sounds_[s].path_).c_str());
	sounds_[s].type_ = s;
}

void SoundManager::Play(SOUND s, bool over, int volume, bool loop, bool topPlay)
{
	// 読み込まれていなかったら再生しない
	if (sounds_[s].id_ == -1) return;

	// 再生中だったら再生しない
	if ((CheckSoundMem(sounds_[s].id_) == 1) && !over)return;

	// 情報を記録
	sounds_[s].loop_ = loop;
	sounds_[s].paused_ = false;

	// 音量を設定
	if (sounds_[s].volume_ != volume) {
		sounds_[s].volume_ = volume;
		ChangeVolumeSoundMem(sounds_[s].volume_, sounds_[s].id_);
	}

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
	StopSoundMem(sounds_[s].id_);
}

void SoundManager::AllStop(void)
{
	for (auto& sound : sounds_) {
		if (sound.id_ == -1)continue;
		if (CheckSoundMem(sound.id_) == 0)continue;

		sound.paused_ = true;
		StopSoundMem(sound.id_);
	}
}

void SoundManager::PausePlay(void)
{
	for (auto& sound : sounds_) {
		if (!sound.paused_)continue;

		Play(sound.type_, false, sound.volume_, sound.loop_, false);
	}
}

void SoundManager::Delete(SOUND s)
{
	// 中身がなかったら早期リターン
	if (sounds_[s].id_ == -1) return;

	// 中身を消去して-1を入れとく
	DeleteSoundMem(sounds_[s].id_);
	sounds_[s].id_ = -1;
	sounds_[s].paused_ = false;
	sounds_[s].volume_ = 255;
}

void SoundManager::Init(void)
{
	// ハンドルIDの変数内をすべて-1で初期化
	// 一時停止判定を初期化
	for (auto& sound : sounds_) {
		sound.id_ = -1;
		sound.paused_ = false;
		sound.volume_ = 255;
	}

	// 使用するデータのパスを入れておく("Data/Sound/～～"←ここから先のパス)
	sounds_[SOUND::SLASH].path_ = "斬撃.mp3";
	sounds_[SOUND::DAMAGE].path_ = "被弾.mp3";
	sounds_[SOUND::BPHIT].path_ = "爆発.mp3";
	sounds_[SOUND::EVASION].path_ = "回避.mp3";
	sounds_[SOUND::BPTHROW].path_ = "竹投げ.mp3";
	sounds_[SOUND::RUN].path_ = "足音.mp3";
	//晩ムーン
	sounds_[SOUND::BAMMOONPUNCH].path_ = "Bammoon/打撃.mp3";
	sounds_[SOUND::BAMMOONMOVE].path_ = "Bammoon/移動.mp3";
	sounds_[SOUND::BAMMOONLANDING].path_ = "Bammoon/着地.mp3";
	sounds_[SOUND::BAMMOONCSPHERE].path_ = "Bammoon/Csphere.mp3";
	sounds_[SOUND::BAMMOONBLASTTHROW].path_ = "竹投げ.mp3";
	sounds_[SOUND::BAMMOONBLAST].path_ = "爆発.mp3";
	sounds_[SOUND::BAMMOONDAMAGE].path_ = "被弾.mp3";
	//ちゅーとりある
	sounds_[SOUND::TUTORIALJUMP].path_ = "踏み込み.mp3";
	sounds_[SOUND::TUTORIALLANDING].path_ = "Bammoon/着地.mp3";
	sounds_[SOUND::TUTORIALDAMAGE].path_ = "被弾.mp3";
	sounds_[SOUND::TUTORIALSLASH].path_ = "斬撃.mp3";
	sounds_[SOUND::TUTORIALBLAST].path_ = "爆発.mp3";
	sounds_[SOUND::TUTORIALBLASTTHSROW].path_ = "竹投げ.mp3";
	//のコピー
	sounds_[SOUND::NOKOPYBEAM].path_ = "Nokopy/ビーム.mp3";
	sounds_[SOUND::NOKOPYDOWN].path_ = "Nokopy/ダウン.mp3";
	sounds_[SOUND::NOKOPYRUSH].path_ = "Nokopy/ラッシュ.mp3";
	sounds_[SOUND::NOKOPYSPINE].path_ = "Nokopy/生える.mp3";
	sounds_[SOUND::NOKOPYWAVE].path_ = "Nokopy/波.mp3";
	sounds_[SOUND::NOKOPYDAMAGE].path_ = "被弾.mp3";


	sounds_[SOUND::BGM1].path_ = "BGM候補１.mp3";
}

void SoundManager:: Release(void)
{
	// 消去されていないものをすべて解放する
	for (auto& sound : sounds_) {
		if (sound.id_ != -1) { DeleteSoundMem(sound.id_); }
	}
}