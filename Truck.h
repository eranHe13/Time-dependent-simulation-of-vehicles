

#ifndef HW3_TRUCK_H
#define HW3_TRUCK_H
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "Time.h"
#include "iostream"

using Course =  pair<Time  , int >;
using TruckCourse = map<string , Course>;
using shared_WareHouse = shared_ptr<Warehouse>;

class Truck:public Vehicle{
private:
    int inventory_amount;
    TruckCourse course;
    shared_WareHouse curr_dest_warehouse;
     shared_WareHouse curr_park_warehouse;
     vector<string> order_course;
public:
     Truck( string &i_name,  string &i_type, const Point &i_location);
     /// UPDATE & SET
     void update_course(vector<string>& data );
     void set_speed( Warehouse& from , Warehouse& to );
     void init( vector<vector<string> >& data );
     void updateInventory();
     void arrived(int time);

     /// COMMANDS
     void destination_cmd(vector<string>& data){cout << "DESTINATION COMMAND NOT AVAILABLE FOR TRUCK"<<endl;} ;
     void course_cmd(vector<string>& data){cout << "COURSE COMMAND NOT AVAILABLE FOR TRUCK"<<endl;};
     void position_cmd(vector<string>& data){cout << "POSITION COMMAND NOT AVAILABLE FOR TRUCK"<<endl;};
     void go(int time) ;

     bool checkEndCourse(int time);
     void print();
     bool needTOleave(int time);
     void tryToDrive(int time);
     bool can_attack();
     void Under_attack();

};



#endif //HW3_TRUCK_H
