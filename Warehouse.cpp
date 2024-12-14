

#include "Warehouse.h"
/*
 * RETURN INVENTORY AMOUNT
 */
int Warehouse::getInventoryAmount() const {
    return inventory_amount;
}

void Warehouse::setInventoryAmount(int inventoryAmount) {
    inventory_amount = inventoryAmount;
}

void Warehouse::operator-=(int n) {
    inventory_amount-=n;

}

void Warehouse::operator+=(int n) {
    inventory_amount+=n;
}

void Warehouse::print() {
    cout << "Warehouse " << getName() << " at position (" << getLocation().x << ", " << getLocation().y << "), Inventory: " << inventory_amount << endl;

}

ostream& operator<<(ostream& os, const Warehouse& obj){
    os << "Warehouse " << ((SimObject)obj).getName() << " at position (" << ((SimObject)obj).getLocation().x << ", " << ((SimObject)obj).getLocation().y << "), Inventory: " << obj.inventory_amount;
    return os;

}


