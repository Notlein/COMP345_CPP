#pragma once
#include <iostream>
#include <queue>

using namespace std;

/*
	BASE CLASS : ORDERS
*/

class Orders {

public:
	// Constructors ---------
	Orders(); // default constructor
	Orders(const Orders& theOrder); //copy constructor
									
	// Assignment operator
	virtual Orders& operator=(const Orders& theOrder); 
	
	// Methods --------------
	virtual bool validate(); // validates the orders to ensure that it's a valid order
	virtual void execute(); // executes the order + output the description of the execution

	Orders(std::string orderType); // setting up the type of the Order
	std::string getType() const; // Accessor that gets the type of the Order
	string* _currentState;

private:
	// Stream Insertion Operator
	friend std::ostream& operator << (std::ostream& desc, const Orders& theOrder);
	// Order type
	std::string* _orderType;
};

/*
	SUBCLASS : DEPLOY
*/

class Deploy :public Orders {

public:
	// Constructors ----------------
	Deploy(); // default constructor
	Deploy(const Deploy& toDep); // copy constructor

	// Assignment Operator ---------
	virtual Deploy& operator=(const Deploy& toDep);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Deploy& deploy);
};

/*
	SUBCLASS : ADVANCE
*/

class Advance :public Orders {

public:
	// Constructors ----------------
	Advance(); // default constructor
	Advance(const Advance& toAdv); // copy constructor

	// Assignment Operator ---------
	virtual Advance& operator=(const Advance& toAdv);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Advance& deploy);
};

/*
	SUBCLASS : BOMB
*/

class Bomb :public Orders {

public:
	// Constructors ----------------
	Bomb(); // default constructor
	Bomb(const Bomb& toAdv); // copy constructor

	// Assignment Operator ---------
	virtual Bomb& operator=(const Bomb& toAdv);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Bomb& deploy);
};

/*
	SUBCLASS : BLOCKADE
*/

class Blockade :public Orders {

public:
	// Constructors ----------------
	Blockade(); // default constructor
	Blockade(const Blockade& toAdv); // copy constructor

	// Assignment Operator ---------
	virtual Blockade& operator=(const Blockade& toAdv);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Blockade& deploy);
};

/*
	SUBCLASS : AIRLIFT
*/

class Airlift :public Orders {

public:
	// Constructors ----------------
	Airlift(); // default constructor
	Airlift(const Airlift& toAdv); // copy constructor
	
	// Assignment Operator ---------
	virtual Airlift& operator=(const Airlift& toAdv);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Airlift& deploy);
};

/*
	SUBCLASS : NEGOTIATE
*/

class Negotiate :public Orders {

public:
	// Constructors ----------------
	Negotiate(); // default constructor
	Negotiate(const Negotiate& toAdv); // copy constructor

	// Assignment Operator ---------
	virtual Negotiate& operator=(const Negotiate& toAdv);

	// Methods ---------------------
	bool validate(); // validates the orders to ensure that it's a valid order
	void execute(); // executes the order + output the description of the execution

private:
	// Stream Insertion Operator ---
	friend std::ostream& operator << (std::ostream& desc, const Negotiate& deploy);
};

class OrderList {

public:
	// Constructors ----------------
	OrderList(); // default constructor
	OrderList(const OrderList& list); // copy constructor

	// Assignment Operator ---------
	OrderList& operator=(const OrderList& list);

	// Methods ---------------------
	void remove();
	void move();

	int size(); // accessor to get the size of the list

	std::queue<Orders*>& get_order_list();

private:
	std::queue<Orders*>* _theList;
	friend std::ostream& operator << (std::ostream& out, const OrderList& list);
};