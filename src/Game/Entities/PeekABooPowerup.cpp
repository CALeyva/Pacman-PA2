#include "PeekABooPowerup.h"

PeekABooPowerup::PeekABooPowerup() {
    this->name = "PeekABoo";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(30*3);
}