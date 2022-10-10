#include "Map.h"
#include "Map.cpp"
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>




using namespace std;

vector<vector<string>> parseMap(ifstream& file) {
    
    string str;
    vector<vector<string>> arr_cont; /* [i][0]  -> continents ; [i][n] -> n > 0, Territoires d'un continent 'i' */
    // ifstream file("./maps/Grand Montreal.map");

    while (getline(file, str)) {

        if (str == "[Continents]") {

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
            /* end of continents array */
        }
       
            

        if (str == "[Territories]"){
            int index = 0;
            string delimiter2 = ",";
            string terrName;
            string terrProperties;

                while (getline(file, str)) {
                    if (str != "\r" && str != "" && str != "\n") {
                        terrName = str.substr(0, str.find(delimiter2));
                        terrProperties = str.substr(str.find(delimiter2) + 1, str.length() - 1);
                        arr_cont.at(index).push_back(terrName);
                        arr_cont.at(index).push_back(terrProperties);
                        

                    } else {index++;}
                    
                }
        }
        // for (int i = 0; i < arr_cont.size(); i++) {

        //     // cout << arr_cont.at(i).at(0) << endl;
        //     // cout << arr_cont.at(i).at(1) << endl << endl;
        //     for (int j = 2; j < arr_cont.at(i).size(); j+=2) {
        //         /* j = territory name; j+1 = territory properties */
        //         // cout << arr_cont.at(i).at(j) << endl;
        //         string delimiter3 = ",";
        //         string name;
        //         string coordX;
        //         string coordY;
        //         string cont;
        //         vector<string> adjTerr;

        //         string props = arr_cont.at(i).at(j + 1);

        //         coordX = props.substr(0, props.find(delimiter3));
                
        //         props = props.substr(props.find(delimiter3)+1,props.length()-1);
        //         coordY = props.substr(0, props.find(delimiter3));
                
        //         props = props.substr(props.find(delimiter3) + 1, props.length() - 1);
        //         cont = props.substr(0, props.find(delimiter3));
                
        //         props = props.substr(props.find(delimiter3) + 1, props.length());
                
        //         // coordX.erase(remove(coordX.begin(), coordX.end(), ' '), coordX.end());
        //         // coordY.erase(remove(coordY.begin(), coordY.end(), ' '), coordY.end());
        //         // cont.erase(remove(cont.begin(), cont.end(), ' '), cont.end());
                

        //         // cout << coordX << ":" << coordY  << endl << "Continent : " << cont << endl << "Adjacent territories :" << props << endl << endl;
        //     }
            
        //     // cout << "\n******************************" << endl;
        // }

    }
    file.close();
    
    return arr_cont;
}


int testloadMaps() {
    
vector<string> stringList;

stringList.push_back("./maps/Grand Montreal.map");
stringList.push_back("./maps/Quebec.map");
stringList.push_back("./maps/Honeycomb.map");

// iterable

for (string x : stringList){
    ifstream file(x);
    vector<vector<string>> v = parseMap(file);

    try
{
    Map m(v);
   x = x.substr(7,x.length());
   x = x.substr(0,x.length()-4);
    m.mapName = new string(x);

    // Uncomment below to show Continent name, number of points and territories.
    //
    // for (int i=0;i<m.continents->size();i++){
    // string* s = new string(*m.continents->at(i).Cname);
    // int* s1 = new int(*m.continents->at(i).nbPts);
    // cout << "Continent name is : " << *s <<endl << "Number of points : " << *s1 << endl << "Territories are : ";
    // cout << *m.continents->at(i).territories->at(0).Tname;
    // for (int j=1;j<m.continents->at(i).territories->size();j++){
    //     cout << ", "<<  *m.continents->at(i).territories->at(j).Tname;
    // }
    //     cout << "." << endl << endl;
//    }

    bool val = m.validate();

    if(m.getNbContinents() < 1){
        std::cerr  << endl << "********************\n" << x << endl << "********************\n" << "There is a problem in the map syntax : Please verify the .map file" << endl;
    } else if (!val){
        std::cerr  << endl << "********************\n" << x << endl << "********************\n" << "There is a problem in the map. It's not a proper connected graph." << endl;

    } else {
        std::cout << "Succesful map created" << endl << "********************\n" << x << endl << "********************" << endl;
        cout << m << endl;  
    }


    m.~Map();
}
catch(const std::exception& e)
{
    std::cerr << "INVALID MAP FILE" << endl << "********************\n" << x << e.what() << endl << "********************" << endl;
}
    }
    return 0;
}

int main(){
    testloadMaps();
    return 0;
}