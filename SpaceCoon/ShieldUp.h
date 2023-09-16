#pragma once
#include "GameObject.h"

class ShieldUp :
    public LarasEngine::GameObject
{
public:
    ShieldUp(const int x, const int y);

    void Update () override;
    virtual size_t GetLayerId() const override { return LarasEngine::LAYER_OBJECT2; };
    void HandleCrash(LarasEngine::GameObject* obj);
    void ReadJson (const QJsonObject& json) override;
private:
    int value;
};

