#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/Assets/bolaFuego.gif", x, y, 20, 20, game) {
	vx = 9;
	vy = -1;  
}

void Projectile::update() {
	vy = vy - 1;   
}
