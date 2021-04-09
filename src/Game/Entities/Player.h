#pragma once
#include "Animation.h"
#include "EntityManager.h"
#include "RandomPowerup.h"
#include "DoublePowerup.h"
#include "PeekABooPowerup.h"

class Player: public Entity {

    private:
        int spawnX, spawnY;                                 // Private Variables for Pacman logic
        int health=3;
        int score=0;
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;                               // Animation properties in Pacman
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;                                  // Entity Manager
        Powerup *poweru;                                    // Powerups
        RandomPowerup *rpu;
        DoublePowerup *dpu;
        PeekABooPowerup *ppu;

    public:
        Player(int, int, int , int, EntityManager*);        // Constructor
        ~Player();                                          // Destructor

        void tick();                                        // Pacman Logic methods
        void render();
        void reset();
        void checkCollisions();
        void keyPressed(int);
        void keyReleased(int);
        void mousePressed(int, int, int);
        void spawnRandom(Player* player);
        void damage(Entity* damageSource);
        void die();

        void setHealth(int);                                // Setters
        void setScore(int);
        void setX(int setX);
        void setY(int setY);
        void setPower(Powerup* power);
        void setFacing(FACING facing);

        int getScore();                                     // Getters
        int getHealth();
        bool getPowerAvailable();
        Powerup* getPower();
        EntityManager* getEm() { return this->em; }
        RandomPowerup* getRPU() { return this->rpu; }
        DoublePowerup* getDPU() { return this->dpu; }
        PeekABooPowerup* getPPU() { return this->ppu; }
};