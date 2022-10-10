#include "Map.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using std::cout;
using std::vector;



using namespace std;

Map::Map() : mapName(new string("empty map")){
	cout << "Map created" << endl;
};
Map::Map(int* nbT, int* nbC, string* mapN) : mapName(mapN)
{
	
	cout << "Map created" << endl;
};

Map::Map(vector<vector<string>> parsedFile){

	

	

	vector<Continent> m;
	
	for(int i=0;i<parsedFile.size();i++){
		string* n = new string(parsedFile[i][0]);
		int* p = new int(stoi(parsedFile[i][1]));
		vector<Territory> list_t;
		
		
		for(int j=2;j<parsedFile[i].size()-1;j+=2){
			string* tn= new string(parsedFile[i].at(j));
			string* props= new string(parsedFile[i].at(j+1));
			
			Territory t(tn,props);
			
			list_t.push_back(t);

		}
		
		// for(int k=0;k<list_t.size()-1;k++){
		// 	cout  << list_t.at(k);
		// }
		
		Continent c(n,p,new vector(list_t));
		

		m.push_back(c);
		c.~Continent();
		
	}

	continents = new vector(m);
	nbContinents = new int(m.size());	
	
}

// copy constructor
Map::Map(const Map& map) {

	this->mapName = new string(*(map.mapName));
	this->continents = new vector(*(map.continents));
};

// assignment operator
Map& Map::operator=(const Map& map) {

	this->mapName = new string(*(map.mapName));
	this->continents = new vector(*(map.continents));
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Map& map) {
	
	
	
	out << "Map name is " << *map.mapName << endl << "It has " << *map.nbContinents << " continents" << endl;
	return out;
}
Map::~Map() {
	delete mapName;
	mapName = nullptr;
	vector<Continent> v;
	continents = new vector(v);
	delete continents;
	continents = nullptr;
}

int Map::getNbContinents(){
	return *nbContinents;
}


bool Map::validate(){
bool status=true;
// for each continent
	for(int i=0; i<continents->size();i++){
		vector<Territory> v = *continents->at(i).territories;
		// cout << "Continent : "<< *continents->at(i).Cname << endl<<endl;

		// for each node Territory
		for(int j=0; j<v.size();j++){
			vector<string> v2 = *v.at(j).adjTerr;
				// cout << "Territory : " << *v.at(j).Tname <<endl <<endl << "Adjacent Territories : "<< endl;
				string a = *v.at(j).Tname;
				// verify if there's a duplicate within the continent
			for(int m=j+1;m<v.size();m++){
				
				string b = *v.at(m).Tname;
				if(a == b){
					status=false;
				}
			}
			// verification for each subsequent continents: 
			for(int n=i+1;n<continents->size();n++){
				// for each territory in the continent:
				for(int k=0;k<continents->at(n).territories->size();k++){
					string d = *continents->at(n).territories->at(k).Tname;
					//  if there's a duplicate
					if(a == d){
						// cout << a << " : " << d << endl;
					status=false;
					
					}
				}
			}
		}
		

		//verify if the continent is a connected subgraph (algorithm)
		for(int h=0;h<continents->at(i).territories->size();h++){
			// Nodes are unvisited
			vector<bool> visited(continents->at(i).territories->size(),false);
			int counter = 0;
			for(int l=0;l<continents->at(i).territories->size();l++){
				
				//if not visited, new component
				if ( !visited[l] ) { // Process the component that contains v.
					counter++;
					
					queue<Territory> q; // For implementing a breadth-first traversal.
					q.push(continents->at(i).territories->at(l)); // Start the traversal from vertex v.
					visited[l] = true;
					while ( !q.empty() ) {
						Territory w = q.front();// w is a node in this component.
						q.pop(); 
						// cout << w << " ";
						// each edge from w to some vertex z
						for(string z : *w.adjTerr )  {
							for(int y=0;y<continents->at(i).territories->size();y++){
								string nameT = *continents->at(i).territories->at(y).Tname;
								int connection = 0;
								if(nameT == z){
									connection = y;
								}
								
								if ( !visited[connection] ) {
								// We’ve found another node in this component.
								visited[connection] = true;
								q.push(continents->at(i).territories->at(connection));
								}
							}
						}
					}
				}
			}
			if(counter != 1){
				
				status=false;
			}	
		}
		
	}


	// third function for connected graph validation to do
	status = true;

	return status;	
}
// }
/// <summary>
/// Territory inner class constructor
/// </summary>
Map::Territory::Territory() {
	int* a = new int(0);
	string* o = new string("not owned");
	string* Tn = new string("");
	vector<string>* adjT = new vector<string>;
	nbArmies=a;
	owner=o;
	Tname = Tn;
	adjTerr=adjT;
};

Map::Territory::Territory(string* name, string* properties) {
	int* a = new int(0);
	string* o = new string("not owned");
	string* Tn = new string(*name);
	vector<string> adjT;
	string* s = new string(*properties);
	for(int i = 0; i<3;i++){
		s = new string(s->substr(s->find(',')+1,s->size()));
	}
	s = new string(s->substr(0,s->size()));
	

	istringstream ss(*s);
	while( ss.good() )
{
    string substr;
    getline( ss, substr, ',' );
	if(substr.at(0) == ' '){
		substr = substr.substr(1, substr.size());
	}
    adjT.push_back( substr );
}
	nbArmies=a;
	owner=o;
	Tname = Tn;
	adjTerr=new vector<string>(adjT);
	
};
// copy constructor
Map::Territory::Territory(const Territory& territory) {
	this -> nbArmies = new int(*(territory.nbArmies));
	this -> owner = new string(*(territory.owner));
	this -> Tname = new string(*(territory.Tname));
	this->adjTerr = new vector<string>(*(territory.adjTerr));
	
};

// assignment operator
Map::Territory& Map::Territory::operator=(const Map::Territory& territory) {
	this->nbArmies = new int(*(territory.nbArmies));
	this->owner = new string(*(territory.owner));
	this->Tname = new string(*(territory.Tname));
	this->adjTerr = new vector<string>(*(territory.adjTerr));
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Map::Territory& territory) {
	out << "Territory name is " << *territory.Tname << endl << "The owner is : " << *territory.owner << endl << "and it has an army of size" << *territory.nbArmies << endl;
	return out;
	
}

Map::Territory::~Territory() {
	delete owner;
	owner = nullptr;
	delete nbArmies;
	nbArmies = nullptr;
	delete Tname;
	Tname = nullptr;
	delete adjTerr;
	adjTerr = nullptr;
	
}

vector<string> Map::Territory::getAdjacentTerritories(){
	return *adjTerr;
}

/// <summary>
/// Continent inner class constructor
/// </summary>
Map::Continent::Continent() {
	string* Cn = new string("");
	int* cP = new int(0);
	vector<Territory>* t = new vector<Territory>;
	Cname = Cn;
	nbPts = cP;
	territories = t;
};

Map::Continent::Continent(string* name, int* pts, vector<Territory>* list_terr) {
	this->Cname = new string(*name);
	this->nbPts = new int(*pts);
	this->territories = new vector<Territory>(*list_terr);
	
};
// copy constructor
Map::Continent::Continent(const Continent& continent) {
	this->Cname = new string(*(continent.Cname));
	this->nbPts = new int(*(continent.nbPts));
	this->territories = new vector<Territory>(*(continent.territories));

};

// assignment operator
Map::Continent& Map::Continent::operator=(const Map::Continent& continent) {
	this->Cname = new string(*(continent.Cname));
	this->nbPts = new int(*(continent.nbPts));
	this->territories = new vector<Territory>(*(continent.territories));
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Map::Continent& continent) {
	out << "Continent name is " << *continent.Cname << endl << "The player the owns the continent scores " << *continent.nbPts << " points" << endl << "and its territories are : insert territories iterator here" << endl;
	return out;
}

Map::Continent::~Continent() {
	Cname = nullptr;
	delete Cname;
	nbPts = nullptr;
	delete nbPts;
	territories = nullptr;
	delete territories;
	
}



