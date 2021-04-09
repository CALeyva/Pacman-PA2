#pragma once

#include <string>

using namespace std;

class Powerup {
    public:
        bool powerupAvailable;
        bool powerupActive;
        bool used;
        int powerupCounter;
        string name;
        
        void activate();
        void powerTick();
        bool getPowerupAvailable() { return this->powerupAvailable; }
        bool getPowerupActive() { return this->powerupActive; }
        bool getUsed() { return this->used; }
        int getPowerupCounter() { return this->powerupCounter; }
        string getName() {return this->name; }
        
        void setPowerupAvailable(bool pu) { this->powerupAvailable = pu; }
        void setPowerupActive(bool activate) { this->powerupActive = activate; }
        void setUsed(bool u) { this->used = u; }
        void setPowerupCounter(int counter) { this->powerupCounter = counter; }
};