#pragma once

#include <vector>
#include "Image.h"


enum moveStatus
{
	oben,
	unten,
	rechts,
	links
};

class Schlange
{
public:
	Schlange(void);
	~Schlange(void);
		
	void DrawSnake(QPainter* painter);
	void AddSnake ();
	void autoMove();
	void SetStatus (int _status);
	QRect GetFirstRect ();
	QRect GetLastRect ();
	bool CheckAufGebissen();
	bool CheckAufKonflikt (int xPos, int yPos);
	std::vector <Image> schlange;
	void Reset();
private:
	
	void InsertNew (int xPos, int yPos);
	int status;	
};

