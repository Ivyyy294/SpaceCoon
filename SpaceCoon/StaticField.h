#pragma once
#include "GameObject.h"

class StaticField :
	public LarasEngine::GameObject
{
public:
	StaticField (GameObject* _parent);
	virtual void Draw (QPainter* painter) override;
	virtual void Update () override;

	inline void SetDeleteMe () { deleteMe = true; };
protected:
	double internalCounter;
	bool draw;
	GameObject* parent;
};

