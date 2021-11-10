#pragma once

#include "Tile.h"
class MovableTile : public Actor
{
public:
	float vxIntelligence;
	float vx;
	MovableTile( float x, float y, Game* game);
	void update();
};

