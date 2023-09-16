#include "stdafx.h"
#include "ScoreList.h"
#include <qjsonarray.h>

ScoreList::ScoreList ()
	: GameObject (0, 0, TYPID_SCORE_LIST, false)
{
	MoveCenter (QPoint (screenW / 2, screenH / 2));
	font = QApplication::font ();

	LoadScoreList ();
}


void ScoreList::Draw(QPainter* painter)
{
	GameObject::Draw(painter);

	painter->save();

	painter->setFont(font);
	painter->setPen(pen);

	std::string text = "Highscore:\n\n";

	size_t count = 0;

	for (const auto& i : scoreVec)
	{
		text += std::to_string (i.points) + " : " + i.name + "\n";

		if (++count >= maxAnz)
			break;
	}

	painter->drawText(GetImageRect(), Qt::AlignLeft, text.c_str());

	painter->restore();
}

QJsonObject ScoreList::GetAsJsonObject () const
{
	QJsonObject object;
	QJsonArray array;

	for (const auto& i : scoreVec)
	{
		QJsonObject o;
		o.insert ("Score", int (i.points));
		o.insert ("Name", i.name.c_str ());
		array.append (o);
	}

	object.insert ("scorelist", array);

	return object;
}

void ScoreList::AddNewScore (size_t score, const std::string& name)
{
	if (!name.empty ())
	{
		Score tmp {score, name};
		scoreVec.push_back (tmp);
		Sort ();
		SaveToJson ("./JSON/savegame.json");
	}
}

void ScoreList::LoadScoreList ()
{
	LoadJson ("./JSON/savegame.json");
}

void ScoreList::SaveScoreList ()
{
}

void ScoreList::ReadJson(const QJsonObject& json)
{
	if (json.contains ("fontcolor"))
	{
		QJsonArray colorArray = json["fontcolor"].toArray ();
		pen.setColor (QColor (colorArray[0].toInt (), colorArray[1].toInt (), colorArray[2].toInt (), colorArray[3].toInt ()));
	}

	if (json.contains ("fontsize"))
		font.setPointSize (json["fontsize"].toInt ());

	if (json.contains ("maxanz"))
		maxAnz =  json["maxanz"].toInt ();

	if (json.contains("scorelist") && json["scorelist"].isArray())
	{
		for (const auto& i : json["scorelist"].toArray ())
		{
			QJsonObject o = i.toObject ();
			Score score{ o["Score"].toInt (), o["Name"].toString ().toLatin1 () };
			scoreVec.push_back (score);
		}

		Sort ();
	}

	if (json.contains ("size") && json["size"].isArray ())
	{
		QJsonArray size = json["size"].toArray ();
		SetRectWidth (size[0].toInt ());
		SetRectHeight (size[1].toInt ());
		MoveCenter (QPointF(screenW / 2, screenH / 2));
	}

	if (json.contains ("positionOffset") && json["positionOffset"].isArray ())
	{
		QJsonArray pos = json["positionOffset"].toArray ();
		Translate (QPointF (pos[0].toInt (), pos[1].toInt ()));
	}
}

void ScoreList::Sort ()
{
	std::sort (scoreVec.begin (), scoreVec.end ());
}
