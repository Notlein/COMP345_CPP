#include "OrdersDriver.h"
class Orders;
int testOrdersLists(){

    //create test orderlist
    OrderList testOrderList;
    queue<Orders*> q = testOrderList.get_order_list();
    //create individual orders and add them to testOrderList

    string returnStatement;

    try{
        
        for(Orders* i = q.front(); i != q.back(); i++){

            //i is an order
            Orders ii = *i;
            ii.validate();
            ii.execute();
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

    return 0;

}