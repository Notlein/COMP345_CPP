#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Territory;
class Hand;
class OrdersList;

class Player {
public:
    Player();  // default constructor
    ~Player(); // destructor
    Player(string playerName);
    Player(int reinforcement, string playerName, vector<Territory*> *territories, vector<Player*> *noAttack, const Hand & hand, const OrdersList & ol);
    Player(const Player &p); // copy constructor
    friend ostream &operator<<(ostream &out, const Player &player);


    vector<Territory*> * toDefend();
    vector<Territory*> * toAttack();
    void issueOrder();

    // vector<Orders *> getOrderList();
    // void printOrder();
    string getName();
    bool territory_belong(Territory * target);
    bool territory_adjacent(Territory * target);
    void remove_territory(Territory * target);
    void add_no_attack(Player * p);
    bool if_can_attack(Player * p);
    void set_received_card(bool v);
    

private:
    string name;
    int reinforcement;
    vector<Territory*> *territories;
    vector<Player*> *noAttack;
    Hand * hand;
    OrdersList * orders;
    bool received_card;
};
