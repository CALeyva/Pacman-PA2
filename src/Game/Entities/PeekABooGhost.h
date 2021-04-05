#pragma once
#include "Ghost.h"

/*
Create a Subclass of Ghost called the PeekABooGhost. This Ghost will spawn
normally like any other ghost when pac man reaches 1000 points. The
PeekABooGhost will remain invisible, unless he is x amount of pixels away from
pacman. You define x. Note: the Ghost class has no access to pacman's location,
however both pacman and the ghost have access to the EntityManager. Use this
information to allow the implementation of this issue.
*/

class PeekABooGhost: public Ghost{
    public:
        PeekABooGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Ghost(x, y, width, height, spriteSheet, em, color){};
};