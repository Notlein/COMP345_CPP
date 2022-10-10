#include "Player.h"
#include "Map.h"

using namespace std;

Player::Player()
{
    name = new string("");
    vector<Map::Territory>* territories;
    // vector<Card*> playerHand;
    // vector<Order*> ordersIssued;
}

Player::~Player(){
    name = nullptr;
    delete name;
    territories = nullptr;
    delete territories;
}

// Player::Player(string playerName, vector<Map::Territory*> territoriesOwned, vector<Card*> playerHand, vector<Order*> ordersIssued) 
// {
//     *name = playerName;
//     *territory = territoriesOwned;
//     *hand = playerHand;
//     *orders = ordersIssued;
// } 

Player::Player(const Player& p)
{
    this->name = new string(*(p.name)); 
}
    

vector<Map::Territory> toDefend() 
{
    //returns an arbitrary list of territories to defend
    vector<Map::Territory> defenceList;
    string territoryName = "Defence Territory";
    // Map::Territory mt = Map::Territory(territoryName);
    // defenceList.push_back(mt); //have this refer to global var
    return defenceList;
}

vector<Map::Territory> toAttack() 
{
    //returns an arbitrary list of territories to attack
    vector<Map::Territory> attackList;
    string territoryName = "Attack Territory";
    // Map::Territory mt = Map::Territory(territoryName);
    // attackList.push_back(mt);

    return attackList ;
}

void issueOrder(string order)
{
    // Order a = Order(order);
    //orders->push_back();
}
