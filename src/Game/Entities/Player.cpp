#include "Player.h"
#include "Dot.h"
#include "BigDot.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    rpu = new RandomPowerup();                                  // Creates New Instances of Powerups
    dpu = new DoublePowerup();
    ppu = new PeekABooPowerup();
    this->setPower(rpu);
}

void Player::tick(){
    if(this->getRPU()->getPowerupActive()) {                    // If RPU is active, ticks it
        this->spawnRandom(this);                                // RPU causes pacman to spawn randomly
        this->getRPU()->powerTick();
    } else if (this->getDPU()->getPowerupActive()) {            // If DPU is active, ticks it
        this->getDPU()->powerTick();
    } else if (this->getPPU()->getPowerupActive()) {            // If PPU is active, ticks it
        this->getPPU()->powerTick();
    }
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick();          
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();     
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();     
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();      
        }
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if(!this->getPPU()->getPowerupActive()) {                               // If PPU is active, Pacman becomes invisible, not drawn in the render method
        if(facing == UP){
            walkUp->getCurrentFrame().draw(x, y, width, height);
        }else if(facing == DOWN){
            walkDown->getCurrentFrame().draw(x, y, width, height);
        }else if(facing == LEFT){
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        }else if(facing == RIGHT){
            walkRight->getCurrentFrame().draw(x, y, width, height);
        }
    }
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-250, 50);

    if(this->getPowerAvailable() == false) {                                                                // If no powers are available, displays that powerups are empty
        ofDrawBitmapString("Powerup: empty", ofGetWidth()/2-125, 50);
    } else {
        if (this->getPower()->getUsed() == false && this->getPower()->getPowerupActive() == false) {        // If powerup is available, unused, and not yet active, displays that it is ready to use
            ofDrawBitmapString(this->getPower()->getName() + ": ready", ofGetWidth()/2-125, 50);
        } else if (this->getPower()->getPowerupActive() == true) {                                          // If powerup is active, displays active powerup and duration left
            ofDrawBitmapString(this->getPower()->getName() + ": " + to_string(this->getPower()->getPowerupCounter()/30) + "." + to_string(this->getPower()->getPowerupCounter()%30) + " remaining", ofGetWidth()/2-125, 50);
        } else {                                                                                            // Displays last powerup used
            ofDrawBitmapString(this->getPower()->getName() + ": used", ofGetWidth()/2-125, 50);
        }
    }
        
};

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
        case 'n':
            die();
            break;
        case 'm':
            if (this->getHealth() < 3) { health++; }
            break;
        case ' ':
            if(this->getPowerAvailable()) {                         // If a powerup is available and unused, pressing ' ' will activate it
                if(this->getPower()->getUsed() == false) {
                    this->getPower()->activate();
                }
            }
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}

void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

int Player::getHealth(){
    return health;
}

void Player::setHealth(int h){
    health = h;
}
int Player::getScore(){
    return score;
}

void Player::setScore(int h){
    score = h;
}

void Player::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                if(this->getDPU()->getPowerupActive()){                 // If DPU is active, dots count for twice the points
                    score += 20;
                } else {
                    score += 10;
                }
            }
            if(dynamic_cast<BigDot*>(entity)){
                em->setKillable(true);
                if(this->getDPU()->getPowerupActive()){                 // If DPU is active, big dots count for twice the points
                    score += 20;
                } else {
                    score +=10;
                }
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
                if (dynamic_cast<RandomGhost*>(entity)) {               // If the ghost is a randomghost, respawns it
                    em->setSpawnRandom(true);
                    if (this->getRPU()->getUsed() == false) {           // If RPU is not yet used, makes it available
                        this->setPower(rpu);
                        this->getRPU()->setPowerupAvailable(true);
                    }
                } else if (dynamic_cast<PeekABooGhost*>(entity)) {      // If the ghost is a peekabooghost, respawns it
                    em->setSpawnPeekABoo(true);
                    if (this->getPPU()->getUsed() == false) {           // If PPU is not yet used, makes it available
                        this->setPower(ppu);
                        this->getPPU()->setPowerupAvailable(true);
                    }
                }
            }else{
                die();
            }
        }
    }
    if(score >= 1500 && this->getDPU()->getUsed() == false){            // Makes DPU available after 1500 points
        this->setPower(dpu);
        this->getDPU()->setPowerupAvailable(true);
    }
}

void Player::spawnRandom(Player* player) {                                                          // Method for moving pacman to a random dot
    Entity* randomDot = player->getEm()->entities[rand() % player->getEm()->entities.size()];       // Finds a random dot
    player->setX(randomDot->getBounds().getX());                                                    // Sets X and Y to the random dot's location
    player->setY(randomDot->getBounds().getY());
    randomDot->remove = true;                                                                       // Removes the dot
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

void Player::setPower(Powerup* power) {
    this->poweru = power;
}

Powerup* Player::getPower() {
    return this->poweru;
}

bool Player::getPowerAvailable() {                                          // Method for setting Power to the available Powerup, returns true if any powerups are available, false otherwise
    if (this->getRPU()->getPowerupAvailable() == true) {
        this->setPower(rpu);
        return true;
    } else if (this->getDPU()->getPowerupAvailable() == true) {
        this->setPower(dpu);
        return true;
    } else if (this->getPPU()->getPowerupAvailable() == true) {
        this->setPower(ppu);
        return true;
    } else {
        return false;
    }
}

void Player::setX(int setX) {                           // Sets pacman's X coordinates
    x = setX;
}

void Player::setY(int setY) {                           // Sets pacman's Y coordinates
    y = setY;
}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete rpu;
    delete dpu;
    delete ppu;
}