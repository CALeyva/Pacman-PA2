#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Leaderboard::Leaderboard() {
    this->loaded = this->load();
    this->order();
}

void Leaderboard::addEntry(string name, int score) {
    Entry entry = {name, score};
    this->entries.push_back(entry);
    this->saved = this->save(entry);
    this->order();
}

Leaderboard::Entry Leaderboard::getEntry(int i) const {
    return this->entries[i];
}

bool Leaderboard::load() {
    ifstream f;
    f.open(this->file, ios::in);
    if (!f.is_open()) { return false; }
    Entry buffer;
    entries.clear();
    while (!f.eof()) {
        f >> buffer.name;
        f >> buffer.score;
        entries.push_back(buffer);
    }
    f.close();
    return true;
}

bool Leaderboard::save(Entry entry) {
    ofstream f;
    f.open(this->file, ios::app);
    if (!f.is_open()) { return false; }
    f << '\n' << entry.name << '\n' << entry.score;
    f.close();
    return true;
}

void Leaderboard::order() {
    sort(entries.begin(), entries.end());
}

void Leaderboard::render(int amount) {
    if (amount > this->entries.size() || amount == -1) amount = entries.size();
    ofSetColor(256, 256, 256);
    ofDrawBitmapString("Leaderboard: ", ofGetWidth()/2, ofGetHeight()/2+75, 50);
    for (int i = 0; i < amount; i++) {
        ofDrawBitmapString(to_string(i+1) + ".  " + entries[i].name + " : " + to_string(entries[i].score) + "pts", ofGetWidth()/2-50, ofGetHeight()/2+(100+15*i), 50);
    }
}