#include "Space.h"

Space::Space(float gravity) {
	this->gravity = gravity;
	dynamicActors.clear();
	staticActors.clear();
    boxActors.clear();
    noGravityActors.clear();
}

void Space::addDynamicActor(Actor* actor) {
	dynamicActors.push_back(actor);
}

void Space::addBoxActor(Actor* actor) {
    boxActors.push_back(actor);
}

void Space::addNoGravityActor(Actor* actor) {
    noGravityActors.push_back(actor);
}
void Space::addStaticActor(Actor* actor) {
	staticActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor) {
	dynamicActors.remove(actor);
}
void Space::removeNoGravityActor(Actor* actor) {
    noGravityActors.remove(actor);
}
void Space::removeStaticActor(Actor* actor) {
	staticActors.remove(actor);
}

void Space::update() {
	for (auto const& actor : dynamicActors) { 
		updateMoveRight(actor);
		updateMoveLeft(actor);
        updateMoveTop(actor);
        updateMoveDown(actor);
	}

    for (auto const& actor : boxActors) {
        updateMoveBoxRight(actor);
        updateMoveBoxLeft(actor); 
    }

}

void Space::updateMoveRight(Actor* dynamicAct) {
    if (dynamicAct->vx > 0) {
        int possibleMovement = dynamicAct->vx;
        // El mejor "idealmente" vx partimos de ese

        for (auto const& staticAct : staticActors) {
            int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            int topDynamic = dynamicAct->y - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y + dynamicAct->height / 2;

            int leftStatic = staticAct->x - staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y  + staticAct->height / 2;
             
            if ((rightDynamic + dynamicAct->vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {
                 
                if (possibleMovement >= leftStatic - rightDynamic) { 
                    possibleMovement = leftStatic - rightDynamic;
                }
            }
        } 
        dynamicAct->x = dynamicAct->x + possibleMovement; 
        dynamicAct->vx = possibleMovement;
    }

}

void Space::updateMoveLeft(Actor* dynamicAct) {
    if (dynamicAct->vx < 0) {
        int possibleMovement = dynamicAct->vx; 

        for (auto const& staticAct : staticActors) {
            int leftDynamic = dynamicAct->x  - dynamicAct->width / 2;
            int topDynamic = dynamicAct->y - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y + dynamicAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
             
            if ((leftDynamic + dynamicAct->vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {
                 
                if (possibleMovement <= rightStatic - leftDynamic) { 
                    possibleMovement = rightStatic - leftDynamic;
                }

            }

        } 
        dynamicAct->x = dynamicAct->x + possibleMovement; 
        dynamicAct->vx = possibleMovement;
    }

}

void Space::updateMoveTop(Actor* dynamicAct) {
    if (dynamicAct->vy < 0) {
        int possibleMovement = dynamicAct->vy; 

        for (auto const& staticAct : staticActors) {
            int topDynamic = dynamicAct->y  - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y  + dynamicAct->height / 2;
            int rightDynamic = dynamicAct->x   + dynamicAct->width / 2;
            int leftDynamic = dynamicAct->x  - dynamicAct->width / 2;

            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((topDynamic + dynamicAct->vy) <= downStatic
                && downDynamic > topStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement <= downStatic - topDynamic) {
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = downStatic - topDynamic;
                }
            }
        }
        // Ya se han comprobado todos los estáticos
        dynamicAct->y = dynamicAct->y + possibleMovement;
        // Restringir la velocidad actual (opcional)
        dynamicAct->vy = possibleMovement;
    }

}

void Space::updateMoveDown(Actor* dynamicAct) {
    if (dynamicAct->vy > 0) {
        int possibleMovement = dynamicAct->vy;
        // El mejor "idealmente" vy partimos de ese

        for (auto const& staticAct : staticActors) {
            int topDynamic = dynamicAct->y - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y + dynamicAct->height / 2;
            int rightDynamic = dynamicAct->x  + dynamicAct->width / 2;
            int leftDynamic = dynamicAct->x  - dynamicAct->width / 2;

            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((downDynamic + dynamicAct->vy) >= topStatic
                && topDynamic < downStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {
                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement >= topStatic - downDynamic) {
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = topStatic - downDynamic;
                    dynamicAct->collisionDown = true;
                }
            }
        }
        // Ya se han comprobado todos los estáticos
        dynamicAct->y = dynamicAct->y + possibleMovement;
        // Restringir la velocidad actual (opcional)
        dynamicAct->vy = possibleMovement;
    }
}

void Space::updateMoveBoxRight(Actor* box) {
    if (box->vx > 0) {
        int possibleMovement = box->vx; 

        for (auto const& staticAct : staticActors) {
            int rightDynamic = box->x + box->width / 4;
            int topDynamic = box->y - box->height / 4;
            int downDynamic = box->y + box->height / 4;

            int leftStatic = staticAct->x - staticAct->width / 4;
            int topStatic = staticAct->y - staticAct->height / 4;
            int downStatic = staticAct->y + staticAct->height / 4;

            if ((rightDynamic + box->vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement >= leftStatic - rightDynamic) {
                    possibleMovement = leftStatic - rightDynamic;
                }
            }
        }
        box->x = box->x + possibleMovement;
        box->vx = possibleMovement;
    }

}

void Space::updateMoveBoxLeft(Actor* dynamicAct) {
    if (dynamicAct->vx < 0) {
        int possibleMovement = dynamicAct->vx;

        for (auto const& staticAct : staticActors) {
            int leftDynamic = dynamicAct->x - dynamicAct->width /4;
            int topDynamic = dynamicAct->y - dynamicAct->height /4;
            int downDynamic = dynamicAct->y + dynamicAct->height / 4;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;

            if ((leftDynamic + dynamicAct->vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement <= rightStatic - leftDynamic) {
                    possibleMovement = rightStatic - leftDynamic;
                }

            }

        }
        dynamicAct->x = dynamicAct->x + possibleMovement;
        dynamicAct->vx = possibleMovement;
    }

}

