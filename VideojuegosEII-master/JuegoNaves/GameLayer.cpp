#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	 
	space = new Space(1);
	scrollX = 0;
	tiles.clear();

	if(game->currentLevel == 0 || game->currentLevel == 2)
		background = new Background("res/Assets/fondo.png", WIDTH * 0.5, HEIGHT * 0.5,-1, game);
	if (game->currentLevel == 1) {
		background = new Background("res/Assets/fondo_cueva2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
		audioBackground = new Audio("res/Assets/Sonidos/MusicaCueva.mp3", true);
		audioBackground->play();
	}

	//Interfaz Vidas
	textLifes = new Text("100", WIDTH * 0.125, HEIGHT * 0.1, game);
	textLifes->content = to_string(100);
	backgroundLifes = new Actor("res/Assets/Iconos/IconoVidas.png", WIDTH * 0.09, HEIGHT * 0.1, 81, 36, game);
	//_________________________
	//Interfaz pociones
	textPotions  = new Text("100", WIDTH * 0.125, HEIGHT * 0.9, game);
	textPotions->content = to_string(0);
	backgroundPotions = new Actor("res/Assets/Iconos/IconoPociones.png", WIDTH * 0.09, HEIGHT * 0.9, 64, 36, game);
	//__________________________
	//Interfaz Arma
	textWeapon = new Text("100", WIDTH * 0.285, HEIGHT * 0.9, game);
	textWeapon->content = to_string(100);
	backgroundWeapon = new Actor("res/Assets/Iconos/IconoArma.png", WIDTH * 0.25, HEIGHT * 0.9, 81, 36, game);
	//__________________________
	//Interfaz Armadura
	textArmor = new Text("100", WIDTH * 0.465, HEIGHT * 0.9, game);
	textArmor->content = to_string(100);
	backgroundArmor = new Actor("res/Assets/Iconos/IconoArmadura.png", WIDTH * 0.43, HEIGHT * 0.9, 81, 36, game);
	//__________________________
	
	cofres.clear();
	projectiles.clear();  
	enemigos.clear();   
	dtiles.clear();
	destiles.clear();
	stiles.clear();
	loadMap("res/" + to_string(game->currentLevel) + ".txt"); 

}

void GameLayer::processControls() { 
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		} 
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		} 
	}
	if (controlShoot) {
		BolaFuego* newProjectile = player->cast();
		if (newProjectile != NULL) { 
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile); 
		}

	}
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);

	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::keysToControls(SDL_Event event) {
	//Cerrar pulsando el aspa
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1: //Escalar la pantalla usando la tecla 1
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}

	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}


void GameLayer::update() { 
	space->update();
	background->update();
	player->update();
	textLifes->content = to_string(player->life);
	textWeapon->content = to_string(player->atackDamage);
	textArmor->content = to_string(player->armor);
	
	// Nivel superado
	if (salida->isOverlapDraggable(player)) {
		if (counter == 0) {
			if (game->currentLevel == 2)
				game->currentLevel--; 
			if (game->currentLevel == 1)
				game->currentLevel = 4;
			else 
				game->currentLevel++;
			if (game->currentLevel > game->finalLevel) {
				game->currentLevel = 0;
			}
			counter = 15;
			init();
		}
		else
			counter--;
	}

	if (entrada->isOverlap(player)) {
		if (counter == 0) {
			game->currentLevel++;
			if (game->currentLevel > game->finalLevel) {
				game->currentLevel = 0;
			}
			counter = 15;
			init();
			if (game->currentLevel == 2) {
				audioBackground = new Audio("res/Assets/Sonidos/MusicaJuego.mp3", true);
				audioBackground->play();
			}
		}
		else
			counter--;
	}
	 
	for (auto const& st : stiles) {
		States s = player->state;
		if (player->isOverlap(st)) {
			player->state = States::CLIMBING;
			break;
		}
		else {
			if (s != States::CAST)
				player->state = States::IDLE; 
		}
	}
  
	for (auto const& e : enemigos) {
		e->update();
		if (e->isOverlap(player)) { 
			int ad = player->atackDamage; 
			int armor = player->armor;
			int potions = player->potions;
			if (game->battleLevel == 0) {
				game->battleLayer = new BattleLayer(0, ad, armor, potions, game);
				audioBackground = new Audio("res/Assets/Sonidos/Batalla.mp3", true);
				audioBackground->play();
			}
			if (game->battleLevel == 1) {
				game->battleLayer = new BattleLayer(1, ad, armor, potions, game);
				audioBackground = new Audio("res/Assets/Sonidos/BatallaSaturnos.mp3", true);
				audioBackground->play();
			}
			
			game->layer = game->battleLayer;
			 
		}
	}

	for (auto const& r : cofres) {
		
		r->update();
	}

	// Colisiones
	for (auto const& dt : dtiles) { 
		if (player->isOverlapDraggable(dt) && player->orientation == Orientation::BOT) {  
			dt->y= dt->y - 3;
			break;
		}
		else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::TOP) { 
			dt->y = dt->y + 3;
			break;
		}
		else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::RIGHT) {
			 
			dt->x = dt->x + 3; 
			break;
		}
		else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::LEFT) {
			dt->x = dt->x - 3; 
			break;
		}  
	}

	for (auto const& dt : dtiles) {
		for (auto const& t : tiles) {
			if (t->isOverlapDraggable (dt) && player->orientation == Orientation::TOP) {
				player->y = player->y - 5;
				dt->y = dt->y - 3;
				break;
			}
			else if (t->isOverlapDraggable (dt) && player->orientation == Orientation::BOT) {
				player->y = player->y + 5;
				dt->y = dt->y + 3;
				break;
			}
			if (t->isOverlapDraggable(dt) && player->orientation == Orientation::RIGHT) {
				player->x = player->x - 5;
				dt->x = dt->x - 3;
				break;
			}
			else if (t->isOverlapDraggable(dt) && player->orientation == Orientation::LEFT) {
				player->x = player->x + 5;
				dt->x = dt->x + 3;
				break;
			} 
		}
	}

	for (auto const& dt : destiles) {
		dt->update();
		if (!dt->hasBeenDestroyed) {
			if (player->isOverlapDraggable(dt) && player->orientation == Orientation::BOT) {
				player->y = player->y + 5;
			}
			else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::TOP) {
				player->y = player->y - 5;
			}
			else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::RIGHT) {
				player->x = player->x - 5;
			}
			else if (player->isOverlapDraggable(dt) && player->orientation == Orientation::LEFT) {
				player->x = player->x + 5;
			}
			else
				continue;
		}
	}
	 
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& rec : cofres) {
		if (player->isOverlap(rec)) {
			if (rec->contenido == Contenido::ARMA && rec->open == false)
				player->atackDamage += 20;
			if (rec->contenido == Contenido::ARMADURA && rec->open == false)
				player->armor += 10;
			if (rec->contenido == Contenido::POCION && rec->open == false)
				player->potions += 1;
			rec->open = true;
			textPotions->content = to_string(player->potions);
		}
	}
	list<BolaFuego*> deleteProjectiles;
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX) == false || projectile -> vx == 0) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}
	for (auto const& tile : destiles) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				tile->impact = true; 
			}
		}
	}
	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}
	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();

	for (auto const& r: cofres) {
		r->draw(scrollX);
	} 

	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	} 

	for (auto const& tile : stiles) {
		tile->draw(scrollX);
	}

	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX);
	}

	entrada->draw(scrollX);
	salida->draw(scrollX);

	for (auto const& tile : dtiles) {
		tile->draw(scrollX);
	}

	for (auto const& tile : destiles) {
		tile->draw(scrollX);
	}

	for (auto const& enemy : enemigos) {
		enemy->draw(scrollX);
	}

	player->draw(scrollX);

	backgroundPotions->draw();
	textPotions->draw(0, 255, 0,1);
	backgroundLifes->draw();
	textLifes->draw(255,50, 50,1);
	backgroundWeapon->draw();
	textWeapon->draw(0, 0, 0,1);
	backgroundArmor->draw();
	textArmor->draw(250, 250, 250,1);
	
	
	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	
	case 'R': {
		Cofre* r = new Cofre(x, y, Contenido::POCION, game);
		r->y = r->y - r->height / 2;
		cofres.push_back(r);
		space->addDynamicActor(r);
		break;
	} 
	case 'O': {
		Cofre* r = new Cofre(x, y, Contenido::ARMA, game);
		r->y = r->y - r->height / 2;
		cofres.push_back(r);
		space->addDynamicActor(r);
		break;
	}
	case 'U': {
		Cofre* r = new Cofre(x, y, Contenido::ARMADURA, game);
		r->y = r->y - r->height / 2;
		cofres.push_back(r);
		space->addDynamicActor(r);
		break;
	}
	case 'E': {
		EnemyOverworld* e = new EnemyOverworld("res/Assets/Saturnos.png",68,29,4 ,17,x, y, game);
		// modificación para empezar a contar desde el suelo.
		e->y = e->y - e->height / 2;
		game->battleLevel = 1;
		enemigos.push_back(e);
		space->addNoGravityActor(e);
		break;
	}
	case 'k': {
		EnemyOverworld* e = new EnemyOverworld("res/Assets/Karst.png",48,29, 2,24, x, y, game);
		// modificación para empezar a contar desde el suelo.
		game->battleLevel = 0;
		e->y = e->y - e->height / 2;
		enemigos.push_back(e);
		space->addNoGravityActor(e);
		break;
	}
	case '1': {
		cout << "x: ";
		cout << x;
		cout << " y : ";
		cout <<y;
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	
	case '#': {
		Tile* tile = new Tile("res/Assets/Tiles/Borde_Mapa.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2; 
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'X': {
		DestructibleTile* tile = new DestructibleTile(x,y,game); 
		tile->y = tile->y - tile->height / 2;
		destiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case 'B': { 
		entrada = new Tile("res/Assets/Tiles/Pared_Volver.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		entrada->y = entrada->y - entrada->height / 2;
		space->addDynamicActor(entrada);
		break;
	}

	case 'C': {
		if (game->currentLevel == 1)
			salida = new Tile("res/Assets/Tiles/Puerta_Cueva.png", x, y, game);
		else
			salida = new Tile("res/Assets/Tiles/Tile_Puerta.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		salida->y = salida->y - salida->height / 2;
		space->addDynamicActor(salida); // Realmente no hace falta
		break;
	}
	case 'P': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Pared.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'T': {
		Tile* tile = new Tile("res/Assets/Arbol.gif", x, y,32,53, game);
		// modificación para empezar a contar desde el suelo.
		 
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'p': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Pared.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case 'A': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Pared_Cueva_Bot.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '0': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Pared_Cueva_Top.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	
	case 'F': {
		Tile* tile = new Tile("res/Assets/Tiles/Pared_Cueva_Top.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'G': {
		Tile* tile = new Tile("res/Assets/Tiles/Pared_Cueva.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'g': {
		Tile* tile = new Tile("res/Assets/Tiles/Pared_Cueva.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case 'H': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_ParedD.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'I': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_ParedI.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'J': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Esquina_Decha_Bot.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'K': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Esquina_Izda_Bot.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'L': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Esquina_Decha_Top.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'M': {
		Tile* tile = new Tile("res/Assets/Tiles/Tile_Esquina_Izda_Top.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	} 
	case 'N': {
		Tile* tile = new Tile("res/Assets/Tiles/Negro.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case ']': {
		Tile* tile = new Tile("res/Assets/Tiles/Suelo_BordeD.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case '[': {
		Tile* tile = new Tile("res/Assets/Tiles/Suelo_BordeI.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	} 
	case 'Q': {
		DraggableTile* tile = new DraggableTile(x, y, game); 
		tile->y = tile->y - tile->height/2;
		dtiles.push_back(tile);
		space->addBoxActor(tile);
		break;
	} 
	case 'S': {
		StairsTile* tile = new StairsTile("res/Assets/Tiles/Escalera_Top.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		stiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case 'D': {
		StairsTile* tile = new StairsTile("res/Assets/Tiles/Escalera_Bot.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		stiles.push_back(tile);
		space->addNoGravityActor(tile);
		break;
	}
	case 's': {
		Tile* tile = new Tile("res/Assets/Tiles/PiedraPrao.gif", x, y, game); 
		tile->y = tile->y - tile->height / 2;
		tile->width = tile->width / 2;
		tile->height = tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'j': {
		Tile* tile = new Tile("res/Assets/Tiles/PiedraCueva.gif", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tile->width = tile->width / 2;
		tile->height = tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}


void GameLayer::teleportPlayer(int x, int y) {
	int px = player->x;
	int py = player->y;
	//Si el jugador entra por la izquierda de la puerta
	if (px < x) {
		player->x = x + 40;// hacer que el jugador aparezca más a la derecha de la puerta para que no esté todo el rato teletransportarse
		player->y = y;
	}
	//Si entra por la izquierda
	else {
		player->x = x - 40; // hacer que el jugador aparezca más a la derecha de la puerta para que no esté todo el rato teletransportarse
		player->y = y;
	}
	
}



