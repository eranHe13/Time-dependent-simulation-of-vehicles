

#ifndef HW3_OBJECTFACTORY_H
#define HW3_OBJECTFACTORY_H
#include <iostream>
#include <memory>
#include <map>
#include "Truck.h"
#include "State_trooper.h"
#include "Chopper.h"



using namespace std;
struct Point;
class ObjectFactory {
private:
    map<string , int> objects_types ;
public:
    ObjectFactory();
    shared_ptr<Vehicle> createObject( string &i_name,  string &i_type, const Point &i_location);
};


#endif //HW3_OBJECTFACTORY_H
