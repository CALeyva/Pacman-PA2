#include "DoublePowerup.h"

DoublePowerup::DoublePowerup() {    // Sets initially the powerup to be inactive, unavailable, unused, and sets duration
    this->name = "Double";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(30*10);
}