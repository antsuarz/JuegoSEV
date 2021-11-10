#include "Puerta.h"

Puerta::Puerta(string fichero, int iden, float x, float y, Game* game) :Actor(fichero, x, y, 22, 35, game) {
	ident = iden;
}
