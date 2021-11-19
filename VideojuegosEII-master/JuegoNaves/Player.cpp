#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 35, 35, game) {

	aJumpingRight = new Animation("res/jugador_saltando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aJumpingLeft = new Animation("res/jugador_saltando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);
	aClimbing = new Animation("res/Assets/Trepando.png",18, 29,
		72, 29, 6, 4, true, game);
	aIdleTop = new Animation("res/Assets/Felix_Idle_Frente.png", 18, 29,
		160, 29, 6, 10, true, game);
	aIdleBot = new Animation("res/Assets/Felix_Idle_Back.png", 18, 29,
		64, 29, 20, 4, true, game);
	aIdleRight = new Animation("res/Assets/Felix_Idle_Derecha.png", 18, 29,
		140,29 , 6, 10, true, game);
	aIdleLeft = new Animation("res/Assets/Felix_Idle_Izquierda.png", 18, 29,
		140, 30, 6, 10, true, game);
	aRunningTop = new Animation("res/Assets/Felix_Walk_Top.png", 19, 30,
		108, 30, 6, 6, true, game);
	aRunningBot = new Animation("res/Assets/Felix_Walk_Down.png", 19, 30,
		95.5, 30, 6, 6, true, game);
	aRunningRight = new Animation("res/Assets/Felix_Walk_Right.png", 19, 30,
		108, 30, 6, 6, true, game);
	aRunningLeft = new Animation("res/Assets/Felix_Walk_Left.png", 19, 30,
		108, 30, 6, 6, true, game);

	aShotingBot = new Animation("res/Assets/Lanzar_Hechizo_Frente.png", 19, 30,36, 30, 12, 2, true, game);
	aShotingTop = new Animation("res/Assets/Lanzar_Hechizo_Espalda.png", 19, 30, 36, 30, 12, 2, true, game);
	aShotingLeft = new Animation("res/Assets/Lanzar_Hechizo_Izquierda.png", 19, 30, 44, 30, 12, 2, true, game);
	aShotingRight = new Animation("res/Assets/Lanzar_Hechizo_Derecha.png", 19, 30, 44, 30, 12, 2, true, game);

	animation = aIdleRight;
	orientation = Orientation::RIGHT;
 
}

void Player::update() {
	 
	if (vy > 0) {
		orientation = Orientation::TOP;
	}
	if (vy < 0) {
		orientation = Orientation::BOT;
	}
	if (vx > 0) {
		orientation = Orientation::RIGHT;
	}
	if (vx < 0) {
		orientation = Orientation::LEFT;
	}
	
	else {
		if(state != States::CLIMBING)
			state = States::MOVING;
	}

	bool hasAnimationEnded = animation->update();

	// Selección de animación basada en estados
	if (state == States::JUMPING) {
		if (orientation == Orientation::RIGHT) {
			animation = aJumpingRight;
		}
		if (orientation == Orientation::LEFT) {
			animation = aJumpingLeft;
		}
	}
	
	if (state == States::CLIMBING || state == States::MOVING || state == States::IDLE) {

		if (vx != 0 || vy != 0) {
			if (orientation == Orientation::TOP) {

				if (state == States::CLIMBING) {
					animation = aClimbing;
				}
				else
					animation = aRunningBot;
			}
			if (orientation == Orientation::BOT) {
				if (state == States::CLIMBING) {
					animation = aClimbing;
				}
				else
					animation = aRunningTop;
			}
			if (orientation == Orientation::RIGHT) {
				animation = aRunningRight;
			}
			if (orientation == Orientation::LEFT) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0 && vy == 0) {
			if (orientation == Orientation::TOP) {
				animation = aIdleTop;
			}
			if (orientation == Orientation::BOT) {
				animation = aIdleBot;
			}
			if (orientation == Orientation::RIGHT) {
				animation = aIdleRight;
				state = States::IDLE;
			}
			if (orientation == Orientation::LEFT) {
				animation = aIdleLeft;
				state = States::IDLE;
			}
		}
	}
}

 


void Player::moveX(float axis) {
	 
		vx = axis * 3;
	 
}

void Player::moveY(float axis) {
	 
		vy = axis * 3;
	 
}

void Player::draw(float scrollX) {
	
	animation->draw(x - scrollX, y);
	
}
