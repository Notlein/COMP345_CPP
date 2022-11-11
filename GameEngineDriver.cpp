#include "GameEngineDriver.h"

using namespace std;

void testGameStates() {


    // GameEngine engine1 = GameEngine();
    // cout << engine1;
    // GameEngine engine2 = engine1;
    // cout << engine2;
    // GameEngine engine3 = GameEngine(engine2);
    // cout << engine3;

    GameEngine engine = GameEngine();
    string input;
    string last;
    cout << "---------Please enter new input------------" << endl;

    // continously reading input from console
    while (cin >> input) {
        if (!input.compare("end") && !last.compare("win")) {
            engine.~GameEngine();
            cout << "You have ended the game" << endl;
            break;
        }

        engine.changeState(&input);
        cout << "---------Please enter new input------------" << endl;
        last = input;
    }
}

void testMainGameLoop(){

    //show a player's reinforecements before and after the reninforcement phase is executed
    cout << "This is a test of the reinforcement phase of the main game loop:\n";
    cout << "John starts the game with 50 reinforements\n";

    cout << "John start the game with XXX territories, and therefore should recieve an additional XXX territories\n";

    //This must be called on a game engine object:
    //reinforcementPhase();

    //cout << "John now has XXX reinforecments, XXX more than previously\n\n;"

    //Show that players only issue other kinds of orders when the can no longer issue deploy orders
    
    //john has this many reinforcements
    //issueOrdersPhase();
    //now john has none;
}