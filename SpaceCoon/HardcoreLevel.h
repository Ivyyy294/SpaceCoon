#pragma once

#include "DefaultLevel.h"

using namespace LarasEngine;

class HardcoreLevel
	: public DefaultLevel
{
public:
	HardcoreLevel ();

	void Start () override;
	virtual LevelId GetLevelId () const override { return LEVELID_HARDCORE; };
	static Level* CreateMethod () { return new HardcoreLevel; };
	void DoPostWork () override;
};

