#pragma once
#include"UiBase.h"
class UiTitle : public UiBase
{
public:
    UiTitle();
    virtual ~UiTitle();

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
    void Load(void) override;
    void SetParam(void) override;
private:

};

