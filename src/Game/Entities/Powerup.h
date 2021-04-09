#pragma once

#include <string>

using namespace std;

class Powerup {
    public:
        string name;                                                                // Public Variable
        
        void activate();                                                            // Basic Powerup manipulation methods
        void powerTick();

        bool getPowerupAvailable() { return this->powerupAvailable; }               // Getters
        bool getPowerupActive() { return this->powerupActive; }
        bool getUsed() { return this->used; }
        int getPowerupCounter() { return this->powerupCounter; }
        string getName() {return this->name; }
        
        void setPowerupAvailable(bool pu) { this->powerupAvailable = pu; }          // Setters
        void setPowerupActive(bool activate) { this->powerupActive = activate; }
        void setUsed(bool u) { this->used = u; }
        void setPowerupCounter(int counter) { this->powerupCounter = counter; }

    private:
        bool powerupAvailable;                                                      // Private Variables accessed through getters and setters
        bool powerupActive;
        bool used;
        int powerupCounter;
};