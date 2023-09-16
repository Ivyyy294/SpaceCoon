#include "stdafx.h"
#include "SpawnHealthBubble.h"
#include "HpUp.h"

SpawnHealthBubble::SpawnHealthBubble (size_t t)
	: trigger (t)
	, last (0)
	, player (nullptr)
{
	GameObject::Vec& playerVec = LE_OH.GetObjectVec (TYPID_PLAYER);

	if (!playerVec.empty())
		player = static_cast <ShipPlayer*> (LE_OH.GetObjectVec (TYPID_PLAYER).at (0).get ());
}

bool SpawnHealthBubble::CheckCondition()
{
	if (!LE_OH.GetObjectVec (TYPID_HP_UP).empty ())
		return false;

	if (player != nullptr && player->GetHitPoints() < player->GetMaxHitPoints())
	{
		size_t tmp = std::floor (GlobalGameValues::Me().scorePoints / trigger);

		if (last < tmp)
		{
			last = tmp;
			return true;
		}
	}

	return false;
}

void SpawnHealthBubble::Run()
{
		int wDesktop = LE_OH.GetPrimaryScreenGeometry ().width();
		int margin = wDesktop / 8;
		int xPos = margin + rand() % (wDesktop - margin * 2);

		LE_ADD_O(new HpUp(xPos));
}

