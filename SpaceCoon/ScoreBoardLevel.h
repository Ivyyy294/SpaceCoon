#pragma once

#include "Level.h"

using namespace LarasEngine;

class ScoreBoardLevel
	: public Level
{
public: 
	ScoreBoardLevel ();

	void Start () override;
	void ProcessInput () override;
	void DoPostWork () override;

	virtual LevelId GetLevelId () const override { return LEVELID_SCORE; };

	static Level* CreateMethod () { return new ScoreBoardLevel; };
};

