#pragma once
#include "Ghost.h"

/*
Create a Subclass of Ghost called the RandomGhost. This Ghost will Spawn when
Pacman reaches 500 points. The Ghost will not Spawn in the location of the
GhostSpawner, instead, it will replace a random dot in the map. Whenever he dies, he
must replace another dot. Be careful not to allow the RandomGhost to appear too
close to Pacman, that he might lose too easily. 
*/

class RandomGhost: public Ghost{
    public:
        RandomGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Ghost(x, y, width, height, spriteSheet, em, color){};
};