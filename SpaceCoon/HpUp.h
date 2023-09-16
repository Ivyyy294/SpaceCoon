#pragma once
#include "GameObject.h"

using namespace LarasEngine;

class HpUp
	: public GameObject
{
public:
	HpUp(const int xPos);

	void Update () override;
	virtual size_t GetLayerId() const override { return LarasEngine::LAYER_OBJECT2; };
	void HandleCrash(LarasEngine::GameObject* obj);
};

