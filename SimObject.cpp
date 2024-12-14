
#include "SimObject.h"

SimObject::SimObject( string &i_name,  string &i_type, const Point &i_location)
        :type(i_type) , name(i_name) , location(i_location){}

const string &SimObject::getName() {
    return name;
}

Point &SimObject::getLocation() {
    return location;
}

void SimObject::updateLocation(Point &loc) {
    location = loc;
}
