#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


//	------------------ Order --------------------------

// Default Constructor
Order::Order() { 	
	this->if_executed = false;
	this->effect = "no effect";
	this->owner = nullptr;
}
// Parameterized Constructor
Order::Order(Player * owner) {
	this->if_executed = false;
	this->effect = "no effect";
	this->owner = owner;
}

// Destructor
Order::~Order() {}

// Copy Constructor
Order::Order(const Order &o) { 
	this->if_executed = o.if_executed;
	this->effect = o.effect;
	this->owner = o.owner;
}

// Assignment Operator ---------
Order &Order::operator=(const Order &o) {
	this->if_executed = o.if_executed;
	this->effect = o.effect;
	this->owner = o.owner;
	return *this;
}

// Stream insertion operator
ostream &operator<<(ostream &out, const Order &o) {
	return out << "Base order:" << endl 
	<< "is_executed: " << o.if_executed << endl
	<< "effect: " << o.effect << endl;
}


//	------------------ Deploy ------------------ 
// Default Constructor
Deploy::Deploy() : Order(), my_num_army(0), my_target(nullptr){}

// Parameterized Constructor
Deploy::Deploy(Player * owner, int num_army, Territory * target) : Order(owner), my_num_army(num_army), my_target(target) {}

// Destructor
Deploy::~Deploy() {}

// Copy constructor
Deploy::Deploy(const Deploy& d):Order(d){
	this->my_num_army = d.my_num_army;
	this->my_target = new Territory(*d.my_target);
}

// Assignment Operator 
Deploy &Deploy::operator=(const Deploy &d) {
	Order::operator=(d);
	this->my_num_army = d.my_num_army;
	this->my_target = new Territory(*d.my_target);
	return *this;
}

// Stream insertion operator
ostream &operator<<(ostream &out, const Deploy &d) {
	return out << "Deploy order:" << endl 
	<< "is_executed: " << d.if_executed << endl
	<< "effect: " << d.effect << endl;
}

// Methods ---------------------
bool Deploy::validate() {
	// checks if the terryitory belongs to the player that issued the order
	return owner->territory_belong(my_target);	
}

void Deploy::execute() {
	// adds the selected number of army units from the reinforcement pool to the target territory
	// if the target territory belongs to the player
	if (validate()) {
		*(my_target->nbArmies) = *(my_target->nbArmies) + my_num_army;
		// remove the selected number of army units from the reinforcement pool after it is added to the territory
		owner->set_reinforcement(owner->get_reinforcement()-my_num_army);
		if_executed = true;
		effect = to_string(my_num_army) + " armies have been added to territory " + *my_target->Tname;
		cout << effect << endl;
	} else {
		// the order is invalid if the target territory does not belong to the player
		cout << "invalid deploy:" << *my_target->Tname << " doesn't belong to player " << owner->getName() << endl;
	}

}

//	------------------ Advance ------------------ 

// Default Constructor
Advance::Advance() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}

// Parameterized Constructor
Advance::Advance(Player * owner, int num_army, Territory * source, Territory * target) : Order(owner), my_num_army(num_army), source(source), target(target){}

// Destructor
Advance::~Advance() {}

Advance::Advance(const Advance& a):Order(a){
	this->my_num_army = a.my_num_army;
	this->source = new Territory(*a.source);
	this->target = new Territory(*a.target);
}

// Assignment Operator ---------
Advance &Advance::operator=(const Advance &a) {
	Order::operator=(a);
	this->my_num_army = a.my_num_army;
	this->source = new Territory(*a.source);
	this->target = new Territory(*a.target);
	return *this;
}

ostream &operator<<(ostream &out, const Advance &a) {
	return out << "Advance order:" << endl 
	<< "is_executed: " << a.if_executed << endl
	<< "effect: " << a.effect << endl;
}

// Methods ---------------------
bool Advance::validate() {
	// check if cannot attack (negotiated)
	if (!owner->if_can_attack(target->getOwner())) {
		cout << "invalid advance: previous negotiation between " << owner->getName() << " and " << target->getOwner()->getName() << endl;
		return false;
	}

	// check if source territory belongs to the order owner
	if (!owner->territory_belong(source)) {
		cout << "invalid advance: territory " << source->getName() << " doesn't belong to player " << owner->getName() << endl;
		return false;
	} 

	// check if source and target are adjacent
	vector<string> src_adj = source->getAdjacentTerritories();
	string tgt_name = target->getName();
	if (find(src_adj.begin(), src_adj.end(), tgt_name) == src_adj.end()) {
		cout << "invalid advance: territory " << tgt_name << " and " << "territory "<< source->getName() << " are not adjacent " << endl;
        return false;
    }

	return true;
}

void Advance::execute() {
	if (validate()) {
		// If the source and target territory both belong to the player
		if (owner->territory_belong(target)) {
			target->setNbArmies(target->getNbArmies() + my_num_army);
			source->setNbArmies(source->getNbArmies() - my_num_army);
			if_executed = true;
			effect = to_string(my_num_army) + " amies was moved from territory " + source->getName() + " to " + target->getName();
			cout << effect << endl;
		} else { 
			// target territory belongs to another player, attack
			source->setNbArmies(source->getNbArmies() - my_num_army);
			while (my_num_army > 0  && target->getNbArmies() > 0) {
				if ((rand() % 10) < 6) {
					target->setNbArmies(target->getNbArmies() - 1);
				}
				if ((rand() % 10) < 7) {
					my_num_army -= 1;
				}
			}
			// defender's army units are eliminated, the attacker captures the territory
			if (target->getNbArmies() == 0) {
				target->setOwner(owner);
				target->setNbArmies(my_num_army);
				// draw a card if player haven't receive card for thisturn

				effect = "attacking player " + source->getOwner()->getName() + " won the attack, with " + to_string(my_num_army) + " armies remaining.";
				if (!target->getOwner()->get_received_card()) {
					target->getOwner()->set_received_card(true);
					// owner->player_draw_card();
					effect += "player will receive a card at the end of his turn";

				} else {
					effect += "player has already conquered at least one territory";
				}
				cout << effect << endl;
			} else {
				effect = "defending player " + target->getOwner()->getName() + " won the attack, with " + to_string(target->getNbArmies()) <+ " armies remaining";
				cout << effect << endl;
			}
			if_executed = true;
		}
	}
}


//	------------------ Airlift ------------------ 

// Default Constructor
Airlift::Airlift() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}

// Parameterized Constructor
Airlift::Airlift(Player *owner, int my_num_army, Territory * source, Territory * target): Order(owner), my_num_army(my_num_army), source(source), target(target){}

// Destructor
Airlift::~Airlift() {}

Airlift::Airlift(const Airlift& a):Order(a){
	this->my_num_army = a.my_num_army;
	this->source = new Territory(*a.source);
	this->target = new Territory(*a.target);
}

ostream &operator<<(ostream &out, const Airlift &a) {
	return out << "Airlift order:" << endl 
	<< "is_executed: " << a.if_executed << endl
	<< "effect: " << a.effect << endl;
}

// Assignment Operator ---------
Airlift &Airlift::operator=(const Airlift &a) {
	Order::operator=(a);
	this->my_num_army = a.my_num_army;
	this->source = new Territory(*a.source);
	this->target = new Territory(*a.target);
	return *this;
}

// Methods ---------------------
bool Airlift::validate() {
	// check if source or target territory does not belong to the player
	if (!owner->territory_belong(source)) {
		cout << "invalid airlift, source territory " << source->getName() << " doesn't belong to player " << owner->getName() << endl;
		return false;
	} 
	if (!owner->territory_belong(target)) {
		cout << "invalid airlift, target territory " << target->getName() << " doesn't belong to player " << owner->getName() << endl;
		return false;
	} 
	return true;
}

void Airlift::execute() {
	if (validate()) {
		// selected number of army units is moved from the source to the target territory
		source->setNbArmies(source->getNbArmies() - my_num_army);
		target->setNbArmies(target->getNbArmies() + my_num_army);
		if_executed = true;
		effect = "moved " + to_string(my_num_army) + " armies from source territory " + source->getName() + " to target territory " + source->getName();
		cout << effect << endl;
	} 
}

//	------------------ Bomb ------------------ 

// Default Constructor
Bomb::Bomb() : Order(),target(nullptr) {}

// Parameterized Constructor
Bomb::Bomb(Player *owner, Territory * target): Order(owner), target(target){}

// Destructor
Bomb::~Bomb() {}

Bomb::Bomb(const Bomb& b):Order(b) {
	this->target = new Territory(*b.target);
}

// Assignment Operator ---------
Bomb &Bomb::operator=(const Bomb &b) {
	Order::operator=(b);
	this->target = new Territory(*b.target);
	return *this;
}

ostream &operator<<(ostream &out, const Bomb &b) {
	return out << "Bomb order:" << endl 
	<< "is_executed: " << b.if_executed << endl
	<< "effect: " << b.effect << endl;
}


// Methods ---------------------
bool Bomb::validate() {
	if (!owner->if_can_attack(target->getOwner())) {
		cout << "invalid bomb: previous negotiation between " << owner->getName() << " and " << target->getOwner()->getName() << endl;
		return false;
	} 
	if (owner->territory_belong(target)) {
		cout << "invalid bomb: target territory " << target->getName() << " belong to player " << owner->getName() << endl;
		return false;
	} 
	if (!owner->territory_adjacent(target)) {
		cout << "invalid bomb: target territory " << target->getName() << " is not adjacent to any territories belonging to player " << owner->getName() << endl;
		return false;
	} 
	return true;
}

void Bomb::execute() {
	if (validate()) {
		// half of the army units are removed from this territory
		target->setNbArmies(target->getNbArmies()/2);
		if_executed = true;
		effect = "bomb: " + to_string(target->getNbArmies()) + " armies were removed from territory " + target->getName();
		cout << effect << endl;
	}
}

//	------------------ Blockade ------------------ 

// Default Constructor
Blockade::Blockade() : Order(),target(nullptr) {}

// Parameterized Constructor
Blockade::Blockade(Player *owner, Territory * target): Order(owner), target(target) {}

// Destructor
Blockade::~Blockade() {}

Blockade::Blockade(const Blockade& b):Order(b){
	this->target = new Territory(*b.target);
}

// Assignment Operator ---------
Blockade &Blockade::operator=(const Blockade &b) {
	Order::operator=(b);
	this->target = new Territory(*b.target);
	return *this;
}

ostream &operator<<(ostream &out, const Blockade &b) {
	return out << "Blockade order:" << endl 
	<< "is_executed: " << b.if_executed << endl
	<< "effect: " << b.effect << endl;
}


// Methods ---------------------
bool Blockade::validate() {
	if (!owner->territory_belong(target)) {
		cout << "invalid blockade: target territory "  << target->getName() << " doesn't belong to player " << owner->getName() << endl;
		return false;
	}

	return true;
}

void Blockade::execute() {
	if (validate()) {
		// number of army units on the territory is doubled
		target->setNbArmies(target->getNbArmies()*2);
		// ownership of the territory is transferred
		target->setOwner(new Player());
		owner->remove_territory(target);
		if_executed = true;
		effect = "blockade: number of amies on territory " + target->getName() + " has been doubled, it now has " + to_string(target->getNbArmies()) 
					+ " armies, ownership transfer to a Neutral player";
		cout << effect << endl;
	}
}


//	------------------ Negotiate ------------------

// Default Constructor
Negotiate::Negotiate() : Order(), target(nullptr) {}

// Parameterized Constructor
Negotiate::Negotiate(Player *owner, Player * target): Order(owner), target(target){}

// Destructor
Negotiate::~Negotiate() {}

Negotiate::Negotiate(const Negotiate& n):Order(n){
	this->target = new Player(*n.target);
}


// Assignment Operator ---------
Negotiate &Negotiate::operator=(const Negotiate &n) {
	Order::operator=(n);
	this->target = new Player(*n.target);
	return *this;
}

ostream &operator<<(ostream &out, const Negotiate &n) {
	return out << "Negotiate order:" << endl 
	<< "is_executed: " << n.if_executed << endl
	<< "effect: " << n.effect << endl;
}


// Methods ---------------------
bool Negotiate::validate() {
	// If the target is the player issuing the order, then the order is invalid
	if (this->owner == target) {
		cout << "invalid negotiate: target is the player issuing the order" << endl;
		return false;
	}
	if (!owner->if_can_attack(target)) {
		cout << "invalid negotiate: previous negotiation between " << owner->getName() << " and " << target->getName() << endl;
		return false;
	}
	return true;
}

void Negotiate::execute() {
	if (validate()) {
		this->owner->add_no_attack(target);
		target->add_no_attack(this->owner);
		if_executed = true;
		effect = "negotiate: " + target->getName() + " and " + owner->getName() + " are added to each other's negotiated list";
		cout << effect << endl;
	} 
}

//	------------------ OrdersList ------------------ 
// Default Constructor
OrdersList::OrdersList() {
	vector<Order *> tmp;
	this->my_ol = &tmp;

}
OrdersList::OrdersList(const OrdersList& ol) {
	for (auto order : *ol.my_ol) {
		Deploy* d = dynamic_cast<Deploy*>(order);
		this->my_ol->push_back(new Deploy(*d));
	}
}

// Destructor
OrdersList::~OrdersList() {
	for (auto order : *my_ol) {
		delete order;
	}
	delete my_ol;
}

// Methods ---------------------
// position is zero indexed
void OrdersList::remove(int pos) {
	my_ol->erase(my_ol->begin()+pos);
}

void OrdersList::move(int new_pos, int prev_pos) {
	my_ol->insert (my_ol->begin() + new_pos, my_ol->at(prev_pos));
	my_ol->erase(my_ol->begin() +prev_pos);
}

void OrdersList::add(Order *o) {
	my_ol->push_back(o);
}

vector<Order *> OrdersList::get_OrderList(){

	return *my_ol;

}



