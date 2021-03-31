#include "Powerup.h"

void Powerup::activate() {
    if(used == false){
        powerupActive = true;
        powerup = false;
        used = true;
        powerupCounter = 30*10;
    }
}

void Powerup::powerTick() {
    if(powerupActive){
        powerupCounter--;
        if(powerupCounter == 0){
            powerupActive = false;
        }
    }
}