#pragma once
#include <iostream>
#include <queue>


using namespace std;

// forward declaration
class Territory;
class Player;

// ----------------------base class----------------

class Order {

	protected:
		bool if_executed;
		string effect;
		Player * owner;

	public:
		// Constructors ---------
		// default constructor
		Order();	
		~Order();
		Order(Player * owner);	
		// copy constructor					
		Order(const Order &o); 
		// Assignment operator
		Order &operator=(const Order &o); 		
		// stream insertion operator
		friend std::ostream &operator<<(std::ostream &out, const Order &o);

		// Methods --------------
		// validates the orders to ensure that it's a valid order
		virtual bool validate() = 0; 
		// executes the order + output the description of the execution
		virtual void execute() = 0;	
};

// ----------------------Deploy----------------

class Deploy : public Order {
	private:
		int my_num_army;
		Territory * my_target;


	public:
		// Constructors ----------------
		Deploy();
		~Deploy();
		Deploy(Player * owner, int num_army, Territory * target);	
		// copy constructor
		Deploy(const Deploy & d);
		// assignment operator
		Deploy &operator=(const Deploy &d);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Deploy &d);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	


};

// ----------------------Advance----------------

class Advance : public Order {
	private:
		int my_num_army;
		Territory * source;
		Territory * target;

	public:
		// Constructors ----------------
		Advance();
		~Advance();
		Advance(Player * owner, int num_army, Territory * source, Territory * target);	
		// copy constructor		   
		Advance(const Advance &a); 
		// Assignment Operator 
		Advance &operator=(const Advance &a);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Advance &a);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	

};

// ----------------------Airlift----------------

class Airlift : public Order {
	private:
		int my_num_army;
		Territory * source;
		Territory * target;
	public:
		// Constructors ----------------
		Airlift();
		~Airlift();
		Airlift(Player *owner, int my_num_army, Territory * source, Territory * target);		
		// copy constructor		   
		Airlift(const Airlift &a); 
		// Assignment Operator ---------
		Airlift &operator=(const Airlift &a);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Airlift &a);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	

};

// ----------------------Bomb----------------
class Bomb : public Order {
	private:
		Territory * target;
	public:
		// Constructors ----------------
		Bomb();	
		~Bomb();
		Bomb(Player *owner, Territory * target);	
		// copy constructor		   
		Bomb(const Bomb &b); 
		// Assignment Operator ---------
		Bomb &operator=(const Bomb &b);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Bomb &b);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	
};

// ----------------------Blockade----------------

class Blockade : public Order {
	private:
		Territory * target;
	public:
		// Constructors ----------------
		Blockade();	
		~Blockade();
		Blockade(Player *owner, Territory * target);	
		// copy constructor		   
		Blockade(const Blockade &b); 
		// Assignment Operator ---------
		Blockade &operator=(const Blockade &b);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Blockade &b);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	
};



// ----------------------Negotiate----------------

class Negotiate : public Order {
	private:
		Player * target;
	public:
		// Constructors ----------------
		Negotiate();	
		~Negotiate();
		Negotiate(Player *owner, Player * target);
		// copy constructor		   
		Negotiate(const Negotiate &n);
		// Assignment Operator ---------
		Negotiate &operator=(const Negotiate &n);
		// stream insertion operator
		friend ostream &operator<<(ostream &out, const Negotiate &n);

		// Methods ---------------------
		// validates the orders to ensure that it's a valid order
		bool validate(); 
		// executes the order + output the description of the execution
		void execute();	 
};

class OrdersList {
	public:
		// default constructor
		OrdersList();					  
		// copy constructor
		OrdersList(const OrdersList& ol);
		~OrdersList();

		// Methods ---------------------
		void remove(int pos);
		void move(int new_pos, int prev_pos);
		void add(Order *o);

	private:
		vector<Order *> *my_ol;


};

