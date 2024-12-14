

#ifndef HW3_WAREHOUSE_H
#define HW3_WAREHOUSE_H

#include "SimObject.h"

class Warehouse : public SimObject {

private:
    int inventory_amount;
public:

    Warehouse(string &i_name,  string &i_type, const Point &i_location , int& amount):
            SimObject(i_name, i_type , i_location),inventory_amount(amount){}

    /// GET & SET & UPDATE
    int getInventoryAmount() const;
    void setInventoryAmount(int inventoryAmount);
    void update(string com , int n){
        if(com == "sub"){
            inventory_amount -= n;
        }
        else if(com == "add"){
            inventory_amount +=n;
        }
    }
    void operator-=(int n );
    void operator+=(int n );
    friend ostream& operator<<(ostream& os, const Warehouse& obj);
    void print();
};


#endif //HW3_WAREHOUSE_H
