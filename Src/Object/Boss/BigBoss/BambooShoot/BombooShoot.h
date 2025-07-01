#include "../BossBase.h"

class BombooShoot : public BossBase
{
public:
    static constexpr int SIZE_X = 200;
    static constexpr int SIZE_Y = 249;


    static constexpr int BOSS_HP = 500;

	enum DRAW
	{
		NORMAL,

		DRAW_MAX,
	};

	enum ATTACK
	{
		NON = -1,
		
		MAX,
	};

    BombooShoot();
    ~BombooShoot();

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    //ゲッター関数
    std::vector<Base*> GetObj(void) override;
    //セッター関数
    void SetDamage(int dmg);

    //攻撃パターンの関数ポインタ
    using AttackFunc = void(BombooShoot::*)();

private:
    //状態ごとのハンドル番号
    int img_[DRAW::DRAW_MAX];

    //状態ごとの行動
    void Idle(void) override;
    void Move(void) override;
    void Attack(void) override;
    void Damage(void) override;
    void Death(void) override;

    //攻撃
    ATTACK attackState_;
    //攻撃パターンの関数ポインタをmapで管理
    std::map<ATTACK, AttackFunc> attackUpdateFuncs_;
    //攻撃用カウンター
    int attackCounter_;
    //攻撃状態管理

    //攻撃の状態ごとの行動



    void IsGround(Collision::DIR dir) override;
};
