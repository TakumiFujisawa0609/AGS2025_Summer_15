#pragma once

#include"../BossBase.h"

class BamBlast;
class Pbullet;

class Bammoon : public BossBase
{
public:
	static constexpr int HP_MAX = 1000;

	static const int LOAD_SIZE_X = 512;
	static const int LOAD_SIZE_Y = 512;

	static constexpr float SCALE = 0.5f;

	static constexpr int SIZE_X = (LOAD_SIZE_X * SCALE) - 50;
	static constexpr int SIZE_Y = (LOAD_SIZE_Y * SCALE) - 30;

	enum class MOTION
	{
		IDLE,
		RUN,
		JUMP,
		ATTACK,
		DAMAGE,
		DEATH,

		MAX,
	};

	static constexpr int ANIMATION_SPEED = 5;

	static constexpr int IDLE_LOAD_NUM = 4;
	static constexpr int ATTACK_LOAD_NUM = 3;

	enum class ATTACK
	{
		NON = -1,
		SWEEP,
		BLAST,
		PBULLET,

		MAX,
	};

	Bammoon();
	~Bammoon();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	std::vector<Base> GetObj(void) override;
	AttackBase* GetAttackIns(void)override;

	void SetDamage(int dmg)override;
	void ObjHit(int i)override;

	int GetAttackState(void)override { return (int)attackState_; }

	void SetDown(Vector2F pos)override;


private:
	//ƒ{ƒX•`‰æŠÖŒW-------------------------------------------------------------------
	std::vector<int> image_[(int)MOTION::MAX];		//‰æ‘œƒnƒ“ƒhƒ‹

	void LoadBammoonImage(void);

	void DrawBammoonImage(void);
	void Animation(void);
	void ChangeMotion(MOTION m, bool loop = true);

	MOTION motion_;

	int animeCounter_;
	int animeInterval_;
	bool animeLoop_;

	const float GetAnimeRatio(void)const { return ((float)animeCounter_ / (float)image_[(int)motion_].size()); }

	//---------------------------------------------------------------------------------


	int counter_;

	//‘Ò‹@ó‘Ô—p``
	void Idle(void) override;
	//ŠÖ”
	
	//•Ï”
	int idleTime_;


	//ˆÚ“®ó‘Ô``
	void Move(void) override;
	//ŠÖ”

	//•Ï”


	//UŒ‚ó‘Ô``
	void Attack(void) override;
	//ŠÖ”
	void AttackUpdate(void);
	void AttackDraw(void);
	void AttackRand(void);

	//•Ï”
	ATTACK attackState_;
	BamBlast* blast_;
	Pbullet* pBullet_;

	//ƒ_ƒ[ƒWó‘Ô``
	void Damage(void) override;
	//ŠÖ”

	//•Ï”
	

	//€–Só‘Ô``
	void Death(void) override;
	//ŠÖ”

	//•Ï”



	//w’è‚µ‚½À•W‚Ì•ûŒü‚ğŒü‚­
	void TargetLook(Vector2F target);

	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};

