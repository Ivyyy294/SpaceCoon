#include "stdafx.h"
#include "Menue.h"
#include "DefaultLevel.h"
#include "IntroLevel.h"
#include "HardcoreLevel.h"
#include "ScoreBoardLevel.h"
#include "ShieldBurst.h"

void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;  

  const QRect& screenGeo = LE_OH.GetPrimaryScreenGeometry ();

  screenWidth = screenGeo.width();
  screenHeight = screenGeo.height();
  int WIDTH = screenWidth;
  int HEIGHT = screenHeight;
 
  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.setGeometry(x, y, WIDTH, HEIGHT);
  widget.setFixedSize(WIDTH, HEIGHT);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setWindowIcon (QIcon (QPixmap(":/Images/Space Coon Logo2.png")));
	int mode = 0;

	LE_OH.RegisterCreateFuncLevels (LEVELID_NORMAL, DefaultLevel::CreateMethod);
	LE_OH.RegisterCreateFuncLevels (LEVELID_SCORE, ScoreBoardLevel::CreateMethod);
	LE_OH.RegisterCreateFuncLevels (LEVELID_HARDCORE, HardcoreLevel::CreateMethod);

	LE_OH.RegisterCreateFuncObjects (TYPID_PLAYER, ShipPlayer::CreateMethod);
	LE_OH.RegisterCreateFuncObjects (TYPID_HUD, HUD::CreateMethod);
	LE_OH.RegisterCreateFuncObjects (TYPID_SHIELD_BURST, ShieldBurst::CreateMethod);

	Menue m;
	LarasEngine::Core engine;
	LE_OH.SetMaxFPS (120);
	LE_OH.SetTargetFPS (60);
	engine.SetMenueDialog(&m);
	engine.SetGameStatus(GameStatus::STATUS_MENUE);

	engine.Run();

	return 0;
}
