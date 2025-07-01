#pragma once

#include"../BossBase.h"

class Bammoon : public BossBase
{
public:
	static constexpr int HP_MAX = 100;

	enum class ATTACK
	{
		NON = -1,



		MAX,
	};

	Bammoon();
	~Bammoon();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	std::vector<Base*>GetObj(void)override;

private:

	ATTACK attackStage_;


	//‘Ò‹@ó‘Ô—p``
	void Idle(void) override;
	//•Ï”
	int idleTime_;


	//ˆÚ“®ó‘Ô``
	void Move(void) override;
	//•Ï”


	//UŒ‚ó‘Ô``
	void Attack(void) override;
	//•Ï”
	

	//ƒ_ƒ[ƒWó‘Ô``
	void Damage(void) override;
	//•Ï”
	

	//€–Só‘Ô``
	void Death(void) override;
	//•Ï”


	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};

