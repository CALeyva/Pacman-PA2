#include "GhostSpawner.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"
#include "Player.h"
#include "Entity.h"
#include "Dot.h"
#include <cmath>

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(Player* player){
    std::vector<string> colors;
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");

    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            int selection = ofRandom(2);
            if (selection == 0 && player->getScore() >= 500) {
                if (!spawnedRandom) {
                    spawnRandomGhost(player, colors[ofRandom(4)]);
                }
            } else if (selection == 1 && player->getScore() >= 1000) {
                if (!spawnedPAB) {
                    spawnPeekABooGhost(player, colors[ofRandom(4)]);
                }
            } else {
                spawnGhost(colors[ofRandom(4)]);
            }
            spawnCounter = 30*5;
        }else{
            spawnCounter--;
        }
    }
    if (player->getScore() >= 500 && !spawnedRandom) { em->setSpawnRandom(true); }
    if (em->getSpawnRandom()) {
        em->setSpawnRandom(false);
        this->spawnedRandom = true;
        spawnRandomGhost(player, colors[ofRandom(4)]);
    }
    if (player->getScore() >= 1000 && !spawnedPAB) { em->setSpawnPeekABoo(true); }
    if (em->getSpawnPeekABoo()) {
        em->setSpawnPeekABoo(false);
        this->spawnedPAB = true;
        spawnPeekABooGhost(player, colors[ofRandom(4)]);
    }

}
void GhostSpawner::spawnGhost(string color){
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
    em->ghosts.push_back(g);
}

void GhostSpawner::spawnRandomGhost(Player* player, string color) {
    Entity* randomDot = em->entities[rand() % em->entities.size()];
    while (!dynamic_cast<Dot*>(randomDot) || abs(player->getBounds().getX() - randomDot->getBounds().getX()) <= 100 || abs(player->getBounds().getY() - randomDot->getBounds().getY()) <= 100) {
        randomDot = em->entities[rand() % em->entities.size()];
    }
    RandomGhost* rg = new RandomGhost(randomDot->getBounds().getX(),randomDot->getBounds().getY(),width-2,height-2,sprite,em, color);
    randomDot->remove = true;
    em->ghosts.push_back(rg);
}

void GhostSpawner::spawnPeekABooGhost(Player* player, string color) {
    PeekABooGhost* pg = new PeekABooGhost(x,y,width-2,height-2,sprite,em, color);
    em->ghosts.push_back(pg);
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        switch (rand() % 4) {
            case 0:
                spawnGhost("red");
                break;
            case 1:
                spawnGhost("pink");
                break;
            case 2:
                spawnGhost("cyan");
                break;
            case 3:
                spawnGhost("orange");
                break;
        }
    }
}