
#ifndef HW3_MODEL_H
#define HW3_MODEL_H

#include "View.h"
#include "vector"
#include <memory>
#include "Validation.h"
#include "Exception.cpp"
#include "ObjectFactory.h"
/*
 * SINGLETON OBJECT
 * It is his responsibility to monitor the world of simulation in all its aspects, from management
 * Time and ending with object storage
 */


using namespace std;
using VehicleMap = map<string,shared_ptr<Vehicle>> ;
using WarehouseMap =  map<string,shared_ptr<Warehouse>> ;
using SimObjectMap =  map<string,shared_ptr<SimObject>>;

class Model {
private:
    SimObjectMap objects;       /// MAP OF ALL OBJECTS
    WarehouseMap warehouses;    /// MAP OF ALL WAREHOUSES
    VehicleMap vehicles;        /// MAP OF ALL WAREHOUSES
    ObjectFactory* factory1;    /// FACTORY TO CREATE THE ELEMENTS
    View v;                     /// VIEWER
    Model();                    /// PRIVATE CONSTRUCTOR
    static Model* instance;

public:
    Model(const Model& rhs) = delete;
    Model& operator=(const Model& rhs) = delete;
    Model& operator=(const Model&& rhs) = delete;
    ~Model();

    /// GETTERS
    static Model* getInstance();                        /// GETTER FRO SINGLETON OBJECT
    Warehouse& getWarehouse(string& warehouse_name);   /// GETTER FOR WAREHOUSE
    const SimObjectMap& getObjects();                 /// GETTER FOR SIM OBJECT
    WarehouseMap& getAllWarehouses();                /// RETURN MAP OF ALL WAREHOUSES

    /// INIT
    void initTruck(string& file);                   /// INITIATION TRUCK
    void initWareHouse(string& file);              /// INITIATION WAREHOUSE

    /// VALIDATION
    void is_valid_course(vector<vector<string> > &data);    /// CHECK TRUCK COURSE
    void check_chopper(const vector<string> &data);        /// CHECK CHOPPER DATA
    void check_State_trooper(const vector<string> &data); /// CHECK STATE TROOPER DATA
    void check_position(vector<string> &data);

    /// COMMANDS
    void createElm(const vector<string> &data);
    void course(vector<string> &data, string &vehicleName) ;      /// COURSE COMMAND TRIGGER TO THE RIGHT VEHICLE
    void destination(vector<string> &data, string &vehicleName); /// DESTINATION COMMAND TRIGGER TO THE RIGHT VEHICLE
    void position(vector<string>& data, string &vehicleName) ;  /// POSITION COMMAND TRIGGER TO THE RIGHT VEHICLE
    void attack(vector<string> &data, string &vehicleName);    /// ATTACK COMMAND TRIGGER TO THE RIGHT CHOPPER
    void stop();                                              /// STOP COMMAND - STOP ALL VEHICLES
    void view(vector<string>& data);                         /// COMMAND FOR THE VIEW OBJECT
    void go(int time);                                      /// SIMULATE FUNC TO RUN PROGRAM

    string operator()(int x , int y);       /// FUNCTION TO CHECK IF THERE ANY OBJECT IN THE GIVEN POINT
    void print() const;                     /// PRINT OBJECTS STATUS
    bool findVehicle(const string& name);
    Point parse_points(string &pointA, string &pointB); /// STRING  TO POINT OBJECT

};


#endif //HW3_MODEL_H
