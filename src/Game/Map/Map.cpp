#include "Map.h"
#include "Dot.h"
#include "BigDot.h"

Map::Map(EntityManager* em){
    entityManager = em;
}

void Map::tick(){
	entityManager->tick();
	player->tick();
	gs->tick(this->getPlayer());

}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	entityManager->render(dynamic_cast<Entity*>(this->getPlayer()));
	player->render();
}

void Map::keyPressed(int key){
	player->keyPressed(key);
	gs->keyPressed(key);

}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBoundBlock(BoundBlock* e){
    entityManager->BoundBlocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::setPlayer(Player* p){
    player = p;
}

Player* Map::getPlayer(){
	return player;
}
void Map::setGhostSpawner(GhostSpawner* p){
    gs = p;
}

bool Map::dotsLeft() {
	for (Entity* entity: this->entityManager->entities) {
		if (dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)) return true;
	}
	return false;
}

Map::~Map(){
	delete player;
	delete entityManager;
	delete gs;
}