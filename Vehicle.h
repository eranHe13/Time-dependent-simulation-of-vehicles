

#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H
#include "SimObject.h"
#include "Warehouse.h"
#include <vector>
#include <memory>
#include <map>
#include <cmath>
#include <algorithm>

/* CLASS VEHICLE
 * OBJECT OF THE SIMULATOR
 * */


/*
 * STATS OF VEHICLES
 * */
static const string Stopped = "Stopped";
static const string Parked = "Parked";
static const string Off_road = "Off road";
static const string Moving_to = "Moving to";
using destination = pair<string , Point >;

class Vehicle :public SimObject{
private:
    string state;
    double speed;
    destination curr_dest;
    bool has_angel;
    double angle;

public:
    Vehicle( string &i_name,  string &i_type, const Point &i_location );     //CONSTRUCTOR FOR TRUCK
    virtual ~Vehicle() = default;
    virtual void go(int time) = 0;                          // VIRTUAL FUNC - SIMULATE EACH VEHICLE
    virtual bool drive(double rest_time , Point& next);           // VIRTUAL FUNC - FORWARD VEHICLE BY TIME

    // UPDATE & SETTERS
    void update_state(const string& s);             // UPDATE VEHICLE STATE
    virtual void update_speed(double s);            // VIRTUAL FUNC - UPDATE VEHICLE SPEED
    void setAngle(double angle);                    // SET ANGLE TO DRIVE
    void setHasAngel(bool hasAngel);                // DRIVE ACCORDING ANGLE

    // GETTERS
    bool isHasAngel() const;                        // IS VEHICLE DRIVE ACCORDING ANGLE
    double getAngle() const;                        // GETTER VEHICLE ANGLE
    string get_state() const;                       // GETTER VEHICLE STATE
    double get_speed() const;                       // GETTER VEHICLE SPEED
    destination get_curr_destination() const;       // GETTER FOR THE CURRENT DESTINATION OF THIS VEHICLE

    virtual void print()=0;
    virtual void destination_cmd(vector<string>& data)=0 ;
    virtual void course_cmd(vector<string>& data) = 0;
    virtual void position_cmd(vector<string>& data) = 0;


};


#endif //HW3_VEHICLE_H
