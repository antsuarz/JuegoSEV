#pragma once
#include "Actor.h"
#include "Animation.h"

class Recolectable : public Actor
{
public:
	Recolectable(float x, float y, Game* g);
	void update();
	void draw(float scrollX);
	Animation* aShining;
	Animation* animation;
};

