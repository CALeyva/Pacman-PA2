#pragma once
#include "GameState.h"
#include "Leaderboard.h"

class PauseState: public GameState {
    public:
        PauseState();
        ~PauseState();
        void tick();
        void keyPressed(int key);
        void render(Leaderboard *lb);
        void reset();
};