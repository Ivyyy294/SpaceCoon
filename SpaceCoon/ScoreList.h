#pragma once
#include "GameObject.h"
#include <functional>

using namespace LarasEngine;

class ScoreList :
    public GameObject
{
public:
	ScoreList();
	virtual void Draw(QPainter* painter) override;
	virtual void Update () override {};
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_HUD; };
	virtual QJsonObject GetAsJsonObject () const override;
	static GameObject* CreateMethod () { return new ScoreList; };

	void AddNewScore (size_t score, const std::string& name);

	void LoadScoreList ();
	void SaveScoreList ();
protected:
	virtual void ReadJson (const QJsonObject& json) override;
	QPen pen;
	QFont font;

private:
	struct Score
	{
		size_t points;
		std::string name;
		typedef std::vector <Score> Vec;
		bool operator< (const Score& val) const { return val.points < points; };
	};

	Score::Vec scoreVec;
	size_t maxAnz;

	void Sort ();
};

