
#include "Vehicle.h"



Vehicle::Vehicle( string &i_name,  string &i_type, const Point &i_location ):
        SimObject(i_name, i_type , i_location),
       state(Parked) , speed(0) , curr_dest({"",{0,0}}){}

bool Vehicle::drive(double rest_time , Point& next) {
    double distance = Point::getDistance(getLocation(), next);
    double k_mCanDo = rest_time * get_speed();
    if (k_mCanDo <= distance) { //
        double t = k_mCanDo / distance;
        double x = ((1.0 - t) * getLocation().x +
                    t * next.getPoint().x);
        double y = ((1 - t) * getLocation().y +
                    t * next.getPoint().y);
        Point loc = {x, y};
        updateLocation(loc);
        update_state(Moving_to);
        return false;
    }
    else {
        updateLocation(next);
        update_state(Parked);
        return true;
    }
}

void Vehicle::update_state(const string& s) {state = s;}

string Vehicle::get_state() const {return state;}

void Vehicle::update_speed(double s) {speed = s;}

double Vehicle::get_speed() const {return speed;}

destination Vehicle::get_curr_destination() const  {return curr_dest;}

bool Vehicle::isHasAngel() const {
    return has_angel;}

void Vehicle::setHasAngel(bool hasAngel) {
    hasAngel = true;}

double Vehicle::getAngle() const {
    return angle;}

void Vehicle::setAngle(double a) {
    angle = a;}

