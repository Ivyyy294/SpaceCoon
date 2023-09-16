#include "stdafx.h"
#include "HUD.h"
#include <qstatictext.h>
#include <qjsonarray.h>

using namespace LarasEngine;

HUD::HUD()
	: GameObject (0, 0, TYPID_HUD)
	, lostText (TYPID_TEXT_LOST)
	, hudTop()
{
}

void HUD::Draw(QPainter* painter)
{
	SimpleGraphicObject::Draw(painter);

	if (GlobalGameValues::Me().showHUDDmgIndicator)
		hudDmgIndicator.Draw(painter);

	if (GlobalGameValues::Me().playerHealth <= 0)
		lostText.Draw(painter);

	hudTop.Draw(painter);
	hudBottom.Draw(painter);
}

void HUD::Update ()
{
	hudTop.Update();
	hudDmgIndicator.Update ();
}

void HUD::ReadJson (const QJsonObject& json)
{
	if (json.contains("fontcolor"))
	{
		QJsonArray colorArray = json["fontcolor"].toArray();
		fontColor = QColor (colorArray[0].toInt(), colorArray[1].toInt(), colorArray[2].toInt(), colorArray[3].toInt());
	}

	lostText.SetText("You Lost!");

	//Init Font
	QFont font = QApplication::font();
	font.setPointSize(json["lostfontsize"].toInt());
	lostText.SetFont(font);

	//Init Pen
	lostText.SetPen(QPen(fontColor));

	QSizeF size = lostText.GetSize();
	lostText.SetPosition((screenW - size.width()) / 2, screenH / 2 - size.height());
}

HudTop::HudTop()
	: GameObject (0, 0, TYPID_HUD_TOP)
	, shieldBar (nullptr)
	, hpWarning ()
{
	LoadJson();
	UpdateHealthbar();
}

void HudTop::Draw(QPainter* painter)
{
	UpdateHealthbar();

	GameObject::Draw(painter);

	for (char i = 0; i < GlobalGameValues::Me().playerHealth; ++i)
		hpVec.at(i).Draw(painter);

	if (shieldBar != nullptr)
		shieldBar->Draw (painter);

	if (GlobalGameValues::Me ().playerHealth <= 1)
		hpWarning.Draw (painter);
}

void HudTop::Update ()
{
	UpdateHealthbar();

	if (shieldBar != nullptr)
		shieldBar->Update();

	if (GlobalGameValues::Me ().playerHealth <= 1)
		hpWarning.Update ();
}

void HudTop::ReadJson (const QJsonObject& json)
{
	if (json.contains("position"))
	{
		QJsonArray posArray = json["position"].toArray();
		SetPosition(posArray[0].toInt(), posArray[1].toInt());
		hpWarning.MoveCenter (GetCenter());
	}

	if (json.contains ("hpWarningFlashSPeed"))
		hpWarning.SetFlashSpeed (json["hpWarningFlashSPeed"].toInt ());

	if (json.contains("positionHealthBar"))
	{
		QJsonArray posArray = json["positionHealthBar"].toArray();
		xPosHealthBar = posArray[0].toInt();
		yPosHealthBar= posArray[1].toInt();
	}

	paddingHealthBar = json["paddingHealthBar"].toInt();

	if (json.contains("positionShield"))
	{
		QJsonArray posArray = json["positionShield"].toArray();
		int xPosShieldBar = posArray[0].toInt();
		int yPosShieldBar = posArray[1].toInt();
		shieldBar.reset(new HudShieldBar(xPosShieldBar, yPosShieldBar));
	}
}

void HudTop::DrawHpWarning ()
{

}

void HudTop::UpdateHealthbar()
{
	for (char i = hpVec.size(); i < GlobalGameValues::Me().playerHealth; ++i)
		hpVec.push_back(HudHealthPoint(xPosHealthBar + paddingHealthBar * i, yPosHealthBar));
}

HUDDmgIndicator::HUDDmgIndicator()
	: GameObject(0, 0, TYPID_HUD_HIT)
	, frameCount (0.0)
	, lifeTime (0.0)
	, red (true)
	, playAlert (true)
{
}

void HUDDmgIndicator::Draw (QPainter* painter)
{
	if (red)
		GameObject::Draw (painter);
}

void HUDDmgIndicator::Update ()
{
	if (GlobalGameValues::Me ().showHUDDmgIndicator)
	{
		if (playAlert)
		{
			LE_OH.PlaySound ("ALERT", 1.0f, 2);
			playAlert = false;
		}

		double lag = TimeInfo::Me().GetFactor ();
		frameCount += lag;
		lifeTime += lag;

		if (frameCount >= 20.f)
		{
			red = !red;
			frameCount = 0.f;
		}

		if (lifeTime >= 120.0)
		{
			GlobalGameValues::Me ().showHUDDmgIndicator = false;
			frameCount = 0.f;
			lifeTime = 0.f;
			playAlert = true;

			ShipPlayer* player = static_cast <ShipPlayer*> (LE_OH.GetObjectVec (TYPID_PLAYER).at (0).get ());
		}
	}
}

HudBottom::HudBottom()
	: GameObject (0, 0, TYPID_HUD_BOTTOM)
	, scoreText(TYPID_TEXT_SCORE)
{
	LoadJson();
}

void HudBottom::ReadJson (const QJsonObject& json)
{
	if (json.contains("position"))
	{
		QJsonArray posArray = json["position"].toArray();
		SetPosition(posArray[0].toInt(), posArray[1].toInt());
	}

	if (json.contains("fontcolor"))
	{
		QJsonArray colorArray = json["fontcolor"].toArray();
		fontColor = QColor(colorArray[0].toInt(), colorArray[1].toInt(), colorArray[2].toInt(), colorArray[3].toInt());
	}

	QFont font = QApplication::font();
	font.setBold(true);

	if (json.contains ("scorefontsize"))
		font.setPointSize(json["scorefontsize"].toInt ());

	scoreText.SetFont(font);

	if (json.contains("scorefontposition"))
	{
		QJsonArray posArray = json["scorefontposition"].toArray();
		scoreText.SetPosition(posArray[0].toInt(), posArray[1].toInt());
	}

	scoreText.SetPen(QPen(fontColor));
}

void HudBottom::Draw(QPainter* painter)
{
	GameObject::Draw(painter);
	drawScore(painter);
}

void HudBottom::drawScore(QPainter* painter)
{
	size_t score = GlobalGameValues::Me().scorePoints;
	scoreText.SetText("Score: " + QString(std::to_string(score).c_str()));
	scoreText.Draw(painter);
}

HudShieldBar::HudShieldBar(const int x, const int y)
	: GameObject (x, y, TYPID_SHIELD_BAR)
	, shieldBarBody (0, 0, TYPID_SHIELD_BAR_2)
	, shieldBarEnd (0, 0, TYPID_SHIELD_BAR_3)
	, shieldIntegrity (1.f)
{
	shieldBarBody.SetPosition(QPointF(GetImageRect().topRight().x(), y));
	shieldBarEnd.SetPosition(QPointF(shieldBarBody.GetImageRect ().topRight().x(), y));

	player = static_cast <ShipPlayer*> (LE_OH.GetObjectVec(TYPID_PLAYER).at(0).get());

	originalShieldBarWidhth = shieldBarBody.GetImageRect ().width();
}

void HudShieldBar::Draw(QPainter* painter)
{
	static size_t frameCount = 0;
	static bool on = true;

	//if (shieldIntegrity >= 0.5f)
	//	on = true;
	//else if (shieldIntegrity < 0.5f && shieldIntegrity > 0.f)
	//{
	//	if (frameCount % 25 == 0)
	//		on = !on;
	//}
	if (shieldIntegrity <= 0.f)
		on = false;
	else
		on = true;

	if (on)
	{
		GameObject::Draw(painter);
		shieldBarBody.Draw(painter);
		shieldBarEnd.Draw(painter);
	}

	frameCount++;
}

void HudShieldBar::Update ()
{
	shieldIntegrity = player->GetShieldIntegrity();
	QRectF rect = GetImageRect ();

	if (shieldIntegrity > 0.f)
	{
		shieldBarBody.SetRectWidth (std::ceil (originalShieldBarWidhth * shieldIntegrity));
		shieldBarEnd.SetPosition(QPointF(shieldBarBody.GetImageRect ().topRight().x(), rect.y()));
	}
	else
		shieldBarEnd.SetPosition(QPointF(rect.topRight().x(), rect.y()));
}

HudHealthPoint::HudHealthPoint(const int xPos, const int yPos)
	: SimpleGraphicObject(xPos, yPos, TYPID_HP)
{
}

HudTopHpWarning::HudTopHpWarning ()
	: GameObject (0,0, TYPID_HUD_HP_WARNING)
	, visible (true)
	, flashSpeed (0)
	, lifetime (0.0)
{
}

void HudTopHpWarning::Draw (QPainter* painter)
{
	if (visible)
		GameObject::Draw (painter);
}

void HudTopHpWarning::Update ()
{
	lifetime += TimeInfo::Me ().GetFactor ();

	if (lifetime >= flashSpeed)
	{
		lifetime = 0.0;
		visible = !visible;
	}
}
