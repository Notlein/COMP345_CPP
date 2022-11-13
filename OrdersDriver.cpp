#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;

vector<vector<string>> parseMap(ifstream& file) {
    
    string str = "";
    
    vector<vector<string>> arr_cont; /* [i][0]  -> continents ; [i][n] -> n > 0, Territoires d'un continent 'i' */
    // ifstream file("./maps/Grand Montreal.map");

    while (getline(file, str)) {

        if (str == "[Continents]") {
            // scan lines for continentName=points
            while (getline(file, str) && str != "[Territories]") {
                if (str != "" && str != "\n") {
                    int found;

                    string temp2;
                    vector<string> temp;
                    string delimiter = "=";

                    temp2 = str.substr(0, str.find(delimiter));
                    temp.push_back(temp2);
                    temp2 = str.substr(str.find(delimiter) + 1, str.length() - 1); 
                    temp.push_back(temp2);
                    arr_cont.push_back(temp);
                }
            }
        }

        if (str == "[Territories]"){
            int index = 0;
            string delimiter2 = ",";
            string terrName;
            string terrProperties;

                while (getline(file, str)) {
                        // removal of spaces before and after commas
                        regex rgx("[ ]*[,][ ]*");
                        string replaced_by = ",";

                    if (str != "\r" && str != "" && str != "\n") {
                        terrName = str.substr(0, str.find(delimiter2));
                        terrProperties = str.substr(str.find(delimiter2) + 1, str.length() - 1);
                        terrProperties = regex_replace(terrProperties, rgx, replaced_by);
                        arr_cont.at(index).push_back(terrName);
                        arr_cont.at(index).push_back(terrProperties);
                    } else {
                        if(str != "\r" && str != "" && str != "\n"){
                            index++;
                        }
                    }
                }
        }
    }
    file.close();

    return arr_cont;
}

Continent testloadMaps() {

    string x = "./maps/Grand Montreal.map";

    ifstream file(x);
    vector<vector<string>> v = parseMap(file);

    
    // parse map name
    Map m(v);
    x = x.substr(7,x.length());
    x = x.substr(0,x.length()-4);
    m.mapName = new string(x);

    Continent c1 = m.continents->at(0);
    return c1;

}



int main() {
     // -------------- set up neccessary objects for testing ---------------
  
    Continent c1 = testloadMaps();
    // t1 and t2 are adjecent 
    // t1 and t3 are not adjacent
    Territory t1 = c1.territories->at(0); //Genda
    Territory t2 = c1.territories->at(3); //Gordonville
    Territory t3 = c1.territories->at(2); //Mirabel
    Territory t4 = c1.territories->at(11); 

    vector<Territory *> t11;
    t11.push_back(&t1);

    vector<Territory *> t22;
    t22.push_back(&t2);
    t22.push_back(&t3);
    t22.push_back(&t4);

    Hand hand1 = Hand();
    Hand hand2 = Hand();

    OrdersList ol1 = OrdersList();
    OrdersList ol2 = OrdersList();

    vector<Player *> pl1;
    vector<Player *> pl2;
 
    //Player(int reinforcement, string playerName, vector<Territory*> territories, vector<Player*> noAttack, const Hand & hand, const OrdersList & ol)
    Player player1 = Player(50, "p1", &t11, &pl1, &hand1, &ol1);
    Player player2 = Player(50, "p2", &t22, &pl2, &hand2, &ol2);

    t1.setOwner(&player1);
    t2.setOwner(&player2);
    t3.setOwner(&player2);
    t4.setOwner(&player2);

    cout << player1 << endl;
    cout << player2 << endl;
 
    cout << "testing deploy -------------------------------" << endl;
    //invalid case: Target territory does not belong to the player that issued the order
    Deploy d1 = Deploy(&player1, 5, &t2);	
    d1.execute();
    cout << d1 << endl;
    // valid case:  selected number of army units is added to the number of army units on that territory
    cout << t1 << endl;
    Deploy d2 = Deploy(&player1, 5, &t1);	
    d2.execute();
    cout << d2 << endl;
    cout << t1 << endl;

    cout << "testing advance -------------------------------" << endl;
    //invalid case: source territory does not belong to the player that issued the order
    Advance a1 = Advance(&player1, 5, &t2, &t2);
    a1.execute();
    cout << a1 << endl;
    //invalid case: target territory is not adjacent to the source territory
    Advance a2 = Advance(&player1, 5, &t1, &t3);
    a2.execute();
    cout << a2 << endl;
    //valid case: source and target territory both belong to the player that issued the order, the army units are moved from the source to the target territory.
    cout << t3 << endl;
    Advance a3 = Advance(&player2, 5, &t3, &t2);
    a3.execute();
    cout << a3 << endl;
    cout << t3 << endl;
    // valid case: attack
    cout << t2 << endl;
    Advance a4 = Advance(&player1, 5, &t1, &t2);
    a4.execute();
    cout << a4 << endl;
    cout << t2 << endl;

    cout << "testing airlift -------------------------------" << endl;
    //invalid case: source or target territory does not belong to the player that issued the order
    Airlift al1 = Airlift(&player1, 5, &t1, &t2);
    al1.execute();
    cout << al1 << endl;
    Airlift al2 = Airlift(&player1, 5, &t2, &t1);
    al2.execute();
    cout << al2 << endl;
    //valid case:  selected number of army units is moved from the source to the target territory
    Airlift al3 = Airlift(&player2, 5, &t3, &t2);
    cout << t2 << endl;
    cout << t3 << endl;
    al3.execute();
    cout << al3 << endl;
    cout << t2 << endl;
    cout << t3 << endl;

    cout << "testing bomb -------------------------------" << endl;
    //invalid case: target belongs to the player that issued the order
    Bomb b1 = Bomb(&player1, &t1);	
    b1.execute();
    cout << b1 << endl;
    //invalid case: target territory is not adjacent to one of the territory owned by the player issuing the order
    Bomb b2 = Bomb(&player1, &t4);	
    b2.execute();
    cout << b2 << endl;
    //valid case: half of the army units are removed from this territory.
    Bomb b3 = Bomb(&player1, &t2);	
    cout << t2 << endl;
    b3.execute();
    cout << b3 << endl;
    cout << t2 << endl;

    cout << "testing blockade -------------------------------" << endl;
    //invalid case:  target territory belongs to an enemy player
    Blockade bl1 = Blockade(&player1, &t4);
    bl1.execute();
    cout << bl1 << endl;
    // valid case:  the number of army units on the territory is doubled and the ownership of the territory is transferred to the Neutral player
    Blockade bl2 = Blockade(&player2, &t3);
    cout << t3 << endl;
    bl2.execute();
    cout << bl2 << endl;
    cout << t3 << endl;

    
    cout << "testing negotiate -------------------------------" << endl;
    // invalid case:  the target is the player issuing the order
    Negotiate n1 = Negotiate(&player1, &player1);
    n1.execute();
    cout << n1 << endl;
    // valid case
    Negotiate n2 = Negotiate(&player1, &player2);
    n2.execute();
    cout << n2 << endl;
    Advance a5 = Advance(&player1, 5, &t1, &t4);
    a5.execute();
    cout << a5 << endl;

    return 0;
}