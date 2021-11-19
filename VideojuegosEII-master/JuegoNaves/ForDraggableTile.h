#pragma once

#include "Tile.h"
class ForDraggableTile : public Tile
{
public:
	ForDraggableTile(string fileName, float x, float y, Type t, Game* game);
	Type type;
};

