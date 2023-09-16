#pragma once
#include "GameObject.h"

class Explosion
	: public LarasEngine::GameObject
{
public:
	void Update () override;
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_OBJECT2; };
	typedef std::vector <Explosion> Vec;

	static void SpawnExplosion(int x, int y);
	static void SpawnExplosion2 (const QRectF& r);
	static void SpawnExplosion2 (const QPointF& p);

private:
	Explosion(int x, int y);
	~Explosion();
	double drawCounter;
	TypId subTyp;
};

