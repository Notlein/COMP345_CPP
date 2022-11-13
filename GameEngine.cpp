#include "GameEngine.h"
#include "Player.h"
#include <string>
#include <math.h>       /* floor */

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

  for(Player * player : *players){


    //print how many reinforcements the current player has to test: 
    cout << "Player " << player -> name << " currently has " << player -> reinforcementPool << "reinforcements available at the begining of their turn.\n";

    //take count of players territories:
    int terrCount = player -> toDefend().size();

    //divide by 3.0:
    double reinforcementDouble = floor(double(terrCount)/3.0);
    int reinforcementInt = int(reinforcementDouble);


    //minimum number of reinforcements is 3, therefore:
    if(reinforcementInt > 3){

      reinforcementInt = 3;

    }

    //continued test
    cout << "Player " << player -> name << " currently has " << terrCount << "territories, so they will recieve " << reinforcementInt << "reinforcements.\n";
    cout << "Player " << player -> name << " currently has " << player -> reinforcementPool << "reinforcements available at the end of the reinforcement phase of their turn.\n\n\n";

    player -> reinforcementPool += reinforcementInt;
  
  }

}

int issueOrdersPhase(){

  //for each turn, each player issues a certain number of deploy order, an order for each card they currently have, as well as one advance order.
  //Please see the implementation in Player::issueOrder()

  for(Player player : *players){

    player.issueOrder();
  
  }

}

int executeOrdersPhase(){

  //for each turn, each player executes all of the orders they issued in that turn
  bool finished = false;
  bool hasOrder = false;

  while(!finished){

    for(Player player : *players){
    
      if(player.orders[0] != null){

        hasOrder = true;
        player.orders[0].execute;
        player.orders.erase(0);

      }
    
    }

    if(hasOrder = false){

      finished = true;

    }

  }

}

  
void mainGameLoop(){

  while(players -> size() > 1){

    cout << "\n================";
    cout << "\nNEW TURN";
    cout << "\n================\n\n";

    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();

    //if a player has no more territories to defend by the end of the turn, they are eliminated from the game:
    for(Player player : *players){

      if (player->toDefend().empty()){

        cout << "Player " << player.name << " has no more territories at the end of this turn, so they are eliminated."
        *players.erase(player);

      }

    }

  }

}


