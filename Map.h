#pragma once

class Player;
class Cards;
class Orders;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

class Map
{
public:


	 // default constructor
	Map() ;
	Map(int *nbT, int *nbC, string *mapN);
	
        // copy constructor
	Map(const Map& map);

        // assignment operator
        Map& operator =(const Map& map);

        // stream insertion operator
        friend ostream& operator <<(ostream& out, const Map& map);

        // Destructor
		~Map();


		
	


	class Territory {
	public:
		// default constructor
		Territory();

		Territory(string* name, string* properties);	


		// copy constructor
		Territory(const Territory& territory);

		// assignment operator
		Territory& operator=(const Territory& territory);

		// stream insertion operator
		friend ostream& operator<<(ostream& out, const Territory& territory);

		// Destructor
		~Territory();

		
		string getOwner() ; /* must change to player*/
		int getNbArmies() ;

		vector<string> getAdjacentTerritories();
		string getName();

		int* nbArmies;
		string* owner;
		string* Tname;
		
		vector<string>* adjTerr;
	};

	class Continent {
	public:
		// default constructor
		Continent();

		Continent(string* name, int* pts, vector<Territory>* list_terr);

		// copy constructor
		Continent(const Continent& continent);

		// assignment operator
		Continent& operator=(const Continent& continent);

		// stream insertion operator
		friend ostream& operator<<(ostream& out, const Continent& continent);

		// Destructor
		~Continent();

		string getName();
		int getNbPts();


		string* Cname;
		int* nbPts;
		vector<Territory>* territories;
	};
	

	

	Map(vector<vector<string>> fileName);	

	/*Continent getContinent(Continent continent) const;*/
	int getNbContinents();
	bool validate();
	Continent getContinent(int* index);
	// void setMapName(string* input) {};
	/*vector<string> getTerritories(Continent continent) const; */
	
	
	

	static bool validateMap(); /* Safeguard here */


	int* nbContinents;
	string* mapName;
	vector<Continent>* continents;
	


};