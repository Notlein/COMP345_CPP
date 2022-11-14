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