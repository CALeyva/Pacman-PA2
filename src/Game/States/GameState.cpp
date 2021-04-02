#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if (map->getPlayer()->getScore() >= 4400) {
		setFinished(true);
		setNextState("WinState");
	}
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	if (key == 'y'){
        setFinished(true);
		setNextState("WinState");
    }
	if (key == 'p'){
		setFinished(true);
		setNextState("PauseState");
		finalScore = map->getPlayer()->getScore();
	}
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	if(getWasPaused() == false){
		this->map = MapBuilder().createMap(mapImage);
	} else {
		setWasPaused(false);
	}
}

void GameState::setScore(int sc){
	score = sc;
}

int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}