#include "GameEngineDriver.h"

using namespace std;

void testGameStates()
{

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
    while (cin >> input)
    {
        if (!input.compare("end") && !last.compare("win"))
        {
            engine.~GameEngine();
            cout << "You have ended the game" << endl;
            break;
        }

        engine.changeState(&input);
        cout << "---------Please enter new input------------" << endl;
        last = input;
    }
}

void testMainGameLoop()
{

    // This method calls the mainGameLoop method on a game engine object.
    // The mainGameLoop and its constituent methods for the three phases all contain console outputs that demonstrate the performance 6 features we are asked to demonstrate.

    // call mainGameLoop on an object of gameengine
    GameEngine *testEngine = new GameEngine();
    testEngine->mainGameLoop();
    // comment it out because main game loop function does not exist
}
