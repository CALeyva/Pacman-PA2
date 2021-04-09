#include "ofApp.h"
#include "Images.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetWindowTitle("Java Game Box");
	leaderboard = new Leaderboard();
	//States
	menuState = new MenuState();
	gameState = new GameState();
	gameOverState = new GameOverState();
	winState = new WinState();
	pauseState = new PauseState();
	// Initial State
	currentState = menuState;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentState != nullptr){
		currentState->tick();												// If the currentState exists, mark a tick
		if(currentState->hasFinished()){									// Changes state if current state is finished
			if(currentState->getNextState() == "Menu"){						// Changes to menustate
				currentState = menuState;
			}else if(currentState->getNextState() == "Game"){				// Changes to gamestate
				if(currentState == pauseState){
					currentState = gameState;								// If game was on pause, sets a boolean to reload the previous gamestate
					currentState->setWasPaused(true);
				}
				currentState = gameState;
			}else if(currentState->getNextState() == "over"){				// Changes to gameoverstate
				gameOverState->setScore(gameState->getFinalScore());		// Sets final score on the leaderboard
				currentState = gameOverState;
			}else if (currentState->getNextState() == "WinState"){			// Changes to winstate
				winState->setScore(gameState->getFinalScore());				// Sets final score on the leaderboard
				currentState = winState;
			}else if (currentState->getNextState() == "PauseState"){		// Changes to pausestate
				currentState = pauseState;									// Saves current score on the gamestate
				pauseState->setScore(gameState->getFinalScore());
			}
			currentState->reset();											// Resets state updating properties
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr) currentState->render(this->leaderboard);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr)
		currentState->keyPressed(key);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}
