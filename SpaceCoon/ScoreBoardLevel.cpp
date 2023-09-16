#include "stdafx.h"
#include "ScoreBoardLevel.h"
#include "ScoreList.h"
#include "Input.h"
#include "BackgroundObject.h"
#include "InputDialog.h"

ScoreBoardLevel::ScoreBoardLevel ()
	: Level (LEVELID_SCORE)
{
}

void ScoreBoardLevel::Start ()
{
	LE_OH.reset ();
	LE_OH.SetTargetFPS (30);

	LE_OH.RegisterCreateFuncObjects (TYPID_SCORE_LIST, ScoreList::CreateMethod);
	
	LE_ADD_O (new Background (Qt::black));
	LE_ADD_O (TYPID_SCORE_LIST);
}

void ScoreBoardLevel::ProcessInput ()
{
	if (Input::Me ().TestKey (Input::Key::Key_Escape))
		LE_OH.SetGameStatus (GameStatus::STATUS_MENUE);
}

void ScoreBoardLevel::DoPostWork ()
{
}
