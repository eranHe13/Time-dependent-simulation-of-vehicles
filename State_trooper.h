
#ifndef HW3_STATE_TROOPER_H
#define HW3_STATE_TROOPER_H

#include <vector>
#include "Vehicle.h"



/*
 * State trooper vehicle inherit from Vehicle
 */


class State_trooper : public Vehicle {
private:
    vector <pair <string ,bool>> warehouse_course; /// VECTOR<{WAREHOUSE , VISITED}>
    shared_ptr<Warehouse> next; /// NEXT DESTINATION
    shared_ptr<Warehouse> in ;  /// CURRENT WAREHOUSE
    string driving_type;
    Point position;
public:
    State_trooper(string &i_name,  string &i_type, const Point &i_location);
    /// SIMULATE
    void  go (int time);

    /// COMMANDS
    void destination_cmd(vector<string>& data);
    void course_cmd(vector<string>& data);
    void position_cmd(vector<string>& data);

    void print();

    // GET & SET
    void set_course(shared_ptr<Warehouse> first_loc);
    string get_next(const string &name);

    /// VALIDATION
    void check_course(vector<string> &data);
    void check_position(vector <string> &data);
};

#endif //HW3_STATE_TROOPER_H
