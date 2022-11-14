#pragma once
#include <iostream>
#include <string>
using namespace std;

class GameEngine {

private:
    string *curr_state;

    // setState modifies the value of curr_state
    void setState(string *new_state);

public:
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
    void startupPhase();
};
