#include "stdafx.h"
#include "HardcoreLevel.h"
#include "ScoreList.h"
#include "InputDialog.h"

HardcoreLevel::HardcoreLevel ()
{
}

void HardcoreLevel::Start ()
{
	DefaultLevel::Start ();
	LE_OH.SetTargetFPS (90);
}

void HardcoreLevel::DoPostWork ()
{
	if (player->DeleteMe ())
	{
		ScoreList* list = static_cast <ScoreList*> (LE_ADD_O (TYPID_SCORE_LIST));
		list->AddNewScore (GlobalGameValues::Me ().scorePoints, LarasEngine::InputDialog::GetInput ("ENTER NAME:") + " [HC]");
		LE_OH.SetGameStatus (GameStatus::STATUS_PAUSE);
		return;
	}
	else
	{
		if (GlobalGameValues::Me ().scorePoints <= 1000)
			GlobalGameValues::Me ().difficulty = GlobalGameValues::Me ().scorePoints / 250;
	}
}

