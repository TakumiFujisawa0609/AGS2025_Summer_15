#include "../BossBase.h"


class BamBeam;
class BamBreath;
class Rushoot;
class Wavemboo;

class Nokopy : public BossBase
{
public:
    static constexpr int SIZE_X = 200;
    static constexpr int SIZE_Y = 200;


    static constexpr int BOSS_HP = 500;

    enum  DRAW
    {
        DRAW_IDLE,
        DRAW_BAMBEAM,
        DRAW_BAMBREATH,
        DRAW_WAVEMBOO,
        DRAW_RUSHOOT,

        DRAW_MAX,
    };

    enum  ATTACK
    {
        NON = -1,
        BAMBEAM,
        BAMBREATH,
        WAVEMBOO,
        RUSHOOT,


        MAX,
    };

    Nokopy();
    ~Nokopy();

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    //ゲッター関数
    std::vector<Base*> GetObj(void) override;
    //セッター関数
    void SetDamage(int dmg);

    //攻撃パターンの関数ポインタ
    using AttackFunc = void(Nokopy::*)();

private:
    //状態ごとのハンドル番号
    int img_[DRAW::DRAW_MAX];
    DRAW DrawPat_;

    //ボスの描画
    void BossDraw(void);


    //状態ごとの行動
    void Idle(void) override;
    void Move(void) override;
    //攻撃
    void Attack(void) override;
    //攻撃状態管理
    void ChangeStateAttack(ATTACK atc);
    //攻撃の状態ごとの行動
    void UpdateBamBeam(void);
    void UpdateBamBreath(void);
    void UpdateWavemboo(void);
    void UpdateRushoot(void);
    void Damage(void) override;
    void Death(void) override;
  
    ATTACK attackState_;
    //攻撃パターンの関数ポインタをmapで管理
    std::map<ATTACK, AttackFunc> attackUpdateFuncs_;
    //攻撃用カウンター
    int attackCounter_;
    //攻撃用インスタンス
    BamBeam* beam_;
    BamBreath* breath_;
    Rushoot* rush_;
    Wavemboo* wave_;


    void IsGround(Collision::DIR dir) override;
};