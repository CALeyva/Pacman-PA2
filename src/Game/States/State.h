#pragma once

#include "ofMain.h"
#include "Leaderboard.h"

class State {
	public:
		State() {}															// Public methods for state logic
		virtual void reset() = 0;
		virtual void tick() = 0;
		virtual void render(Leaderboard *lb) = 0;							// Virtual leaderboard render method
		virtual void keyPressed(int key) = 0;
		virtual void mousePressed(int x, int y, int button) = 0;

		virtual void keyReleased(int key){}
		void mouseMoved(int x, int y){}
		void mouseDragged(int x, int y, int button){}
		void mouseReleased(int x, int y, int button){}
		void mouseEntered(int x, int y){}
		void mouseExited(int x, int y){}
		void windowResized(int w, int h){}
		void gotMessage(ofMessage msg){}
		void dragEvent(ofDragInfo dragInfo){}
		
		bool hasFinished(){													// State updating methods
			return finished;
		}

		string getNextState(){
			return nextState;
		}

		void setFinished(bool finished){
			this->finished = finished;
		}

		void setNextState(string nextState){
			this->nextState = nextState;
		}

		void setWasPaused(bool paused){
			this->wasPaused = paused;
		}
		
		bool getWasPaused(){
			return wasPaused;
		}

	private:
		string nextState;													// Private State updating variables
		bool finished = false;
		bool wasPaused = false;
};