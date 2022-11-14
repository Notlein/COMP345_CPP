#include "Map.h"
// #include "Player.h"

// deactivate below before submission
// #include "Map.cpp"
// #include "Player.cpp"


#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;


// function to parse the map file and normalize it.
// Known bugs: if a map has all its territories without double line breaks between continents, the map won't load.
// Also, if there is space at the end of a territory's name, 
// it won't recognize it as the same territory in the adj list of other territories. To be fixed with Regex
vector<vector<string> > parseMap(ifstream& file) {
    
    string str = "";
    
    vector<vector<string> > arr_cont; /* [i][0]  -> continents ; [i][n] -> n > 0, Territoires d'un continent 'i' */
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


vector<vector<string> > LoadMaps(int switchNum)
{

    vector<string> stringList;
    vector<vector<string> > mappp;
    // Add maps here
    switch(switchNum){
        case 1:
            stringList.push_back("./maps/Grand Montreal.map");
            break;
        case 2: 
            stringList.push_back("./maps/Quebec.map");
            break;
        case 3:
            stringList.push_back("./maps/Honeycomb.map");   
            break;
        
    }
    
    return mappp;
}
