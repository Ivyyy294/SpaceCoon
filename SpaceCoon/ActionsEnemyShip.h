#pragma once

#include "EnemyShip.h"
#include "Input.h"

class ActionShootPlayer
	: public AIAction
{
public:
	ActionShootPlayer (EnemyShip* _ship);

	virtual void Run (double lag) override;
	virtual bool Check () override;
protected:
	EnemyShip* ship;
};

class ActionShipEntrance
	: public AIPrimaryAction
{
public:
	ActionShipEntrance (GameObject* _object);

	virtual void Run (double lag) override;
	virtual bool Check () override;
protected:
	char frameNr;
	GameObject* object;
};

class ActionShipEvade
	: public AIPrimaryAction
{
public:
	ActionShipEvade (GameObject* _object);

	virtual void Run (double lag) override;
	virtual bool Check () override;
protected:

	struct CollisionInfo
	{
		double r;
		QPointF center;
		double dist;
		typedef std::vector <CollisionInfo> Vec;
	};

	char frameNr;
	GameObject* object;
	QPointF objectCenter;
	double r1;
	CollisionInfo::Vec collisionObjects;
	LarasEngine::Input::Key currentInput;

private:
	bool IsCollisionPossible (const GameObject& o, CollisionInfo& collision) const;
	double GetRadiusToRectF (const QRectF& rect) const;
};

