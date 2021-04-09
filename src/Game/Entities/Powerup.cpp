#include "Powerup.h"

void Powerup::activate() {
    if(getPowerupAvailable() == true) {
        setPowerupActive(true);
        setPowerupAvailable(false);
    }
}

void Powerup::powerTick() {
    if(getPowerupActive()){
        setPowerupCounter(getPowerupCounter()-1);
        if(getPowerupCounter() == 0){
            setPowerupActive(false);
            setUsed(true);
        }
    }
}