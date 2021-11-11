#include "Cofre.h"

Cofre::Cofre(float x, float y, Game* g)
	:Actor("res/Assets/cofre.png", x, y, 18, 17, g) {

	aOpening = new Animation("res/Assets/Animacion_AbrirCofre.png", 18, 27,
		90, 23, 15, 5, false, game);
	aClose = new Animation("res/Assets/cofre.png", 18, 20,
		18, 17, 15, 1, false, game);
	aOpen = new Animation("res/Assets/cofre_abierto.png", 18, 27,
		18, 23, 15, 1, false, game);
	animation = aClose;
	open = false;
	hasBeenOpened = false;
}

void Cofre::update() {
	
	if (open && hasBeenOpened == false) {
		animation = aOpening; 
		animation->update(); 
		cont--;
	}
	if (cont == 0)
		hasBeenOpened = true;
	if (hasBeenOpened)
		animation = aOpen;
	
}

void Cofre::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
