#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include <string>
#include <algorithm>
using namespace std;



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

vector<Territory*>* Player::toAttack(){
    vector<Territory*>* attackList = new vector<Territory*>();
	
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
}

vector<Territory*> * Player::toDefend() {
    return this->territories;
}

void Player::issueOrder() {
    // Order *o = new Order();
    // orders->add(o);

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

void Player::add_territory(Territory * t) {
    this->territories->push_back(t);
}



// void Player::remove_territory(Territory * t) {
//     territories->erase(remove(territories->begin(), territories->end(), t), territories->end());
// }
