#pragma once

// #include "Cards.h"
// #include "Map.h"
// #include "Orders.h"
class Map;
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Player
{
    public:
        Player(); //default constructor
        ~Player(); //destructor
        // Player(string playerName, vector<Map::Territory*> territoriesOwned, vector<Cards*> playerHand, vector<Orders*> ordersIssued);
        Player(const Player&); //copy constructor
        

        //Data members
        string* name;
        // vector<Map::Territory> *territories;
        // vector<Cards*> *hand;
        // vector<Orders*> *orders;

        void toDefend(); 
        void toAttack();
        void issueOrder();

        //vector<Map::Territory*> *defenceList;
        //vector<Map::Territory*> *attackList;
};

string testPlayers();
