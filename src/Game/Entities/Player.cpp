#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"

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
    
}
void Player::tick(){
    if(powerupActive){ powerTick(); }
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
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
        
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
    
    if(score < 1500){
        ofDrawBitmapString("Powerup: loading " + to_string(1500 - score) + "/1500", ofGetWidth()/2-100, 50);
    } else if(score >= 1500 && powerup){
        ofDrawBitmapString("Powerup: ready", ofGetWidth()/2-100, 50);
    } else if(powerupActive){
        ofDrawBitmapString("Powerup: " + to_string(powerupCounter/30) + "." + to_string(powerupCounter%30) + " remaining", ofGetWidth()/2-100, 50);
    } else if(used == true){
        ofDrawBitmapString("Powerup: used", ofGetWidth()/2-50, 50);
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
            if (this->powerup == true) {
                activate();
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
                if(powerupActive){
                    score += 20;
                } else {
                    score += 10;
                }
            }
            if(dynamic_cast<BigDot*>(entity)){
                em->setKillable(true);
                if(powerupActive){
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
            }else{
                die();

            }
        }
    }
    if(score >= 1500 && used == false){ powerup = true; }
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}