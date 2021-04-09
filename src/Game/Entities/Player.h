#pragma once
#include "Animation.h"
#include "EntityManager.h"
#include "RandomPowerup.h"
#include "DoublePowerup.h"
#include "PeekABooPowerup.h"

class Player: public Entity {

    private:
        int spawnX, spawnY;
        int health=3;
        int score=0;
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        Powerup *poweru;
        RandomPowerup *rpu;
        DoublePowerup *dpu;
        PeekABooPowerup *ppu;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        void setHealth(int);
        int getScore();
        void setScore(int);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        void die();
        void setPower(Powerup* power);
        Powerup* getPower();
        bool getPowerAvailable();
        void spawnRandom(Player* player);
        vector<Powerup*> PowersUnused;
        EntityManager* getEm() { return this->em; }
        void setX(int setX);
        void setY(int setY);
        RandomPowerup* getRPU() { return this->rpu; }
        DoublePowerup* getDPU() { return this->dpu; }
        PeekABooPowerup* getPPU() { return this->ppu; }
};