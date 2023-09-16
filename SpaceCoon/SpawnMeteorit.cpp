#include "stdafx.h"
#include "SpawnMeteorit.h"
#include "Meteorit.h"
#include <qjsondocument.h>

using namespace LarasEngine;

SpawnMeteorit::SpawnMeteorit()
{
	std::string jsonFileName = "./JSON/asteroid.json";
	QFile loadFile(jsonFileName.c_str());

	bool ok = loadFile.open(QIODevice::ReadOnly);

	if (ok)
	{
		QByteArray saveData = loadFile.readAll();

		QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

		maxCount = loadDoc.object()["maxcount"].toInt();
	}
}

bool SpawnMeteorit::CheckCondition()
{
	if (LE_OH.GetObjectVec (TYPID_ASTEROID).size() < (maxCount + GlobalGameValues::Me().difficulty))
		return true;

	return false;
}

void SpawnMeteorit::Run()
{
	int r = rand() % 100;

	if (r < 15)
		Meteorit::SpawnMeteorit();
}
