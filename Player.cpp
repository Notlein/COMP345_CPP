#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include <string>
#include <algorithm>
using namespace std;

class Hand;

Player::Player() {
    vector<Territory *> *tmp1 = new vector<Territory *>;
    vector<Player *> *tmp2 = new vector<Player *>;
    this->name = "";
    this->reinforcement = 0;
    this->territories = tmp1;
    this->noAttack = tmp2;
    this->hand = new Hand();
    this->orders = new OrdersList();
    this->received_card = false;
}
Player::Player(string playerName) {
    vector<Territory *> *tmp1 = new vector<Territory *>;
    vector<Player *> *tmp2 = new vector<Player *>;
    this->name = playerName;
    this->reinforcement = 0;
    this->territories = tmp1;
    this->noAttack = tmp2;
    this->hand = new Hand();
    this->orders = new OrdersList();
    this->received_card = false;

}
OrdersList* Player::get_orders(){

    return orders;

}

Player::~Player() {
    for (auto territory : *territories) {
		delete territory;
	}
    for (auto p : *noAttack) {
		delete p;
	}
    delete territories;
    delete noAttack;

}

Player::Player(int reinforcement, string playerName, vector<Territory*> *territories,vector<Player*> *noAttack, Hand * hand, OrdersList * ol) {
    this->reinforcement = reinforcement;
    this->name = playerName;
    this->territories = territories;
    this->noAttack = noAttack;
    this->hand = hand;
    this->orders = ol;
    this->received_card = false;
}

Player::Player(const Player &p) {
    this->reinforcement = p.reinforcement;
    this->name = p.name;
    this->territories = p.territories;
    this->noAttack = p.noAttack;
    this->received_card = p.received_card;
    this->hand = new Hand(*(p.hand));
    this->orders = new OrdersList(*(p.orders));

}

ostream &operator<<(ostream &out, const Player &p) {
	out << "Player " << p.name << " have " << p.territories->size() << " territories " << endl;
    for (auto t : *p.territories) {
        cout << t->getName() << endl;
    }
    return out;
}

//vector<Territory*>* Player::toAttack(){
    //vector<Territory*>* attackList = new vector<Territory*>();
	
	// for (auto t : *this->territories) {
	// 	for (auto adjt : t->getAdjacentTerritories()) {
    //         bool own = false;
	// 		for (auto t2 : *this->territories) {
    //             if (t2->getName() == adjt) {
    //                 own = true;
    //             }
	// 	    }
    //         if (!own) {
    //             attackList
    //         }
	//     }
    // }
    //return NULL;
//}

//vector<Territory*> * Player::toDefend() {
    //return this->territories;
//}

vector<Territory*> * Player::toDefend(){

	vector<Territory*> * sortedToDefend =  territories;
	std::sort(sortedToDefend->begin(), sortedToDefend->end());
	return sortedToDefend;
		
}

vector<Territory*> * Player::toAttack(){

	vector<Territory*> * sortedToAttack;
	for (Territory * territory : *territories){

		for (string adjacent : territory->adjTerr*){

			//if(*(adjacent.owner) != this){

				//sortedToAttack->pushBack(adjacent);			

			//}

            bool isEnemy = true;

            for (Territory * territory : *territories){

                if (*(territory->Tname) == adjacent){

                    isEnemy = false;
                    break;

                }

            }

            if (isEnemy){

                sortedToAttack->pushBack(adjacent);

            }
			
		}

	}

	std::sort(sortedToAttack->begin(), sortedToAttack->end());
	return sortedToAttack;
	
}

string Player::getName() {
    return this->name;
}
void Player::set_received_card(bool v) {
    this->received_card = v;
 }

bool Player::get_received_card() {
    return received_card;
}

bool  Player::territory_belong(Territory * target) {
    if (find(territories->begin(), territories->end(), target) != territories->end()) {
        return true;
    }
    return false;
}

bool Player::territory_adjacent(Territory * target) {
    for (auto territory : *territories) {
        vector<string> src_adj = territory->getAdjacentTerritories();
        string tgt_name = target->getName();
        if (find(src_adj.begin(), src_adj.end(), tgt_name) != src_adj.end()) {
            return true;
        }
	}
    return false;
};

void Player::remove_territory(Territory * target) {
    vector<Territory *>::iterator position = find(territories->begin(), territories->end(), target);
    if (position != territories->end()) {
        territories->erase(position);
    }
};

void Player::add_no_attack(Player * p) {
    noAttack->push_back(p);
};

bool Player::if_can_attack(Player * p) {
    // if find, then cannot attack
    if (find(noAttack->begin(), noAttack->end(), p) != noAttack->end()) {
        return false;
    }
    return true; 
};

void Player::set_reinforcement(int i){
    this->reinforcement=i;
}

int Player::get_reinforcement(){
    return this->reinforcement;
}

// void Player::player_draw_card() {
//     string c = this->hand->draw();
// }


 void Player::issueOrder() {

     //for each turn, each player will deploy all of their available reinforcements
     //Hand *hand;
     while(reinforcement > 0 ){

         orders -> add(new Deploy);
         reinforcement--;

     }

     cout << name << "Has no more reinforcements to deploy\n";
     //for each turn, each player issues an order from one card in thier hand, if their hand is not empty.

    if(hand->get_numCardsHand() > 0){

         cout << name << "Is now issuing an order from a car in their hand: ";

         if (hand->arrHand[0] == " Airlift"){

             orders->add(new Airlift);
             //*hand[0].delete
             cout << name << " Airlift card\n";

         }

         else if (hand->arrHand[0] == "Bomb"){

             orders->add(new Bomb);
             //*hand[0].delete
             cout << name << " Bomb card\n";

         }

         else if (hand->arrHand[0] == "Blockade"){

             orders->add(new Blockade);
             //*hand[0].delete
             cout << name << " Blockade card\n";

         }

         else if (hand->arrHand[0] == "Negotiate"){

             orders->add(new Negotiate);
             //*hand[0].delete
             cout << name << " Negotiate card\n";

         }

         else{

             cout <<"There is an invalid card in the deck\n";

         }
    }

    //Finally, for each turn, each player issues one advance order.

    cout << name << "Is now issuing an advance order\n\n";
    orders->add(new Advance);

    cout << name <<"'s issue orders phase is complete for this turn\n\n========\n\n";
 }