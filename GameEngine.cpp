#include "GameEngine.h"
#include <string>

using namespace std;

// constructor
GameEngine::GameEngine() {
  //set the state to start when a new game engine is created
  string * str = new string("start");
  curr_state = str;
  cout << "State set to " << * str << endl;
}

// copy constructor
GameEngine::GameEngine(const GameEngine& engine) {
  this -> curr_state = new string(*(engine.curr_state));  
}

// assignment operator
GameEngine& GameEngine::operator=(const GameEngine& engine) {
  this -> curr_state = new string(*(engine.curr_state)); 
  return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const GameEngine& GameEngine) {
  out << "Current State is " << *GameEngine.curr_state << endl;
	return out;
}


// destructor
GameEngine::~GameEngine() {
  delete curr_state;
  curr_state = NULL;
}

// the setter function to set state to a new value
void GameEngine::setState(string * new_state) {
  delete curr_state;
  curr_state = new_state;
  cout << "State set to " << * new_state << endl;
}

// changeState takes user entered transition and check if it is a valid input, if so, make the transition
void GameEngine::changeState(string * input) {
  // -------------------startup----------------------  
  if (*curr_state == "start") {
    if (*input == "loadmap") {
      setState(new string("map loaded"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "map loaded") {
    if (*input == "loadmap") {
      setState(new string("map loaded"));
    } else if (*input == "validatemap") {
      setState(new string("map validated"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "map validated") {
    if (*input == "addplayer") {
      setState(new string("players added"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "players added") {
    if (*input == "addplayer") {
      setState(new string("players added"));
    } else if (*input == "assigncountries") {
      setState(new string("assign reinforcement"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  // ------------------play-------------------  
  } else if (*curr_state == "assign reinforcement") {
    if (*input == "issueorder") {
      setState(new string("issue orders"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "issue orders") {
    if (*input == "issueorder") {
      setState(new string("issue orders"));
    } else if (*input == "endissueorders") {
      setState(new string("execute orders"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "execute orders") {
    if (*input == "execorder") {
      setState(new string("execute orders"));
    } else if (*input == "endexecorders") {
      setState(new string("assign reinforcement"));
    } else if (*input == "win") {
      setState(new string("win"));
    }else {
       cout << "You have entered an invalid command" << endl;
    }
  } else if (*curr_state == "win") {
    if (*input == "play") {
      setState(new string("start"));
    } else {
       cout << "You have entered an invalid command" << endl;
    }
  }

}

int reinforcementPhase(){

  

}

int issueOrdersPhase(){



}

int issueOrdersPhase(){



}

  
int mainGameLoop(){

    

}

