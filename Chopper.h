
#ifndef HW3_CHOPPER_H
#define HW3_CHOPPER_H
#include "Vehicle.h"

/*
 * Chopper vehicle inherit from Vehicle
 * default big 5
 */

static const int MAX_SPEED = 170;
static const int FIRST_ATTACK_RANGE = 2;
static const int MAX_ATTACK_RANGE = 20;

class Chopper : public Vehicle {
private:
    int attack_range;
    string type;
    Point dest;
public:
    Chopper(string &i_name,  string &i_type, const Point &i_location);

    /// SIMULATE
    void  go (int time);

    /// COMMANDS
    void destination_cmd(vector<string>& data);
    void position_cmd(vector<string>& data);
    void course_cmd(vector<string>& data);
    void attack(shared_ptr<Vehicle> truck);

    ///CHECK DATA COMMANDS
    void check_position(vector<string> &data);
    void check_course(vector<string> &data);

    /// STATUS
    void print();

};


#endif //HW3_CHOPPER_H
