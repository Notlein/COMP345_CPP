#include "GameEngine.h"
#include <string>
//#include "Map.h"
//#include "Player.h"
//#include "Cards.h"
//#include "Orders.h"
#include <vector>
#include <math.h>       /* floor */
#include "Player.h"
using namespace std;

vector<Player *> players;
/*
Player player1 = Player(50, "george", &tett1, &pl1, &hand1, &ol1);
Player player2 = Player(50, "greg", &tett2, &pl1, &hand2, &ol1);
Player player3 = Player(50, "ann", &tett3, &pl1, &hand3, &ol1);
Player player4 = Player(50, "monkey", &tett4, &pl1, &hand4, &ol1);
Player player5 = Player(50, "ya mama", &tett5, &pl1, &hand5, &ol1);
Player player6 = Player(50, "padre", &tett6, &pl1, &hand6, &ol1);
*/

// constructor
GameEngine::GameEngine()
{
  // set the state to start when a new game engine is created
  string *str = new string("start");
  curr_state = str;
  cout << "State set to " << *str << endl;
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

int reinforcementPhase(){

  for(Player * player : players){


    //print how many reinforcements the current player has to test: 
    cout << "Player " << player -> getName() << " currently has " << player -> get_reinforcement() << "reinforcements available at the begining of their turn.\n";

    //take count of players territories:
    int terrCount = player -> toDefend()->size();

    //divide by 3.0:
    double reinforcementDouble = floor(double(terrCount)/3.0);
    int reinforcementInt = int(reinforcementDouble);


    //minimum number of reinforcements is 3, therefore:
    if(reinforcementInt > 3){

      reinforcementInt = 3;

    }

    //continued test
    cout << "Player " << player -> getName() << " currently has " << terrCount << "territories, so they will recieve " << reinforcementInt << "reinforcements.\n";
    cout << "Player " << player -> getName() << " currently has " << player -> get_reinforcement() << "reinforcements available at the end of the reinforcement phase of their turn.\n\n\n";

    player -> set_reinforcement(player->get_reinforcement() + reinforcementInt);
  
  }

}

int issueOrdersPhase(){

  //for each turn, each player issues a certain number of deploy order, an order for each card they currently have, as well as one advance order.
  //Please see the implementation in Player::issueOrder()

  for(Player * player : players){

    player->issueOrder();
  
  }

}

int executeOrdersPhase(){

  //for each turn, each player executes all of the orders they issued in that turn
  bool finished = false;
  bool hasOrder = false;

  while(!finished){

    for(Player * player : players){
    
      OrdersList* playerOrderList = player->get_orders();
      vector<Order *>* playersOrders = playerOrderList->get_OrderList(); 

      if(playersOrders[0] != nullptr){

        hasOrder = true;
        playersOrders[0].execute;
        playersOrders.erase(0);

      }
    
    }

    if(hasOrder = false){

      finished = true;

    }

  }

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

      if (*(players[i])->toDefend().empty()){

        cout << "Player " << player->getName() << " has no more territories at the end of this turn, so they are eliminated.";
        *players.erase(player);

      }

    }

  }
}
// void GameEngine::startupPhase()
// {
//   vector<vector<string> > map;
//   vector<string> stringList;
//   int attempts = 0;
//   int switchNum = 0;
//   bool GameStart = false;
//   bool startPhase = false;

//   vector<string *> tett1;
//   vector<string *> tett2;
//   vector<string *> tett3;
//   vector<string *> tett4;
//   vector<string *> tett5;
//   vector<string *> tett6;
//   Player *player1;
//   Player *player2;
//   Player *player3;
//   Player *player4;
//   Player *player5;
//   Player *player6;
//   vector<string> card1;
//   vector<string> card2;
//   vector<string> card3;
//   vector<string> card4;
//   vector<string> card5;
//   vector<string> card6;

//   Deck d;
//   d.genDeck();

//   while (!startPhase)
//   {
//     int accessSwitch = 0;
//     cout << "Enter the command: \n";
//     cout << "list of options: \n"
//          << "*------------------*\n"
//          << "loadmap option \n"
//          << "validate map\n"
//          << "gamestart\n"
//          << "*------------------*\n";
//     string input;

//     getline(cin, input);

//     if (input == "loadmap option")
//       accessSwitch = 1;
//     else if (input == "validate map")
//       accessSwitch = 2;
//     else if (input == "gamestart")
//       accessSwitch = 3;
//     else
//       exit(0);
//     switch (accessSwitch)
//     {
//     case 1:
//       while (!GameStart)
//       {
//         string loading;
//         cout << "Enter an input to load map (loadmap <filename>): \n"
//              << "1. ./maps/Grand Montreal.map\n"
//              << "2. ./maps/Quebec.map\n"
//              << "3. ./maps/Honeycomb.map\n";
//         getline(cin, loading);

//         if (loading == "loadmap ./maps/Grand Montreal.map")
//         {
//           switchNum = 1;
//           GameStart = true;
//           stringList.push_back("./maps/Grand Montreal.map");
//         }
//         else if (loading == "loadmap ./maps/Quebec.map")
//         {
//           switchNum = 2;
//           stringList.push_back("./maps/Quebec.map");
//           GameStart = true;
//         }

//         else if (loading == "loadmap ./maps/Honeycomb.map")
//         {
//           switchNum = 3;
//           stringList.push_back("./maps/Honeycomb.map");
//           GameStart = true;
//         }

//         switch (switchNum)
//         {
//         case 0:
//           cout << "Input has no matching map, enter again you have " << 3 - attempts << " attempts";
//           if (attempts == 3)
//           {
//             cout << "You entered the input wrong three times, program exits.\n";
//             exit(0);
//           }
//           attempts++;
//           break;
//         case 1:
//           map = LoadMaps(1);
//           break;
//         case 2:
//           map = LoadMaps(2);
//           break;
//         case 3:
//           map = LoadMaps(3);
//           break;
//         }
//         cout << endl;
//       }
//       break;

//     case 2:
//       for (string x : stringList)
//       {
//         ifstream file(x);
//         vector<vector<string> > v = parseMap(file);

//         try
//         {
//           // parse map name
//           Map m(v);
//           x = x.substr(7, x.length());
//           x = x.substr(0, x.length() - 4);
//           m.mapName = new string(x);

//           // Uncomment below to show Continent name, number of points and territories.
//           // for (int i = 0; i < m.continents->size(); i++)
//           // {
//           // string *s = new string(*m.continents->at(i).Cname);
//           // int *s1 = new int(*m.continents->at(i).nbPts);
//           // cout << "Continent name is : " << *s << endl
//           //     << "Number of points : " << *s1 << endl
//           //     << "Territories are : ";
//           // cout << *m.continents->at(i).territories->at(0).Tname;
//           // for (int j = 1; j < m.continents->at(i).territories->size(); j++)
//           // {
//           //     cout << *m.continents->at(i).territories->at(j).Tname << endl;
//           // }
//           // cout << "." << endl
//           //     << endl;
//           // }
//           // end of comment section

//           cout << endl;
//           cout << "Map validation initiated:";
//           cout << endl;
//           bool val = m.validate();

//           if (m.getNbContinents() < 1)
//           {
//             std::cerr << endl
//                       << "********************\n"
//                       << x << endl
//                       << "********************\n"
//                       << "There is a problem in the map syntax : Please verify the .map file" << endl;
//           }
//           else if (!val)
//           {
//             std::cerr << endl
//                       << "********************\n"
//                       << x << endl
//                       << "********************\n"
//                       << "There is a problem in the map. It's not a proper connected graph." << endl;
//           }
//           else
//           {
//             std::cout << "Succesful map created" << endl
//                       << "********************\n"
//                       << x << endl
//                       << "********************" << endl;
//             cout << m << endl;
//           }
//           map = v;
//           m.~Map();
//         }
//         catch (const std::exception &e)
//         {
//           std::cerr << "INVALID MAP FILE" << endl
//                     << "********************\n"
//                     << x << endl
//                     << "********************" << endl
//                     << endl
//                     << e.what() << endl
//                     << endl;
//         }
//       }
//       break;
//     case 3:
//     {
//       int numPlayer = 0;
//       bool switchPlayer = false;

//       cout << "How many players do you want to add? ( 2 ~ 6 )" << endl;

//       while (!switchPlayer)
//       {
//         cout << "Input: ";
//         cin >> numPlayer;
//         if (numPlayer < 7 && numPlayer > 1)
//         {
//           switchPlayer = true;
//         }
//       }

//       srand(time(NULL));

//       int sizeofarray = numPlayer;
//       int nubersArray[sizeofarray];
//       int n = sizeofarray, r, result;
//       int getRandNum[sizeofarray];
//       int arr[sizeofarray];
//       for (int i = 0; i < sizeofarray; i++)
//       {
//         arr[i] = i;
//       }
//       srand(time(NULL));
      
//       for (int x = 0; x < sizeofarray; ++x)
//       {
//         result = r = 0;
//         r = rand() % n;  // get random number from 0 to n
//         result = arr[r]; // the sought random no intothing w/ it
//         getRandNum[x] = arr[result];
//         arr[r] = arr[n - 1]; // replace the generated number
//         n--;                 // new count;
//       }

//       for (int i = 0; i < sizeofarray; i++)
//       {
//         cout << arr[i] << " ";
//       }

//       cout << endl;
//       int tettDistribute1 = 0;
//       int tettDistribute2 = 0;
//       for (int i = 0; i < numPlayer; i++)
//       {

//         switch (nubersArray[i])
//         {
//         case 0:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player1:" << endl;
//           cin >> namePlayer1;

//           card1.push_back(d.draw());
//           card1.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett1.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player1 = new Player(50, namePlayer1, tett1, card1, s);

//           break;
//         }
//         case 1:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player2:" << endl;
//           cin >> namePlayer1;

//           card2.push_back(d.draw());
//           card2.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett2.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player1 = new Player(50, namePlayer1, tett2, card2, s);

//           break;
//         }
//         case 2:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player3:" << endl;
//           cin >> namePlayer1;

//           card3.push_back(d.draw());
//           card3.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett3.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player3 = new Player(50, namePlayer1, tett3, card3, s);

//           break;
//         }
//         case 3:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player4:" << endl;
//           cin >> namePlayer1;

//           card4.push_back(d.draw());
//           card4.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett4.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player4 = new Player(50, namePlayer1, tett4, card4, s);

//           break;
//         }
//         case 4:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player5:" << endl;
//           cin >> namePlayer1;

//           card5.push_back(d.draw());
//           card5.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett5.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player5 = new Player(50, namePlayer1, tett5, card5, s);

//           break;
//         }
//         case 5:
//         {
//           string namePlayer1;
//           cout << "Enter the name of the player6:" << endl;
//           cin >> namePlayer1;

//           card6.push_back(d.draw());
//           card6.push_back(d.draw());

//           for (; tettDistribute1 < map.size() / numPlayer; tettDistribute1++)
//           {
//             for (; tettDistribute2 < map[tettDistribute1].size(); tettDistribute2++)
//             {
//               // cout << map[i][j];
//               tett6.push_back(&map[tettDistribute1][tettDistribute2]);
//             }
//           }

//           vector<Order *> s;
//           player6 = new Player(50, namePlayer1, tett6, card6, s);

//           break;
//         }
//         }
//       }
//     }
//     }
//   }
//   GameEngine engine = GameEngine();
//   string input;
//   string last;
//   cout << "---------Please enter new input------------" << endl;

//   // continously reading input from console
//   while (cin >> input)
//   {
//     if (!input.compare("end") && !last.compare("win"))
//     {
//       engine.~GameEngine();
//       cout << "You have ended the game" << endl;
//       break;
//     }

//     engine.changeState(&input);
//     cout << "---------Please enter new input------------" << endl;
//     last = input;
//   }
// }
