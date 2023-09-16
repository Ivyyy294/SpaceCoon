#pragma once

#include "GameObject.h"

class Meteorit :
	public LarasEngine::GameObject
{
public:
	typedef std::vector<Meteorit> Vec;

	Meteorit (int xPos, int yPos, TypId id);
	~Meteorit(void);
	
	int GetScorePoints() const;
	void SetStartPosition(const int x, const int y);
	void Update () override;
	void HandleCrash(LarasEngine::GameObject* obj);
	static void SpawnMeteorit ();
	inline double GetTrajectory () const { return trajectory; };
private:
	double trajectory;
	int frameCount;
	double offsetRotation;
	int baseHp;
	TypId subTyp;

	void ApplyTrajectory ();
protected:
	void ReadJson (const QJsonObject& json) override;
	void Init() override;
	void SpawnExplosionAtCollision(LarasEngine::GameObject* obj);
};

