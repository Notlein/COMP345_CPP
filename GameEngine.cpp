#include "GameEngine.h"
#include <string>
#include "MapDriver.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <vector>
#include <math.h>
using namespace std;

vector<Player *> players;

// constructor
GameEngine::GameEngine()
{
  // set the state to start when a new game engine is created
  string *str = new string("start");
  curr_state = str;
  cout << "State set to " << *str << endl;
  vector<Player *> player;
}

// copy constructor
GameEngine::GameEngine(const GameEngine &engine)
{
  this->curr_state = new string(*(engine.curr_state));
}

// assignment operator
GameEngine &GameEngine::operator=(const GameEngine &engine)
{
  this->curr_state = new string(*(engine.curr_state));
  return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const GameEngine &GameEngine)
{
  out << "Current State is " << *GameEngine.curr_state << endl;
  return out;
}

// destructor
GameEngine::~GameEngine()
{
  delete curr_state;
  curr_state = NULL;
}

// the setter function to set state to a new value
void GameEngine::setState(string *new_state)
{
  delete curr_state;
  curr_state = new_state;
  cout << "State set to " << *new_state << endl;
}

// changeState takes user entered transition and check if it is a valid input, if so, make the transition
void GameEngine::changeState(string *input)
{
  // -------------------startup----------------------
  if (*curr_state == "start")
  {
    if (*input == "loadmap")
    {
      setState(new string("map loaded"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "map loaded")
  {
    if (*input == "loadmap")
    {
      setState(new string("map loaded"));
    }
    else if (*input == "validatemap")
    {
      setState(new string("map validated"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "map validated")
  {
    if (*input == "addplayer")
    {
      setState(new string("players added"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "players added")
  {
    if (*input == "addplayer")
    {
      setState(new string("players added"));
    }
    else if (*input == "assigncountries")
    {
      setState(new string("assign reinforcement"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
    // ------------------play-------------------
  }
  else if (*curr_state == "assign reinforcement")
  {
    if (*input == "issueorder")
    {
      setState(new string("issue orders"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "issue orders")
  {
    if (*input == "issueorder")
    {
      setState(new string("issue orders"));
    }
    else if (*input == "endissueorders")
    {
      setState(new string("execute orders"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "execute orders")
  {
    if (*input == "execorder")
    {
      setState(new string("execute orders"));
    }
    else if (*input == "endexecorders")
    {
      setState(new string("assign reinforcement"));
    }
    else if (*input == "win")
    {
      setState(new string("win"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
  else if (*curr_state == "win")
  {
    if (*input == "play")
    {
      setState(new string("start"));
    }
    else
    {
      cout << "You have entered an invalid command" << endl;
    }
  }
}
// implement get vector of players
vector<Player *> *GameEngine::getPlayer()
{
  return player;
}

void GameEngine::startupPhase(vector<Player *> *player)
{
  // Adjacent map
  vector<vector<string> > map;
  int totalPlayer = 0;
  cout << &map << "map1" << endl;
  // string that will contain terrytories
  vector<string> stringList;
  cout << &stringList << "stringList" << endl;
  int attempts = 0;  // Multiple wrong input automatically exits the program
  int switchNum = 0; // switch number

  // For taking input from the user.
  bool GameStart = false;
  bool startPhase = false;

  // Initizlie deck why not
  Deck aDeck;
  aDeck.genDeck();
  cout << &aDeck << "aDeck" << endl;
  int maploadCount = 0;
  // You have three options to start UI.
  while (!startPhase)
  {
    int accessSwitch = 0;
    cout << "Enter the command: \n";
    cout << "list of options: \n"
         << "*------------------*\n"
         << "loadmap option \n"
         << "validate map\n"
         << "gamestart\n"
         << "*------------------*\n";
    string input;
    if (maploadCount >= 1)
      GameStart = false;
    getline(cin, input);

    // thsese switches will assign to the map that user wants.
    if (input == "loadmap option")
    {
      accessSwitch = 1;
    }
    else if (input == "validate map")
    {
      accessSwitch = 2;
    }
    else if (input == "gamestart")
    {
      accessSwitch = 3;
    }
    else
      exit(0);

    switch (accessSwitch)
    {
      // case 1 is option for the maps
    case 1:
      while (!GameStart)
      {
        string loading;
        cout << "Enter an input to load map (loadmap <filename>): \n"
             << "1. ./maps/Grand Montreal.map\n"
             << "2. ./maps/Quebec.map\n"
             << "3. ./maps/Honeycomb.map\n";
        getline(cin, loading);
        // user chooses 1 to load grand montreal map
        if (loading == "loadmap ./maps/Grand Montreal.map")
        {
          switchNum = 1;
          if (maploadCount >= 1)
            stringList.erase(stringList.begin());
          stringList.push_back("./maps/Grand Montreal.map");
          GameStart = true;
          maploadCount++;
        }
        // user chooses 2 to load Quebec map
        else if (loading == "loadmap ./maps/Quebec.map")
        {
          switchNum = 2;
          if (maploadCount >= 1)
            stringList.erase(stringList.begin());
          stringList.push_back("./maps/Quebec.map");
          GameStart = true;
          maploadCount++;
        }
        // user chooses 3 to load honey comb map
        else if (loading == "loadmap ./maps/Honeycomb.map")
        {
          switchNum = 3;
          if (maploadCount >= 1)
            stringList.erase(stringList.begin());
          stringList.push_back("./maps/Honeycomb.map");
          GameStart = true;
          maploadCount++;
        }

        // this switch lets to access the map and assign the adjacent map to whichever user choosed in the last command.
        switch (switchNum)
        {
        case 0:
          cout << "Input has no matching map, enter again you have " << 3 - attempts << " attempts";
          if (attempts == 3)
          {
            cout << "You entered the input wrong three times, program exits.\n";
            exit(0);
          }
          attempts++;
          break;
        case 1:
          // loads the map
          map = LoadMaps(1);
          break;
        case 2:
          map = LoadMaps(2);
          break;
        case 3:
          map = LoadMaps(3);
          break;
        }
        cout << endl;
      }
      break;
      // Case 2 validates map by checking if all the territories are connected.
    case 2:
      for (string x : stringList)
      {
        ifstream file(x);
        vector<vector<string> > v = parseMap(file);

        try
        {
          Map m(v);
          x = x.substr(7, x.length());
          x = x.substr(0, x.length() - 4);
          m.mapName = new string(x);

          // Uncomment below to show Continent name, number of points and territories.
          // for (int i = 0; i < m.continents->size(); i++)
          // {
          // string *s = new string(*m.continents->at(i).Cname);
          // int *s1 = new int(*m.continents->at(i).nbPts);
          // cout << "Continent name is : " << *s << endl
          //     << "Number of points : " << *s1 << endl
          //     << "Territories are : ";
          // cout << *m.continents->at(i).territories->at(0).Tname;
          // for (int j = 1; j < m.continents->at(i).territories->size(); j++)
          // {
          //     cout << *m.continents->at(i).territories->at(j).Tname << endl;
          // }
          // cout << "." << endl
          //     << endl;
          // }
          // end of comment section

          cout << endl;
          cout << "Map validation initiated:";
          cout << endl;
          bool val = m.validate();
          // Checks if there an error with path
          if (m.getNbContinents() < 1)
          {
            std::cerr << endl
                      << "********************\n"
                      << x << endl
                      << "********************\n"
                      << "There is a problem in the map syntax : Please verify the .map file" << endl;
          }
          // checks if map is not correctly connected
          else if (!val)
          {
            std::cerr << endl
                      << "********************\n"
                      << x << endl
                      << "********************\n"
                      << "There is a problem in the map. It's not a proper connected graph." << endl;
          }
          else
          // when map is valid.
          {
            std::cout << "Succesful map created" << endl
                      << "********************\n"
                      << x << endl
                      << "********************" << endl;
            cout << m << endl;
          }
          map = v;
          m.~Map();
        }
        // invalid map file
        catch (const std::exception &e)
        {
          std::cerr << "INVALID MAP FILE" << endl
                    << "********************\n"
                    << x << endl
                    << "********************" << endl
                    << endl
                    << e.what() << endl
                    << endl;
        }
      }
      break;
      // where user adds players.
    case 3:
    {

      // intialize orders list hand and territory objects that will assign to the player

      bool switchPlayer = false;
      // number of territory will be evenly distributed to the players


      // in an excapable while loop
      while (!switchPlayer)
      {

        if (totalPlayer >= 2)
        {
          string ans;
          cout << "Do you wanna stop creating player(s)? yes/no\n";

          cin >> ans;
          if (ans != "no")
          {
            switchPlayer = true;
            startPhase = true;
            cout << "Game play start!" << endl;
            break;
          }
        }
        totalPlayer++;

        vector<Player *> pl1;
        Hand hand1 = Hand();
        Territory *t1 = new Territory();
        // user inputs name of player
        string namePlayer1;

        cout << "Enter the name of the player:" << endl;
        cin >> namePlayer1;
        OrdersList ol1 = OrdersList();
        // draws two cards from the deck
        hand1.set_card(aDeck.draw());
        hand1.set_card(aDeck.draw());

        // vector pointer to territory
        vector<Territory *> tet;

        // this will everly distribute the number of territories,

        // for (; tettDistribute1 < map.size() / 6; tettDistribute1++)
        // {
        //   for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
        //   {
        //     t1 = new Territory(&map[tettDistribute1][tettDistribute2]);

        //     tet.push_back(t1);
        //   }
        // }

        // initialize the potiner to a player

        Player *player1 = new Player(50, namePlayer1, &tet, &pl1, &hand1, &ol1);

        // and push the pointer to player to the pointer to player vector.
        player->push_back(player1);

        // when number of players are 6 it exits
        if (totalPlayer == 6)
        {
          cout << "You have maximum players \n";
          switchPlayer = true;
          startPhase = true;
          break;
        }
      }

      cout << endl;
      break;
    }
    }
  }
  int tettDistribute1 = 0;
  int tettDistribute2 = 0;
  int counter = 0;
  for (; tettDistribute1 < map.size() / totalPlayer; tettDistribute1++)
  {
    for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
    {
        // cout << map[tettDistribute1][tettDistribute2];
        player->at(counter)->territories->push_back(new Territory(&map[tettDistribute1][tettDistribute2]));
        counter++;
        if (counter == totalPlayer)
        {
            counter = 0;
        }
    }
  }
  
}

int main()
{
  GameEngine *game = new GameEngine();
  vector<Player *> player;
  
  game->startupPhase(&player);



  game->~GameEngine();
  
  return 0;
}

int reinforcementPhase()
{

  for (Player *player : players)
  {

    // print how many reinforcements the current player has to test:
    cout << "Player " << player->getName() << " currently has " << player->get_reinforcement() << "reinforcements available at the begining of their turn.\n";

    // take count of players territories:
    int terrCount = player->toDefend()->size();

    // divide by 3.0:
    double reinforcementDouble = floor(double(terrCount) / 3.0);
    int reinforcementInt = int(reinforcementDouble);

    // minimum number of reinforcements is 3, therefore:
    if (reinforcementInt > 3)
    {

      reinforcementInt = 3;
    }

    // continued test
    cout << "Player " << player->getName() << " currently has " << terrCount << "territories, so they will recieve " << reinforcementInt << "reinforcements.\n";
    cout << "Player " << player->getName() << " currently has " << player->get_reinforcement() << "reinforcements available at the end of the reinforcement phase of their turn.\n\n\n";

    player->set_reinforcement(player->get_reinforcement() + reinforcementInt);
  }
  return 0;
}

 int issueOrdersPhase(){

   //for each turn, each player issues a certain number of deploy order, an order for each card they currently have, as well as one advance order.
   //Please see the implementation in Player::issueOrder()

   for(Player * player : players){

     player->issueOrder();

   }
   return 0;
 }

int executeOrdersPhase()
{

  // for each turn, each player executes all of the orders they issued in that turn
  bool finished = false;
  bool hasOrder = false;

  while (!finished)
  {

    for (Player *player : players)
    {

      OrdersList *playerOrderList = player->get_orders();
      vector<Order *> playersOrders = playerOrderList->get_OrderList();

      if (!playersOrders.empty())
      {

        hasOrder = true;
        playersOrders[0]->execute();
        playersOrders.erase(playersOrders.begin());
      }
    }

    if (hasOrder == false)
    {

      finished = true;
    }
  }
  return 0;
}

void mainGameLoop(){

   while(players.size() > 1){

     cout << "\n================";
     cout << "\nNEW TURN";
     cout << "\n================\n\n";

     reinforcementPhase();
     issueOrdersPhase();
     executeOrdersPhase();

     //if a player has no more territories to defend by the end of the turn, they are eliminated from the game:
     for(int i = 0; i < players.size(); i++){

       if (players[i]->toDefend()->empty()){

         cout << "Player " << players[i]->getName() << " has no more territories at the end of this turn, so they are eliminated.";
         *players.erase(players.begin() + i);

       }

     }

   }
 }