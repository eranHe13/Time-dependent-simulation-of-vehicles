
#include "ObjectFactory.h"

shared_ptr<Vehicle> ObjectFactory::createObject(string &i_name,  string &i_type, const Point &i_location) {
    switch (objects_types.at(i_type)) {
        case 1:
            return make_shared<Truck>(i_name, i_type, i_location);
        case 2:
            return make_shared<Chopper>(i_name, i_type, i_location);
        case 3:
            return make_shared<State_trooper>(i_name, i_type, i_location);
        default:
            return nullptr;
    }
}

ObjectFactory::ObjectFactory() :objects_types(){
    objects_types.insert({"Truck" , 1});
    objects_types.insert({"Chopper" , 2});
    objects_types.insert({"State_trooper" , 3});
}
