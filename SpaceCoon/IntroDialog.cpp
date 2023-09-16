#include "stdafx.h"
#include "IntroDialog.h"
#include "Input.h"

IntroDialog::IntroDialog()
	: Dialog (TYPID_DIALOG_INTRO)
{
}

void IntroDialog::Update ()
{
	Dialog::Update();

	if (indexCurrentText >= textVec.size())
	{
		LE_OH.SetActiveLevel(LEVELID_NORMAL);
	}
}

