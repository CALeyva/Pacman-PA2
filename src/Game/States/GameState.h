#pragma once
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"

class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		void setScore(int sc);
		int getFinalScore();
		int score;
		ofSoundPlayer music;
		Map* map;
		int finalScore=0;
	
	private:
		ofImage mapImage;

};