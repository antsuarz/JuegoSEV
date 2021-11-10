#include "MovableTile.h"

MovableTile::MovableTile(float x, float y, Game* game)
	: Actor("res/bloque_metal.png", x, y,40,32, game) {
	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;
}

void MovableTile::update() {
	if (vx == 0) {
		vxIntelligence = vxIntelligence * -1;
		vx = vxIntelligence;
	}
	x = x + vx;
	vy = -1;
}

