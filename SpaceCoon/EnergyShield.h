#pragma once
#include "GameObject.h"
#include "GlobalGameValues.h"
#include "ShieldBurst.h"

class EnergyShield :
    public LarasEngine::GameObject
{
public:
    EnergyShield(int hitPoints, double _scale = 1.0);

    void Draw(QPainter* painter) override;
    void Update () override;
    void HandleCrash(GameObject* obj);
    
    inline size_t GetMaxHp() const { return maxHp; };
	 inline bool IsShieldBurstActive () const { return shieldBurst->GetActive (); };
	 void ShieldBurst ();
protected:
	virtual void ReadJson (const QJsonObject& json) override;
private:
    size_t maxHp;
	 //float timer{ 0.f };
	 //size_t shieldBurstCost{ 0 };
	 LarasEngine::ShieldBurst* shieldBurst{nullptr};
	 //size_t oWidth;
};

