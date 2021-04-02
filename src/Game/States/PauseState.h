#pragma once
#include "GameState.h"

class PauseState: public GameState {
    public:
        PauseState();
        ~PauseState();
        void tick();
        void keyPressed(int key);
        void render();
        void reset();
};