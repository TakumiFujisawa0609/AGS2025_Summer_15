#pragma once

#include"../BossBase.h"

class BamBlast;
class Pbullet;
class Stripe;
class Csphere;

class Bammoon : public BossBase
{
public:
	static constexpr int HP_MAX = 700;

	static const int LOAD_SIZE_X = 512;
	static const int LOAD_SIZE_Y = 512;

	static constexpr float SCALE = 0.5f;

	static constexpr int SIZE_X = (LOAD_SIZE_X * (int)SCALE) - 50;
	static constexpr int SIZE_Y = (LOAD_SIZE_Y * (int)SCALE) - 30;

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
		STRIPE,
		CSPHERE,
		BAMLINE,

		MAX,
	};

	const int ATTACKDMG[(int)ATTACK::MAX] =
	{
		3,//SWEEP
		3,//BLAST
		2,//PBULLET
		5,//STRIPE
		1//CSPHERE
	};

	static constexpr int DEATH_DIRECTION_TIME = 150;

	Bammoon();
	~Bammoon();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void DrawHp(void)override;

	std::vector<Base> GetObj(void) override;
	int GetObjDamage(void) { return (attackState_ != ATTACK::NON) ? ATTACKDMG[(int)attackState_] : 0; }
	AttackBase* GetAttackIns(void)override { return nullptr; }

	void SetDamage(int dmg)override;
	void ObjHit(int i)override;

	ATTACK GetAtState(void) { return attackState_; }

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

	bool pinch_;

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
	Stripe* stripe_;
	Csphere* csphere_;

	//ƒ_ƒ[ƒWó‘Ô``
	void Damage(void) override;
	//ŠÖ”

	//•Ï”
	

	//€–Só‘Ô``
	void Death(void) override;
	//ŠÖ”

	//•Ï”
	int deathCou_;


	//w’è‚µ‚½À•W‚Ì•ûŒü‚ğŒü‚­
	void TargetLook(Vector2F target);

	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};

