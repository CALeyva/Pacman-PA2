#include "PauseState.h"

PauseState::PauseState() {
    music.load("music/pacman_chomp.wav");
}

void PauseState::tick() {
    if(!music.isPlaying()){
			music.play();
	}
}

void PauseState::render(Leaderboard *lb) {
    ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
    lb->render(-1);
}

void PauseState::keyPressed(int key) {
    if(key == 'r') {
        setFinished(true);
        setNextState("Game");
    }
    if(key == 'q') {
        setFinished(true);
        setNextState("Menu");
        map->getPlayer()->setHealth(3);
        finalScore = map->getPlayer()->getScore();
        map->getPlayer()->setScore(0);
    }
    map->keyPressed(key);
}

void PauseState::reset(){
    setFinished(false);
    setNextState("");
}

PauseState::~PauseState(){
    delete map;
}