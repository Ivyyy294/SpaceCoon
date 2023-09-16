#include "stdafx.h"
#include "StaticField.h"
#include "TimeInfo.h"

StaticField::StaticField (GameObject* _parent)
	: GameObject (0, 0, TYPID_STATIC)
	, internalCounter (0.f)
	, draw (true)
	, parent (_parent)
{
}

void StaticField::Draw (QPainter* painter)
{
	if (draw)
		GameObject::Draw (painter);
}

void StaticField::Update ()
{
	if (internalCounter >= 20.f)
	{
		internalCounter = 0.f;
		draw = !draw;
	}
	else
		internalCounter += LarasEngine::TimeInfo::Me ().GetFactor ();

	if (parent->DeleteMe () || parent->GetHitPoints() <= 0)
		deleteMe = true;
}
