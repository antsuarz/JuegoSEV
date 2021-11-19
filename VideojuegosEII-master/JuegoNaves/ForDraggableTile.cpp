#include "ForDraggableTile.h"
 

ForDraggableTile::ForDraggableTile(string filename, float x, float y, Type t,Game* game)
	: Tile(filename, x, y, game) {

	type = t;

}