#include "stdafx.h"
#include "Menue.h"
#include <qpixmap.h>

using namespace LarasEngine;

Menue::Menue(QWidget *parent)
	: QDialog(parent)
	, exitCode (GameStatus::STATUS_EXIT)
{
	ui.setupUi(this);

	QPixmap bkgnd(":/Images/Menue.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
}

void Menue::on_pushButtonExit_pressed()
{
	done (GameStatus::STATUS_EXIT);
}

void Menue::on_pushButtonSinglePlayer_pressed()
{
	LE_OH.SetActiveLevel (LEVELID_NORMAL);
	done(GameStatus::STATUS_GAME);
}

void Menue::on_pushButtonTwoPlayers_pressed()
{
	LE_OH.SetActiveLevel (LEVELID_HARDCORE);
	done(GameStatus::STATUS_GAME);
}

void Menue::on_pushButtonScore_pressed ()
{
	LE_OH.SetActiveLevel (LEVELID_SCORE);
	done (GameStatus::STATUS_GAME);
}
