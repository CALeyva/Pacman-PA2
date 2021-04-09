#include "DoublePowerup.h"

DoublePowerup::DoublePowerup() {
    this->name = "Double";
    this->setPowerupActive(false);
    this->setPowerupAvailable(false);
    this->setUsed(false);
    this->setPowerupCounter(30*10);
}