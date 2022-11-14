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
    Player(int reinforcement, string playerName, vector<Territory*> *territories, vector<Player*> *noAttack, Hand * hand, OrdersList * ol);
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
    bool get_received_card();
    void set_reinforcement(int i);
    int get_reinforcement();
    void add_territory(Territory * t);
    // void remove_territory(Territory * t);
    // void player_draw_card();

private:
    string name;
    int reinforcement;
    vector<Territory*> *territories;
    vector<Player*> *noAttack;
    Hand * hand;
    OrdersList * orders;
    bool received_card;
};
