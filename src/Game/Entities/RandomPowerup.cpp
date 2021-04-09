#include "RandomPowerup.h"

RandomPowerup::RandomPowerup() {    // Sets initially the powerup to be inactive, unavailable, unused, and sets duration
    this->name = "Random";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(1);
}