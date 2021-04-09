#include "Powerup.h"

void Powerup::activate() {                              // Activation of Powerup
    if(getPowerupAvailable() == true) {                 // If the powerup is available, activate it and make it unavailable
        setPowerupActive(true);
        setPowerupAvailable(false);
    }
}

void Powerup::powerTick() {                             // Tick in Powerup
    if(getPowerupActive()){                             // Only ticks if active
        setPowerupCounter(getPowerupCounter()-1);       // Counts down once per tick
        if(getPowerupCounter() == 0){                   // If countdown reaches 0, powerup is deactivated and marked as used
            setPowerupActive(false);
            setUsed(true);
        }
    }
}