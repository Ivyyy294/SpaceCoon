#include "stdafx.h"
#include "SpawnShieldUp.h"
#include "ShieldUp.h"

SpawnShieldUp::SpawnShieldUp (size_t t)
	: trigger (t)
	, last (0)
	, player (nullptr)
{
	GameObject::Vec& playerVec = LE_OH.GetObjectVec (TYPID_PLAYER);

	if (!playerVec.empty ())
		player = static_cast <ShipPlayer*> (LE_OH.GetObjectVec (TYPID_PLAYER).at (0).get ());
}

bool SpawnShieldUp::CheckCondition()
{
	if (!LE_OH.GetObjectVec (TYPID_SHIELD_UP).empty ())
		return false;

	if (player != nullptr && player->GetHitPointsShield () < player->GetMaxHitPointsShield ())
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

void SpawnShieldUp::Run()
{
    int wDesktop = LE_OH.GetPrimaryScreenGeometry ().width();
    int margin = wDesktop / 8;
    int xPos = margin + rand() % (wDesktop - margin * 2);

    LE_ADD_O(new ShieldUp(xPos, -100));
}

