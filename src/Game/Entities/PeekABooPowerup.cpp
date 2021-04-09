#include "PeekABooPowerup.h"

PeekABooPowerup::PeekABooPowerup() {    // Sets initially the powerup to be inactive, unavailable, unused, and sets duration
    this->name = "PeekABoo";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(30*3);
}