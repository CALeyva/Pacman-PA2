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
	// When there are no dots left, the game is won
	if (!map->dotsLeft()) {
		setFinished(true);
		setNextState("WinState");
		// Sets final score
		finalScore = map->getPlayer()->getScore();
		// Adds leaderboard entry
		leaderboard->addEntry("You", finalScore);
	}
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		// Sets final score
		finalScore = map->getPlayer()->getScore();
		// Resets score
		map->getPlayer()->setScore(0);
		// Adds leaderboard entry
		leaderboard->addEntry("You", finalScore);
	}
}
void GameState::render(Leaderboard *lb) {
	this->leaderboard = lb;
	map->render();
}

void GameState::keyPressed(int key){
	if (key == 'y'){
		// When pressed, wins game; for testing
        setFinished(true);
		setNextState("WinState");
		finalScore = map->getPlayer()->getScore();
		// Adds entry to leaderboard
		leaderboard->addEntry("You", finalScore);
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
		// Sets map property to a newly created
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