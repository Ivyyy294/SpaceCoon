#pragma once
#include "GameObject.h"
#include "ShipPlayer.h"

class HUDDmgIndicator
	: public LarasEngine::GameObject
{
public:
	HUDDmgIndicator();
	virtual void Draw (QPainter* painter) override;
	virtual void Update () override;
	virtual size_t GetLayerId () const override { return LarasEngine::LAYER_HUD; };
private:
	double frameCount;
	double lifeTime;
	bool red;
	bool playAlert;
};

class HudShieldBar
	: public LarasEngine::GameObject
{
public:
	HudShieldBar (const int x, const int y);
	virtual void Draw(QPainter* painter) override;
	virtual void Update () override;
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_HUD; };

	typedef std::shared_ptr <HudShieldBar> Ptr;
private:
	SimpleGraphicObject shieldBarBody;
	SimpleGraphicObject shieldBarEnd;
	ShipPlayer* player;
	size_t originalShieldBarWidhth;
	float shieldIntegrity;
};


class HudHealthPoint
	: public LarasEngine::SimpleGraphicObject
{
public:
	HudHealthPoint(const int xPos, const int yPos);
};

class HudTopHpWarning
	: public LarasEngine::GameObject
{
public:
	HudTopHpWarning ();
	virtual size_t GetLayerId () const override { return LarasEngine::LAYER_HUD; };
	virtual void Draw (QPainter* painter) override;
	virtual void Update () override;
	inline void SetFlashSpeed (const size_t _flashSPeed) { flashSpeed = _flashSPeed; };
private:
	double lifetime;
	bool visible;
	size_t flashSpeed;
};

class HudTop
	: public LarasEngine::GameObject
{
public:
	HudTop();
	virtual void Draw(QPainter* painter) override;
	virtual void Update () override;
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_HUD; };
protected:
	void ReadJson (const QJsonObject& json) override;
	void DrawHpWarning ();
	std::vector <HudHealthPoint> hpVec;
	void UpdateHealthbar();
	int xPosHealthBar;
	int yPosHealthBar;
	int paddingHealthBar;
	HudTopHpWarning hpWarning;
	HudShieldBar::Ptr shieldBar;
};

class HudBottom
	: public LarasEngine::GameObject
{
public:
	HudBottom();
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_HUD; };
	virtual void Draw(QPainter* painter) override;
	virtual void Update () override {};
protected:
	void ReadJson (const QJsonObject& json) override;
private:
	LarasEngine::SimpleTextObject scoreText;
	QColor fontColor;

	void drawScore(QPainter* painter);
};

class HUD
	: public LarasEngine::GameObject
{
public:
	HUD();

	virtual void Draw(QPainter* painter) override;
	virtual void Update () override;
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_HUD; };

	static GameObject* CreateMethod () { return new HUD; };
protected:
	void ReadJson (const QJsonObject& json) override;

private:
	LarasEngine::SimpleTextObject lostText;
	HUDDmgIndicator hudDmgIndicator;
	QColor fontColor;
	HudTop hudTop;
	HudBottom hudBottom;
};


