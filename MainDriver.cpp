#include "MapDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "GameEngineDriver.h"


using namespace std;

int main(){

testLoadMaps();
testPlayers();
testCards();
testOrdersLists();
testGameStates();
cout << "Driver loaded" << endl;
return 0;
}


