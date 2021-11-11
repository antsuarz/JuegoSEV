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
	//textPoints = new Text("0", WIDTH * 0.92, HEIGHT * 0.05, game);
	//textPoints->content = to_string(points);
	//textLifes = new Text("0", WIDTH * 0.13, HEIGHT * 0.1, game);
	//textLifes->content = to_string(lifes);
	//textRecolectables = new Text("0", WIDTH * 0.75, HEIGHT * 0.05, game);
	//textRecolectables->content =  to_string(recolectable);
	if(game->currentLevel == 0 || game->currentLevel == 2)
		background = new Background("res/Assets/fondo.png", WIDTH * 0.5, HEIGHT * 0.5,-1, game);
	if (game->currentLevel == 1) {
		background = new Background("res/Assets/fondo_cueva2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
		audioBackground = new Audio("res/Assets/Sonidos/MusicaCueva.mp3", true);
		audioBackground->play();
	}
	//Laposición es relativa a la pantalla, en este caso el 85% del aancho y el 5% del alto
	//backgroundPoints = new Actor("res/icono_puntos.png",
		//WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	//backgroundLifes= new Actor("res/icono_vidas.png",
		//WIDTH *0.07 , HEIGHT * 0.1 ,40, 40, game);
	//backgroundRecolectables = new Actor("res/icono_recolectable.png",
		//WIDTH * 0.65, HEIGHT * 0.07, 40, 40, game);

	puertas.clear();
	cofres.clear();
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	enemies.clear(); // Vaciar por si reiniciamos el juego
	mtiles.clear();
	dtiles.clear();
	stiles.clear();
	loadMap("res/" + to_string(game->currentLevel) + ".txt"); 

}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio automático de input
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas

		if (game->input == game->inputKeyboard) {
			keysToControls(event);
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
	
	// Nivel superado
	if (salida->isOverlap(player)) {
		if (counter == 0) {
			if (game->currentLevel == 2)
				game->currentLevel--;
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
		if (player->isOverlap(st))
			player->state = States::CLIMBING; 
		else
			player->state = States::IDLE;
	}
	for (auto const& enemy : enemies) {
		enemy->update();
	}
	for (auto const& tile : mtiles) {
		tile->update();
	}  

	for (auto const& r : cofres) {
		r->update();
	}

	// Colisiones
	for (auto const& mt : mtiles) {
		for (auto const& t : tiles)
			if (mt->isOverlap(t)) {
				if (t->x > mt->x) {
					mt->x = mt->x - 5;
				}
				else
					mt->x = mt->x + 5;
				mt->vx = mt->vx * -1;
				
			}
		if (player->isOverlap(mt) && player->state == States::IDLE) {
			player->x = mt->x;
		}
	}
	 
	int px = player->x;
	int py = player->y;
	for (auto const& dt : dtiles) { 
		if (player->isOverlap(dt) && px < dt->x && py == dt -> y -1) {
			dt->x = dt->x + 1;
		}
		else if (player->isOverlap(dt) && px > dt->x && py == dt->y - 1){
			dt->x = dt->x - 1;
		}
		else {
			int count = 0;
			for (auto const& t : tiles)
				if (dt->isOverlap(t))
					count++;
			for (auto const& t : mtiles)
				if (dt->isOverlap(t))
					count++;
			if (count > 0)
				count = 0;
			else
				dt->y = dt->y + 5;
		} 
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& rec : cofres) {
		if (player->isOverlap(rec)) {
			rec->open = true; 
		}
	}
	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;

	//Elimina los proyectiles si se salen de la pantalla
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
	for (auto const& p : puertas) {
		if (p->isOverlap(player)) {
			for(auto const& p2 : puertas)
				if (p2->ident == p -> ident && p2-> x != p-> x) {
					teleportPlayer(p2->x, p2->y);
				}
		}
	}
	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->impacted();	
			}
		}
	}
	for (auto const& enemy : enemies) {
		if (enemy->state == States::DEAD) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
				points++;
				textPoints->content = to_string(points);
			}
		}
	}


	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

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

	for (auto const& p : puertas) {
		p->draw(scrollX);
	}

	for (auto const& r: cofres) {
		r->draw(scrollX);
	}

	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	}
	for (auto const& tile : mtiles) {
		tile->draw(scrollX);
	}

	for (auto const& tile : dtiles) {
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
	player->draw(scrollX);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX);
	}
	//textPoints->draw(255,233,0);
	//backgroundPoints->draw();
	//textLifes->draw(0,0,0);
	//backgroundLifes->draw();
	//textRecolectables->draw(255, 0, 0);
	//backgroundRecolectables->draw();
	
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
		Cofre* r = new Cofre(x, y, game);
		r->y = r->y - r->height / 2;
		cofres.push_back(r);
		space->addDynamicActor(r);
		break;
	}
	case 'E': {
		Enemy* enemy = new Enemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '4': {
		Puerta* p = new Puerta("res/puerta-4.png",4, x, y, game);
		p->y = p->y - p->height / 2;
		puertas.push_back(p);
		space->addStaticActor(p);
		break;
	}
	case '5': {
		Puerta* p = new Puerta("res/puerta-5.png", 5, x, y, game);
		p->y = p->y - p->height / 2;
		puertas.push_back(p);
		space->addStaticActor(p);
		break;
	}
	case '7': {
		Puerta* p = new Puerta("res/puerta-7.png", 7, x, y, game);
		p->y = p->y - p->height / 2;
		puertas.push_back(p);
		space->addStaticActor(p);
		break;
	}
	case '8': {
		Puerta* p = new Puerta("res/puerta-8.png", 8, x, y, game);
		p->y = p->y - p->height / 2;
		puertas.push_back(p);
		space->addStaticActor(p);
		break;
	}
	case '9': {
		Puerta* p = new Puerta("res/puerta-9.png", 9, x, y, game);
		p->y = p->y - p->height / 2;
		puertas.push_back(p);
		space->addStaticActor(p);
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
	case 'B': {
		entrada = new Tile("res/Assets/Tiles/Pared_Volver.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		entrada->y = entrada->y - entrada->height / 2;
		space->addNoGravityActor(entrada);
		break;
	}
	case 'C': {
		salida = new Tile("res/Assets/Tiles/Tile_Puerta.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		salida->y = salida->y - salida->height / 2;
		space->addNoGravityActor(salida); // Realmente no hace falta
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
	case 'X': {
		MovableTile* tile = new MovableTile(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		mtiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'Q': {
		DraggableTile* tile = new DraggableTile(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		dtiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'S': {
		StairsTile* tile = new StairsTile(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		stiles.push_back(tile);
		space->addNoGravityActor(tile);
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



