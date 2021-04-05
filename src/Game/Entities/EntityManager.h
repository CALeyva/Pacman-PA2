#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> BoundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	void setSpawnRandom(bool b) {this->spawnRandom = b; };
	bool getSpawnRandom() { return this->spawnRandom; };
private:
	bool killable = false;
	int killableCounter;
	bool spawnRandom = false;
};