#include "PlayerDriver.h"

string testPlayers() {

    string returnStatement;
    string errorMessage;

    //create test player(s)
    Player testPlayer1 = Player();

    try{
        //player.territories exists
        // if (testPlayer1.territories != NULL)
        //     returnStatement = returnStatement + "testPlayer1 has a list of territories";
        // else{
        //     errorMessage = "testPlayer1 has no list of territories";
        //     throw(errorMessage);
        // }
        
        //player.hand exists
        // if (testPlayer1.hand != NULL)
        //     returnStatement = returnStatement + ", testPlayer1 has a list of cards";
        // else{
        //     errorMessage = "testPlayer1 has no list of cards";
        //     throw(errorMessage);
        // }

        //player.toDefend returns list
        // if (testPlayer1.toDefend != NULL)
        //     returnStatement = returnStatement + ", testPlayer1 has a list of territories to defend";
        // else{
        //     errorMessage = "testPlayer1 has no list of territories to defend";
        //     throw(errorMessage);
        // }

        // //player.toAttack returns list
        // if (testPlayer1.toAttack != NULL)
        //     returnStatement = returnStatement + ", testPlayer1 has a list of territories to attack";
        // else{
        //     errorMessage = "testPlayer1 has no list of territories to attack";
        //     throw(errorMessage);
        // }

        // //check size of order list
        // int orders = testPlayer1.orders;
        // //player.issueOrder()
        // testPlayer1.issueOrder();
        // //verify that order list is now larger by one
        // if (testPlayer1.orders = orders + 1)
        //     returnStatement = returnStatement + ", testPlayer1's orders increased by one upon the call to testPlayer1.issueOrder";
        // else{
        //     errorMessage = "testPlayer1's orders did not increase by one upon the call to testPlayer1.issueOrder";
        //     throw(errorMessage);
        // }

    }
    catch(string errorMessage){

        cout << errorMessage;

    }

    return returnStatement;

}