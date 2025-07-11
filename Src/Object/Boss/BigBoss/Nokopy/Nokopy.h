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
    static constexpr float SPAWN_POS_Y = 300;
    static constexpr float SPAWN_POS_RIGHT = 1150;
    static constexpr float SPAWN_POS_LEFT = 150;

    enum  DRAW
    {
        DRAW_IDLE,
        DRAW_MOVE,
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
    std::vector<Base> GetObj(void) override;
    AttackBase* GetAttackIns(void)override;
    //セッター関数
    void SetDamage(int dmg)override;
    void ObjHit(int i)override;

    //攻撃パターンの関数ポインタ
    using AttackFunc = void(Nokopy::*)();


private:
    //状態ごとのハンドル番号
    int img_[DRAW::DRAW_MAX];
    DRAW DrawPat_;

    //ボスの描画
    void BossDraw(void);


    //状態ごとの行動
    //通常状態-------------------------------------------------------------------
    void Idle(void) override;
    int idleCounter_;
    //-------------------------------------------------------------------

    //移動--------------------------------------------------------
    void Move(void) override;
    int moveCounter_;
    AsoUtility::DIRECTION dir_;         //向いている向き
    //------------------------------------------------------------

    //攻撃-------------------------------------------------------
    void Attack(void) override;
    //攻撃状態管理
    void ChangeAttackState(ATTACK atc);
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
    //ターゲット座標
    Vector2F targetPos_;
    //突進用カウンターフラグ
    bool isRushReflection_;
    //攻撃用インスタンス
    BamBeam* beam_;
    BamBreath* breath_;
    Rushoot* rush_;
    Wavemboo* wave_;
    //---------------------------------------------------------------

    bool isDive_;       //潜っているか
    void IsGround(Collision::DIR dir) override;
};