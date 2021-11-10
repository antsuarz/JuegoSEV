#include "Recolectable.h"

Recolectable::Recolectable(float x, float y, Game* g)
	:Actor("res/recolectable-idle.png", x, y, 40, 40, g) {

	aShining = new Animation("res/recolectable.png", width, height,
		256, 32, 6, 8, false, game);
	animation = aShining;
}

void Recolectable::update() {
	animation->update();
}

void Recolectable::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
