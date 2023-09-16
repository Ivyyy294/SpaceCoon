#include "stdafx.h"
#include "DefaultLevel.h"
#include "GameObject.h"
#include "GlobalGameValues.h"
#include "SpawnMeteorit.h"
#include "SpawnBoss.h"
#include "SpawnEnemy.h"
#include "SpawnHealthBubble.h"
#include "SpawnShieldUp.h"
#include "Input.h"
#include "BackgroundObject.h"
#include "ScoreList.h"
#include "InputDialog.h"
#include "DebugInfoObject.h"

using namespace LarasEngine;

DefaultLevel::DefaultLevel()
	: Level (LEVELID_NORMAL)
{
	LE_OH.RegisterCreateFuncObjects (TYPID_SCORE_LIST, ScoreList::CreateMethod);
	LE_OH.RegisterCreateFuncObjects (TYPID_DEBUG_INFO, DebugInfoObject::CreateMethod);
}

void DefaultLevel::Start()
{
	LE_OH.reset();

	GlobalGameValues::Me().playerHealth = 0;
	GlobalGameValues::Me().scorePoints = 0;
	GlobalGameValues::Me().showHUDDmgIndicator = false;

	LE_OH.SetTargetFPS (60);

	//Add Background
	LE_ADD_O (new Background(Qt::black));

	//Add Player
	player = static_cast <ShipPlayer*> (LE_ADD_O (TYPID_PLAYER));
	GlobalGameValues::Me().playerHealth = player->GetHitPoints();

	//Add HUD
	LE_ADD_O (TYPID_HUD);

	//LE_ADD_O (TYPID_BOSS);
	LE_ADD_E(new SpawnHealthBubble(450));
	LE_ADD_E(new SpawnShieldUp(325));
	LE_ADD_E (new SpawnMeteorit());
	LE_ADD_E(new SpawnEnemy(300));
	LE_ADD_E(new SpawnBoss (1000));

#ifdef _DEBUG
	GameObject* debugInfo = LE_ADD_O (TYPID_DEBUG_INFO);
	debugInfo->Translate (QPointF (8, 160));
#endif // _DEBUG

	LE_OH.PlaySound ("BGM", 0.5f, QSoundEffect::Infinite);
}

void DefaultLevel::ProcessInput ()
{
	if (Input::Me ().TestKey (Input::Key::Key_R))
	{
		if (LE_OH.GetGameStatus () == GameStatus::STATUS_PAUSE)
			LE_OH.SetGameStatus (GameStatus::STATUS_GAME);

		Input::Me ().ResetPlayerInput ();
		Start ();
	}
	else if (Input::Me ().TestKey (Input::Key::Key_Escape))
	{
		LE_OH.StopSound ("BGM");
		LE_OH.SetGameStatus(GameStatus::STATUS_MENUE);
	}
	else if (Input::Me ().TestKey (Input::Key::Key_P))
	{
		Input::Me ().ResetPlayerInput();

		if (LE_OH.GetGameStatus () == GameStatus::STATUS_PAUSE)
			LE_OH.SetGameStatus (GameStatus::STATUS_GAME);
		else
			LE_OH.SetGameStatus (GameStatus::STATUS_PAUSE);
	}
}

void DefaultLevel::DoPostWork()
{
	if (player->DeleteMe())
	{
		ScoreList* list = static_cast <ScoreList*> (LE_ADD_O (TYPID_SCORE_LIST));
		list->AddNewScore (GlobalGameValues::Me ().scorePoints, LarasEngine::InputDialog::GetInput ("ENTER NAME:"));
		LE_OH.SetGameStatus(GameStatus::STATUS_PAUSE);
		return;
	}
	else
	{
		if (GlobalGameValues::Me ().scorePoints <= 1250)
			GlobalGameValues::Me().difficulty = GlobalGameValues::Me().scorePoints / 250;
	}
}
