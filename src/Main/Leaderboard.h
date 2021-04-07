#pragma once

#include "ofMain.h"

class Leaderboard {

private:
	string file = "src/Main/Leaderboard.txt";
    typedef struct Entry {
        string name;
        int score;
        bool operator<(const Entry& a) const {
            return score > a.score; 
        }
    };
    vector<Entry> entries;
    static int const SizeOfEntry = sizeof(Entry);
    bool load();
    bool save(Entry entry);
    void order();
    bool loaded;
    bool saved;
public:
    Leaderboard();
    void addEntry(string name, int score);
    Entry getEntry(int i) const;
    void render(int amount);
};
