#pragma once

#include "Actor.h"
#include <list>

class Space
{
public:
	Space(float gravity);
	void update(); 
	void flyRight(Actor* a);
	void flyLeft(Actor* a);
	void updateMoveRight(Actor* dynamicAct);
	void updateMoveLeft(Actor* dynamicAct);
	void updateMoveTop(Actor* dynamicAct);
	void updateMoveDown(Actor* dynamicAct);
	void addDynamicActor(Actor* actor);
	void addNoGravityActor(Actor* actor);
	void addStaticActor(Actor* actor);
	void removeDynamicActor(Actor* actor);
	void removeStaticActor(Actor* actor);
	void removeNoGravityActor(Actor* actor);
	float gravity;
	list<Actor*> dynamicActors;
	list<Actor*> staticActors;

	list<Actor*> noGravityActors;
};

