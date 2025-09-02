#pragma once

#include<memory>
#include<list>

#include<map>
#include<DxLib.h>
#include <chrono>
#include"../Common/Vector2.h"
#include"../Application.h"

class SceneBase;
class Fader;

class SceneManager
{
public:
	// ƒV[ƒ“ŠÇ——p
	enum class SCENE_ID
	{
		NONE = -1,
		TITLE,
		TUTORIAL,
		BOSSSELECT,
		BATTLEDONE,
		CLEAR,
		GAMEOVER,
	};

public:

	static void CreateIns(void) { if (ins_ == nullptr) { ins_ = new SceneManager(); ins_->Init(); } }
	static SceneManager& GetIns(void) { return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Destroy(); delete ins_; ins_ = nullptr; } }

private:

	SceneManager(void);
	SceneManager(const SceneManager&);
	~SceneManager(void) = default;


	// ƒCƒ“ƒXƒ^ƒ“ƒX
	static SceneManager* ins_;

	// ¶¬‰Šú‰»
	void Init(void);

	// ƒŠƒ\[ƒX‚Ì”jŠü
	void Destroy(void);

public:

	void Update(void);
	void Draw(void);


	// ó‘Ô‘JˆÚ
	void ChangeScene(std::shared_ptr<SceneBase>scene);
	void ChangeScene(SCENE_ID scene);

	// ƒV[ƒ“‚ğV‚µ‚­Ï‚Ş
	void PushScene(std::shared_ptr<SceneBase>scene);
	void PushScene(SCENE_ID scene);

	// ÅŒã‚É’Ç‰Á‚µ‚½ƒV[ƒ“‚ğíœ‚·‚éB
	void PopScene(void);

	// ‹­§“I‚É“Á’è‚ÌƒV[ƒ“‚É”ò‚ÔBƒŠƒZƒbƒg‚ğ‚©‚¯“Á’è‚ÌƒV[ƒ“‚Ì‚İ‚É‚·‚éB
	void JumpScene(std::shared_ptr<SceneBase>scene);
	void JumpScene(SCENE_ID scene);


	// ƒV[ƒ“ID‚Ìæ“¾
	SCENE_ID GetSceneID(void) { return sceneId_; }




	// ƒfƒ‹ƒ^ƒ^ƒCƒ€‚Ìæ“¾
	float GetDeltaTime(void) const { return deltaTime_; }

	// ‰‰o```````````````````````````````
	void Slow(int time = 10, int inter = 5) { slowCounter_ = time; }

	void HitStop(int stopTime = 5) { hitStopCounter_ = stopTime; }

	// ‰æ–Ê—h‚ê‚Ìí—Ş
	enum ShakeKinds { WID/*‰¡—h‚ê*/, HIG/*c—h‚ê*/, DIAG/*Î‚ß—h‚ê*/, ROUND/*‚­‚é‚­‚é*/ };
	// ‰æ–Ê—h‚ê‚Ì‘å‚«‚³
	enum ShakeSize { SMALL = 3/*¬‚³‚­*/, MEDIUM = 5/*’†‚­‚ç‚¢*/, BIG = 8, /*‘å‚«‚­*/ };

	/// <summary>
	/// ‰æ–Ê—h‚ç‚µ
	/// </summary>
	/// <param name="kinds">—h‚ê•û(enum ShakeKinds ‚ğg—p)</param>
	/// <param name="size">—h‚ê‚é‘å‚«‚³(enum ShakeSize ‚ğg—p)</param>
	/// <param name="time">—h‚ê‚éŠÔ(ƒtƒŒ[ƒ€”)</param>
	void Shake(ShakeKinds kinds = ShakeKinds::DIAG, ShakeSize size = ShakeSize::MEDIUM, int time = 20);

	void ZoomPos(Vector2F pos) { zoomPos_ = pos; }
	void ZoomScale(float scale) { scale_ = scale; }
	//``````````````````````````````````

	void SetMapNum(Vector2 num) { mapNum_ = num; }

	//ƒ{ƒX‚Ìí—Ş
	enum class BOSS_KINDS
	{
		TUTORIAL,
		NOKOPY,
		BAMMOON,
		RUNBOO,

		MAX,
	};
	const BOSS_KINDS GetNowBoss(void)const { return nowBossKinds_; }
	void SetBossKinds(BOSS_KINDS k) { nowBossKinds_ = k; }
	
	/// <summary>
	/// ‘OƒtƒŒ[ƒ€‚ÆŒ»ƒtƒŒ[ƒ€‚Ì’l‚ğ”»’è
	/// </summary>
	/// <param name="classId">”»•Ê—pˆø”(ƒNƒ‰ƒX‚²‚Æ‚É”‚ğ•Ï‚¦‚È‚¢‚Æ‹£‡‚µ‚Ä³‚µ‚­”ä‚×‚ê‚È‚¢)</param>
	/// <param name="i">”ä‚×‚½‚¢’l</param>
	/// <returns>true=‚»‚ê‚Íˆá‚¤‚º/false=“¯‚¶’l</returns>
	bool ThatsNotRight(int classId,int i);

private:
	// ƒV[ƒ“
	std::list<std::shared_ptr<SceneBase>>scenes_;
	SCENE_ID sceneId_;

	// ƒfƒ‹ƒ^ƒ^ƒCƒ€
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	void ResetDeltaTime(void);


	// ƒqƒbƒgƒXƒgƒbƒvƒJƒEƒ“ƒ^[
	const int HIT_STOP_TIME = 5;
	int hitStopCounter_;

	// ƒXƒ[ƒJƒEƒ“ƒ^[
	const int SLOW_TIME = 40;
	int slowCounter_;

	// ‰æ–Ê—h‚ê------------------------
	int mainScreen_;
	int shake_;
	ShakeKinds shakeKinds_;
	ShakeSize shakeSize_;
	Vector2 ShakePoint(void);
	//---------------------------------

	Vector2F zoomPos_;
	float scale_ = 1.0f;

	void ZoomCtr(void);

	Vector2 mapNum_;

	BOSS_KINDS nowBossKinds_;

	std::map<int, int>perValues;
	std::map<int, int>nowValues;
};

using ShakeKinds = SceneManager::ShakeKinds;
using ShakeSize = SceneManager::ShakeSize;

using BOSS_KINDS = SceneManager::BOSS_KINDS;