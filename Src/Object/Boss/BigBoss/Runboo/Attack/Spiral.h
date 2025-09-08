#include <DxLib.h>
#include <vector>
#include "../../../Tutorial/Attack/AttackBase.h"
#include"../../../../../Application.h"


class Spiral : public AttackBase
{
public:
    static constexpr int BULLET_NUM = 20;      // 1âÒÇÃîgÇÃíeêî
    static constexpr float BULLET_SPEED = 5.0f;
    static constexpr float SIZE_X = 32.0f;
    static constexpr float SIZE_Y = 32.0f;

    static constexpr int IMAGE_NUM = 8;
    static constexpr float IMAGE_BIG_RATE = 2.0f;

    Spiral(float moveSpeed);
    ~Spiral();

    void Init(const Vector2F* pos) override;
    void Update(Vector2F boss);
    void Update() override {}
    void Draw() override;
    void Release() override;

    const std::vector<Base> Get() const override;

    void Hit(int i);

    bool End() { return false; } // èÌÇ… falseÅAïKóvÇ…âûÇ∂Çƒägí£
    void SetIsAlive(bool isAlive);

private:
    std::vector<Base> obj_;
    Vector2F startPos_;
    float angleOffset_;
    int imageArray_[IMAGE_NUM];
    int arrayIndex_;
    int shootTimer_;
    int fireCount_;

    void ChangeDispPos() override;
};