#include "PauseState.h"

PauseState::PauseState() {                          // PauseState includes music
    music.load("music/pacman_chomp.wav");
}

void PauseState::tick() {                           // Keeps music playing during PauseState
    if(!music.isPlaying()){
		music.play();
	}
}

void PauseState::render(Leaderboard *lb) {          // Renders the current score while game is paused
    ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
    // Renders entire leaderboard
    lb->render(-1);
}

void PauseState::keyPressed(int key) {
    if(key == 'r') {                                // Unpauses the game, sets next state to gamestate
        setFinished(true);
        setNextState("Game");
    }
    if(key == 'q') {                                // Quits the game, sets next state to menustate
        setFinished(true);
        setNextState("Menu");
        map->getPlayer()->setHealth(3);             // Resets pacman health and score
        finalScore = map->getPlayer()->getScore();  // Saves finalscore for the leaderboard
        map->getPlayer()->setScore(0);
    }
    map->keyPressed(key);                           // Registers keypress on the map
}

void PauseState::reset(){                           // Resets state updating properties
    setFinished(false);
    setNextState("");
}

PauseState::~PauseState(){                          // Deletes map instance
    delete map;
}