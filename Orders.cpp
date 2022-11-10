#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


//	------------------ Order --------------------------

// Defualt Constructor
Order::Order() { 	
	this->if_executed = false;
	this->effect = "";
	this->owner = NULL;
}

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
	return out << "This is a base order with effect " << endl;
}


//	------------------ Deploy ------------------ 
// default constructor
Deploy::Deploy() : Order(), my_num_army(0), my_target(NULL){}

// copy constructor
Deploy::Deploy(const Deploy& d):Order(d){
	this->my_num_army = d.my_num_army;
	this->my_target = new Territory(*d.my_target);
}

// Assignment Operator ---------
Deploy &Deploy::operator=(const Deploy &d) {
	Order::operator=(d);
	this->my_num_army = d.my_num_army;
	this->my_target = new Territory(*d.my_target);
	return *this;
}

// Methods ---------------------
bool Deploy::validate() {
	return owner->territory_belong(my_target);	
}

void Deploy::execute() {
	if (validate()) {
		*(my_target->nbArmies) = *(my_target->nbArmies) + my_num_army;
		if_executed = true;
	} else {
		cout << "invalid deploy" << endl;
	}

}

//	------------------ Advance ------------------ 

// Constructors ----------------
Advance::Advance() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}

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

// Methods ---------------------
bool Advance::validate() {
	// check if source territory belongs to the order owner
	if (!owner->territory_belong(source)) {
		return false;
	} 
	// check if cannot attack (negotiated)
	if (!owner->territory_belong(target) && !owner->if_can_attack(target->getOwner())) {
		return false;
	}
	// check if source and target are adjacent
	vector<string> src_adj = source->getAdjacentTerritories();
	string tgt_name = target->getName();
	if (find(src_adj.begin(), src_adj.end(), tgt_name) == src_adj.end()) {
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
		} else { // target territory belongs to another player, attack
			source->setNbArmies(source->getNbArmies() - my_num_army);
			while (my_num_army > 0  && target->getNbArmies() > 0) {
				bool attack_kill = (rand() % 10) < 6;
				bool defend_kill = (rand() % 10) < 7;
				if (attack_kill && defend_kill) {
					my_num_army -= 1;
					target->setNbArmies(target->getNbArmies() - 1);
				} else if (attack_kill) {
					target->setNbArmies(target->getNbArmies() - 1);
				} else if (defend_kill) {
					my_num_army -= 1;
				}
			 }
			 // defender's army units are eliminated, the attacker captures the territory
			 if (target->getNbArmies() == 0) {
				target->setOwner(owner);
				target->setNbArmies(my_num_army);
			 }
		}
	} else {
		cout << "invalid advance" << endl;
	}
}


//	------------------ Airlift ------------------ 

// Constructors ----------------
Airlift::Airlift() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}

Airlift::Airlift(const Airlift& a):Order(a){
	this->my_num_army = a.my_num_army;
	this->source = new Territory(*a.source);
	this->target = new Territory(*a.target);
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
	if (!owner->territory_belong(source) || !owner->territory_belong(target)) {
		return false;
	} 
	return true;
}

void Airlift::execute() {
	if (validate()) {
		// selected number of army units is moved from the source to the target territory
		source->setNbArmies(source->getNbArmies() - my_num_army);
		target->setNbArmies(target->getNbArmies() + my_num_army);
	} else {
		cout << "invalid airlift" << endl;
	}
}

//	------------------ Bomb ------------------ 

// Constructors ----------------
Bomb::Bomb() : Order(),target(nullptr) {}

Bomb::Bomb(const Bomb& b):Order(b) {
	this->target = new Territory(*b.target);
}

// Assignment Operator ---------
Bomb &Bomb::operator=(const Bomb &b) {
	Order::operator=(b);
	this->target = new Territory(*b.target);
	return *this;
}

// Methods ---------------------
bool Bomb::validate() {
	return (!owner->territory_belong(target) && owner->territory_adjacent(target) && owner->if_can_attack(target->getOwner()));
}

void Bomb::execute() {
	if (validate()) {
		// half of the army units are removed from this territory
		target->setNbArmies(target->getNbArmies()/2);
	} else {
		cout << "invalid bomb" << endl;
	}
}

//	------------------ Blockade ------------------ 

// Constructors ----------------
Blockade::Blockade() : Order(),target(nullptr) {}

Blockade::Blockade(const Blockade& b):Order(b){
	this->target = new Territory(*b.target);
}

// Assignment Operator ---------
Blockade &Blockade::operator=(const Blockade &b) {
	Order::operator=(b);
	this->target = new Territory(*b.target);
	return *this;
}

// Methods ---------------------
bool Blockade::validate() {
	return owner->territory_belong(target);
}

void Blockade::execute() {
	if (validate()) {
		// number of army units on the territory is doubled
		target->setNbArmies(target->getNbArmies()*2);
		// ownership of the territory is transferred
		owner->remove_territory(target);
	} else {
		cout << "invalid blockade" << endl;
	}
}


//	------------------ Negotiate ------------------

// Constructors ----------------
Negotiate::Negotiate() : Order(), target(nullptr) {}

Negotiate::Negotiate(const Negotiate& n):Order(n){
	this->target = new Player(*n.target);
}


// Assignment Operator ---------
Negotiate &Negotiate::operator=(const Negotiate &n) {
	Order::operator=(n);
	this->target = new Player(*n.target);
	return *this;
}


// Methods ---------------------
bool Negotiate::validate() {
	// If the target is the player issuing the order, then the order is invalid
	return this->owner == target && owner->if_can_attack(target);
}

void Negotiate::execute() {
	if (validate()) {
		this->owner->add_no_attack(target);
		target->add_no_attack(this->owner);
	} else {
		cout << "invalid negotiate" << endl;
	}
}

//	------------------ OrdersList ------------------ 

// Constructors ----------------
OrdersList::OrdersList() {
	vector<Order *> my_ol;
}
OrdersList::OrdersList(const OrdersList& ol) {
	for (auto order : ol.my_ol) {
		Deploy* d = dynamic_cast<Deploy*>(order);
		this->my_ol.push_back(new Deploy(*d));
	}
}
OrdersList::~OrdersList() {
	for (auto order : my_ol) {
		delete order;
	}
}

// Methods ---------------------
// position is zero indexed
void OrdersList::remove(int pos) {
	my_ol.erase(my_ol.begin()+pos);
}

void OrdersList::move(int new_pos, int prev_pos) {
	my_ol.insert (my_ol.begin() + new_pos, my_ol.at(prev_pos));
	my_ol.erase(my_ol.begin() +prev_pos);
}

void OrdersList::add(Order *o) {
	my_ol.push_back(o);
}



