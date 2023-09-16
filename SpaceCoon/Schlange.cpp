#include "Schlange.h"


Schlange::Schlange(void)
{
	Reset();
}


Schlange::~Schlange(void)
{
}

void Schlange::InsertNew (int xPos, int yPos)
{
	schlange.push_back (Image (xPos, yPos, ":/Images/snake.png"));
}

void Schlange::DrawSnake(QPainter* painter)
{
	for (auto i: schlange)
	{
		painter->drawImage (i.GetRect(), i.GetImage());
	}
}

void Schlange::AddSnake ()
{
	QRect rect = GetLastRect();

	switch (status)
	{
	case oben:
		{
			InsertNew (rect.x(), rect.y()+20);
			break;
		}
	case unten:
		{
			InsertNew (rect.x(), rect.y()-20);
			break;
		}
	case links:
		{
			InsertNew (rect.x()+20, rect.y());
			break;
		}
	case rechts:
		{
			InsertNew (rect.x()-20, rect.y());
			break;
		}

	}	
}

void Schlange::autoMove()
{
	int xMod = 0;
	int yMod = 0;
	int angelMod;

	switch (status)
	{
	case oben:
		{
			yMod = -20;
			break;
		}
	case unten:
		{
			yMod = 20;
			break;
		}
	case links:
		{
			xMod = -20;
			break;
		}
	case rechts:
		{
			xMod = 20;
			break;
		}

	}
	for (int i = schlange.size()-1; i > 0; i--)
	{
		QRect rect = schlange[i-1].GetRect();
		schlange[i].SetPosition( rect.x(), rect.y());
	}
	QRect rect = schlange.begin()->GetRect();
	schlange.begin()->SetPosition( rect.x() + xMod, rect.y() + yMod);

	rect = schlange.begin()->GetRect();
	if (rect.x() >= 500)
		schlange.begin()->SetPosition( 0, rect.y());
	if (rect.x() < 0)
		schlange.begin()->SetPosition( 500, rect.y());
	if (rect.y() >= 500)
		schlange.begin()->SetPosition( rect.x(), 0);
	if (rect.y() < 0)
		schlange.begin()->SetPosition( rect.x(), 500);
}

void Schlange::SetStatus (int _status)
{
	status = _status;
}

QRect Schlange::GetFirstRect ()
{
	return schlange.begin()->GetRect();
}
QRect Schlange::GetLastRect ()
{
	std::vector<Image>::iterator iter = schlange.end();
	iter--;
	return iter->GetRect();
}

bool Schlange::CheckAufGebissen()
{
	std::vector<Image>::iterator iter = schlange.begin();
	for (iter++; iter != schlange.end(); iter++)
	{
		if (iter->GetRect() == GetFirstRect())
		{
			return true;
		}
	}
	return false;
}

bool Schlange::CheckAufKonflikt (int xPos, int yPos)
{
	std::vector<Image>::iterator iter = schlange.begin();
	for (iter++; iter != schlange.end(); iter++)
	{
		if (xPos == iter->GetRect().x() && yPos == iter->GetRect().y())
		{
			return true;
		}
	}
	return false;
}

void Schlange::Reset()
{
	schlange.clear();
	InsertNew (20, 20);
	AddSnake();
	status = rechts;
}