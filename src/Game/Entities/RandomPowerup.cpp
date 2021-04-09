#include "RandomPowerup.h"
// #include "Entity.h"
// #include "Player.h"
// #include "Dot.h"

RandomPowerup::RandomPowerup() {
    this->name = "Random";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(1);
}

// void RandomPowerup::spawnRandom(Player* player) {
//     // Player* player = dynamic_cast<Player*>(p);
//     Entity* randomDot = player->getEm()->entities[rand() % player->getEm()->entities.size()];
//     while (!dynamic_cast<Dot*>(randomDot) || abs(player->getBounds().getX() - randomDot->getBounds().getX()) <= 100 || abs(player->getBounds().getY() - randomDot->getBounds().getY()) <= 100) {
//         randomDot = player->getEm()->entities[rand() % player->getEm()->entities.size()];
//     }
//     player->setX(randomDot->getBounds().getX());
//     player->setY(randomDot->getBounds().getY());
//     randomDot->remove = true;
// }