#pragma once

class Powerup {
    public:
        virtual void activate();
        void powerTick();
        bool powerup = false;
        bool powerupActive = false;
        bool used = false;
        int powerupCounter;
};