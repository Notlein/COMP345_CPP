#include "Player.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

Player::Player()
{
    name = new string("");
    // vector<Map::Territory>* territories;
    // vector<Card*> playerHand;
    // vector<Order*> ordersIssued;
}

Player::~Player(){
    name = nullptr;
    delete name;
    // territories = nullptr;
    // delete territories;
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

void issueOrder()
{
    // Order a = Order(order);
    //orders->push_back();

    //for each turn, each player will deploy all of their available reinforcements

    while(*reinforcementPool > 0 ){

        orders.push_back(new Deploy);
        *reinforcementPool--;

    }

    cout << *name << "Has no more reinforcements to deploy\n";
    //for each turn, each player issues an order from one card in thier hand, if their hand is not empty.

    if(!*hand.empty()){

        cout << *name << "Is now issuing an order from a car in their hand: ";

        if (*(*hand[0].card_type) == "Airlift"){

            orders.push_back(new Airlift);
            //*hand[0].delete
            cout << *name << "Airlift card\n";

        }

        else if (*(*hand[0].card_type) == "Bomb"){

            orders.push_back(new Bomb);
            //*hand[0].delete
            cout << *name << "Bomb card\n";

        }

        else if (*(*hand[0].card_type) == "Blockade"){

            orders.push_back(new Blockade);
            //*hand[0].delete
            cout << *name << "Blockade card\n";

        }

        else if (*(*hand[0].card_type) == "Negotiate"){

            orders.push_back(new Negotiate);
            //*hand[0].delete
            cout << *name << "Negotiate card\n";

        }

        else{

            cout <<"There is an invalid card in the deck\n";

        }
    }

    //Finally, for each turn, each player issues one advance order.

    cout << *name << "Is now issuing an advance order\n\n";
    orders.push_back(new Advance);

    cout << *name <<"'s issue orders phase is complete for this turn\n\n========\n\n";
}
