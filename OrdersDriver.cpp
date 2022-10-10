#include "OrdersDriver.h"

string testOrdersLists(){

    //create test orderlist
    OrderList testOrderList = new OrderList();

    //create individual orders and add them to testOrderList

    String returnStatement;

    try{

        for(i = testOrderList.being(); i != testOrderList.end(); i++){

            //i is an order
            i.validate();
            i.execute();
            //the above two invocations prove that the order's class is a subclass of order through polimorphism.
            //validate and execute are both methods or class Order which are inherited by subtypes

        }

        //test move() and remove():
        testOrderList.move();
        testOrderList.remove();

    }

    catch(string errorMessage){

        cout << errorMessage;

    }

    return testOrdersLists;

}