#pragma once

#include "Layer.h"
#include "Player.h"
#include "Audio.h" 
#include "Puerta.h"

#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "MovableTile.h"
#include "DraggableTile.h"
#include "StairsTile.h"
#include "Space.h"
#include <list>
#include "Cofre.h"

#include "Pad.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String



class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	int newEnemyTime = 0;
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	list<Tile*> tiles;
	list<MovableTile*> mtiles;
	list < DraggableTile* > dtiles;
	list < StairsTile* > stiles;
	void calculateScroll();
	float scrollX;
	Space* space;
	Audio* audioBackground;
	Text* textPoints;
	Text* textLifes;
	Text* textRecolectables;
	int points;
	int lifes;
	int recolectable;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundLifes;
	Actor* backgroundRecolectables;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
	int counter =15;
	void teleportPlayer(int x, int y);
	Tile* salida;
	Tile* entrada;
	//Movidas pal ratón
	// Elementos de interfaz
	Pad* pad;
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	Actor* buttonJump;
	Actor* buttonShoot;
	//---------------

	list<Cofre*> cofres;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Puerta*> puertas;
	

};

