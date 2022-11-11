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
	this->owner = new Player();
}

Order::Order(Player * owner) {
	this->if_executed = false;
	this->effect = "";
	this->owner = owner;
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

Deploy::Deploy(Player * owner, int num_army, Territory * target) : Order(owner), my_num_army(num_army), my_target(target) {}

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
		cout << my_num_army << " armies have been added to territory " << *my_target->Tname << endl;
	} else {
		cout << "validation failed, invalid deploy" << endl;
	}

}

//	------------------ Advance ------------------ 

// Constructors ----------------
Advance::Advance() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}
Advance::Advance(Player * owner, int num_army, Territory * source, Territory * target) : Order(owner), my_num_army(num_army), source(source), target(target){}

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
	// check if cannot attack (negotiated)
	if (!owner->if_can_attack(target->getOwner())) {
		cout << "invalid advance: negotiated between " << owner->getName() << " and " << target->getOwner()->getName() << endl;
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
			cout << my_num_army << " amies was moved from territory  " << source->getName() << " to " << target->getName() << endl;
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
				target->getOwner()->set_received_card(true);
				cout << "attacking player " << source->getOwner()->getName() << " won the attack, with " << my_num_army << " armies remaining" << endl;
			 } else {
				cout << "defending player " << target->getOwner()->getName() << " won the attack, with " << target->getNbArmies() << " armies remaining" << endl;
			 }
		}
	}
}


//	------------------ Airlift ------------------ 

// Constructors ----------------
Airlift::Airlift() : Order(), my_num_army(0), source(nullptr), target(nullptr) {}
Airlift::Airlift(Player *owner, int my_num_army, Territory * source, Territory * target): Order(owner), my_num_army(my_num_army), source(source), target(target){}

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
		cout << "moved " << my_num_army << " armies from source territory " << source->getName() << " to target territory " << source->getName()<< endl;
	} 
}

//	------------------ Bomb ------------------ 

// Constructors ----------------
Bomb::Bomb() : Order(),target(nullptr) {}

Bomb::Bomb(Player *owner, Territory * target): Order(owner), target(target){}

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
	if (!owner->if_can_attack(target->getOwner())) {
		cout << "invalid bomb: negotiated between " << owner->getName() << " and " << target->getOwner()->getName() << endl;
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
		cout << "bomb: " << target->getNbArmies() << " armies were removed from territory " << target->getName() << endl;
	}
}

//	------------------ Blockade ------------------ 

// Constructors ----------------
Blockade::Blockade() : Order(),target(nullptr) {}
Blockade::Blockade(Player *owner, Territory * target): Order(owner), target(target){}

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
	if (!owner->territory_belong(target)) {
		cout << "invalid blockade: territory "  << target->getName() << " belongs to enemy of player " << owner->getName() << endl;
		return false;
	}

	return true;
}

void Blockade::execute() {
	if (validate()) {
		// number of army units on the territory is doubled
		target->setNbArmies(target->getNbArmies()*2);
		// ownership of the territory is transferred
		owner->remove_territory(target);
	}
}


//	------------------ Negotiate ------------------

// Constructors ----------------
Negotiate::Negotiate() : Order(), target(nullptr) {}
Negotiate::Negotiate(Player *owner, Player * target): Order(owner), target(target){}

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
	if (this->owner == target) {
		cout << "invalid negotiate: target is the player issuing the order" << endl;
		return false;
	}
	if (!owner->if_can_attack(target)) {
		cout << "invalid negotiate: negotiated" << endl;
		return false;
	}
	return true;
}

void Negotiate::execute() {
	if (validate()) {
		this->owner->add_no_attack(target);
		target->add_no_attack(this->owner);
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



