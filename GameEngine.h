#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Player;

class GameEngine {

private:
    string *curr_state;
    // setState modifies the value of curr_state
    void setState(string *new_state);
    vector <Player *> *player;
public:
    // get vector of players
    vector <Player *> *getPlayer();
    // default constructor
    GameEngine();
    // copy constructor
    GameEngine(const GameEngine &engine);
    // assignment operator
    GameEngine &operator=(const GameEngine &engine);
    // stream insertion operator
    friend ostream &operator<<(ostream &out, const GameEngine &GameEngine);
    // Destructor
    ~GameEngine();

    // changeState takes user entered transition and check if it is a valid input, if so, make the transition
    void changeState(string *input);

    // ---------------Assignment 2 ---------------- //
    void startupPhase(vector <Player *> *player);
    //vector<Player*>player
    // Reinforcement phase of main game loop:
    int reinforcementPhase();
    // Issue orders phase of main game loop:
    // int issueOrdersPhase();
    // Execute orders phase of main game loop:
    int executeOrdersPhase();
    // Main game loop:
    int mainGameLoop();
};
