#include "stdafx.h"
#include "IntroLevel.h"
#include "Input.h"
#include "IntroDialog.h"
#include "BackgroundObject.h"

IntroLevel::IntroLevel()
	: Level ("Intro")
{
}

void IntroLevel::Start()
{
	LE_OH.reset();
	GlobalGameValues::Me().scorePoints = 0;
	GlobalGameValues::Me().playerHealth = 0;
	GlobalGameValues::Me().showHUDDmgIndicator = false;

	LE_OH.SetTargetFPS (60);

	//Add Background
	LE_ADD_O(new Background (Qt::black));
	
	//Add Dialog
	LE_ADD_O(new IntroDialog);
}

void IntroLevel::ProcessInput()
{
	if (Input::Me ().TestKey (Input::Key::Key_Escape))
		LE_OH.SetGameStatus(GameStatus::STATUS_EXIT);
}
