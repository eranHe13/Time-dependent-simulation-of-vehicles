

#include "Model.h"

Model* Model::instance = nullptr;

Model::Model():objects(), warehouses(),vehicles(),factory1(new ObjectFactory()),v(){
    factory1 = new ObjectFactory();
}

/// GETTERS
/*SINGLETON FUNCTION*/
Model* Model::getInstance() {
    if(instance == nullptr){
        instance = new Model();
    }
    return instance;}

/*FUNCTION TO GET THE ASKED WAREHOUSE*/
Warehouse &Model::getWarehouse(string &warehouse_name) {
    return *warehouses.at(warehouse_name);
}
/*FUNCTION TO GET ALL OBJECTS FOR VIEW*/
const SimObjectMap &Model::getObjects() {
    return objects;
}
/*FUNCTION TO GET ALL WAREHOUSE*/
WarehouseMap &Model::getAllWarehouses() {
    return warehouses;
}


/// INIT
/*CHECK DATA AND CREATE TRUCK*/
void Model::initTruck(string &file) {
    string type = "Truck";
    vector<vector<string> > data;
    is_truck_valid(file, data);
    is_valid_course(data);
    string truck_name = file.substr(0, file.find('.'));
    Point firstLocation = instance->objects.at(data[0][0])->getLocation();
    shared_ptr<Vehicle> truck = (factory1->createObject(truck_name , type, firstLocation));
    dynamic_pointer_cast<Truck>(truck)->init(data);
    objects.insert({truck_name, truck});
    vehicles.insert({truck_name, truck});
}
/*CHECK DATA AND CREATE WAREHOUSE*/
void Model::initWareHouse(string &file) {
    vector<vector<string> > data;
    is_warehouse_valid(file, data);
    string type = "Warehouse";
    for (auto &d: data) {
        Point loc(stof(d[1]), stof(d[2]));
        int amount = stoi(d[3]);
        string name = d[0];
        shared_ptr<Warehouse> p = make_shared<Warehouse>(name, type , loc , amount); // CRATE WAREHOUSE
        instance->objects.insert({name, p});
        instance->warehouses.insert({name, p});
    }
    string name = "Frankfurt";
    Point loc = {40, 10};
    int amount = 100000;
    shared_ptr<Warehouse> p = make_shared<Warehouse>(name, type , loc , amount); // CRATE WAREHOUSE
    instance->objects.insert({name, p});
    instance->warehouses.insert({name, p});

}


/// VALIDATION
/*FUNCTION TO CHECK IF THE COURSE DATA OF THE NEW TRUCK IS VALID*/
void Model::is_valid_course(vector<vector<string> > &data) {
    for (auto &s: data) {
        if (instance->warehouses.find(s[0]) == instance->warehouses.end())
            throw Exception(s[0] + " NOT INCLUDE IN THE MAP");
    }
}
/*FUNCTION TO CHECK IF THE DATA OF THE NEW CHOPPER IS VALID*/
void Model::check_chopper(const vector<string> &data) {
    if (data[1].size() > 12 || instance->vehicles.find(data[1]) != instance->vehicles.end()) {
        throw Exception("NAME LENGTH NOT VALID OR THIS STATE TROOPER IS ALL READY EXIST");
    }
    if(data.size() != 5 ){
        throw Exception("NEED FOR ARGUMENTS TO CREATE CHOPPER");
    }
}
/*FUNCTION TO CHECK IF THE DATA OF THE NEW STATE TROOPER IS VALID*/
void Model::check_State_trooper(const vector<string> &data) {
    if (data[1].size() > 12 || instance->vehicles.find(data[1]) != instance->vehicles.end()) {
        throw Exception("NAME LENGTH NOT VALID OR THIS STATE TROOPER IS ALL READY EXIST");
    }
    if (instance->warehouses.find(data[3]) == instance->warehouses.end()) {
        throw Exception(data[3] + " WAREHOUSE NOT EXIST IN THE MAP ");
    }
}


/// COMMANDS
/*FUNCTION TO CREATE ELEMENTS USING OBJECT FACTORY CLASS*/
void Model::createElm(const vector<string> &data) {
    if(findVehicle(data[1])){
        throw Exception(data[1] +  " " + data[2] + " IS ALL READY EXIST");
    }

    if (data[2] == "State_trooper") {
        string type = "State_trooper";
        instance->check_State_trooper(data);
        Point p = instance->warehouses[data[3]]->getLocation();
        string name = data[1];
        string warehouse_loc = data[3];
        auto s = factory1->createObject(name, type, p);
        dynamic_pointer_cast<State_trooper>(s)->set_course(instance->warehouses[data[3]]);
        objects.insert({name, s});
        vehicles.insert({name, s});
    }

    else if (data[2] == "Chopper") {
        string type = "Chopper";
        instance->check_chopper(data);
        string pointA =  data[3];
        string pointB =  data[4];
        string name = data[1];
        Point p = parse_points(pointA , pointB);
        auto s = factory1->createObject(name, type, p);
        objects.insert({name, s});
        vehicles.insert({name, s});
    }
    else {
        throw Exception("VEHICLE TYPE NOT IN THE SYSTEM");
    }
}
/*FUNCTION TO UPDATE COURSE COMMAND FOR THE GIVEN VEHICLE*/
void Model::course(vector<string>& data, string &vehicleName)  {
    if(!findVehicle(vehicleName)){
        cout << data[0] << " NOT EXIST"<< endl;
        return;
    }
    shared_ptr<Vehicle> v =  vehicles.at(vehicleName);
    v->course_cmd(data);
}
/*FUNCTION TO UPDATE DESTINATION COMMAND FOR THE GIVEN VEHICLE*/
void Model::destination(vector<string>& data, string &vehicleName)  {
    if(!findVehicle(vehicleName)){
        cout << data[3] << " NOT EXIST"<< endl;
        return;
    }
    shared_ptr<Vehicle> v =  vehicles.at(vehicleName);
    v->destination_cmd(data);
}
/*FUNCTION TO UPDATE POSITION COMMAND FOR THE GIVEN VEHICLE*/
void Model::position(vector<string>& data, string &vehicleName){
    if(!findVehicle(vehicleName)){
        cout << data[3] << " NOT EXIST"<< endl;
        return;
    }
    shared_ptr<Vehicle> v =  vehicles.at(vehicleName);
    v->position_cmd(data);
}
/*FUNCTION TO UPDATE ATTACK COMMAND FOR THE GIVEN CHOPPER*/
void Model::attack(vector<string> &data, string &vehicleName) {
    if(vehicles.find(vehicleName) == vehicles.end() ){
        cout << vehicleName + " not exist" << endl;
    }
    if(!dynamic_pointer_cast<Chopper>(vehicles.at(vehicleName)) ){
        cout << vehicleName + " is not Chopper" << endl;
    }
    if(data.size() == 3 && vehicles.find(data[2]) != vehicles.end()){
        if(!dynamic_pointer_cast<Truck>(vehicles.at(data[2])) ){
            cout << data[2 ] + " is not Truck" << endl;
            return;
        }
        shared_ptr<Vehicle> truck  = vehicles.at(data[2]);
        dynamic_pointer_cast<Chopper>(vehicles.at(vehicleName))->attack(truck);
    }
}
/*FUNCTION TO STOP ALL VEHICLES*/
void Model::stop() {
    for(auto& v: vehicles){
        v.second->update_state(Stopped);
    }
}
/*SIMULATION FUNC TO SIMULATE EACH VEHICLE*/
void Model::go(int time){
    for(auto v : instance->vehicles){
        v.second->go(time);
    }
    v.update();
}
/*FUNCTION TO UPDATE VIEW*/
void Model::view(vector<string> &data) {
    v.update();
    v(data[0] , data);
}



/*
 * CHECK IF THERE OBJECT IN THE GIVEN LOCATION
 */
string Model::operator()(int x , int y){
    for( auto& ele : instance->objects){
        if(int(ele.second->getLocation().x) == x  && int(ele.second->getLocation().y) == y) return ele.first;}
    return "0";
}


/*
 * FUNCTION TO PARSE POINT FROM STRING TO DOUBLE RETURN POINT OBJECT
 */
Point  Model::parse_points(string& pointA , string& pointB){
    string a = pointA.substr(pointA.find('(')+1 , pointA.find(',')-1);
    string b = pointB.substr(  0, pointB.find(')'));
    if(!isFloat(a ) || !isFloat(b)) throw Exception( pointA + " " + pointB +  " THE POINTS NOT VALID");
    return  Point(stod(a) , stod(b));
}


/*
 * FUNCTION TO PRINT STATUS OF EACH OBJECT
 */
void Model::print() const {
    cout << "Warehouses: " << endl;
    for (const auto &s: instance->warehouses) {
        s.second.get()->print();
    }
    cout << "-----------------------------------------------------------------------" << endl;


    for (const auto &s: instance->vehicles) {
        s.second->print();
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------" << endl;
}


/*
 * FUNCTION TO CHECK IF VEHICLE EXIST
 */
bool Model:: findVehicle(const string& name){
    for(auto& v : instance->vehicles){
        if(v.first == name) return true;
    }
    return false;
}
/*
 * FUNCTION TO CHECK POSITION COMMAND DATA
 */
void Model:: check_position(vector<string> &data){
    if(data.size() != 5) {
        throw Exception("NEED 5 ARGUMENTS FOR COURSE COMMEND");
    }
    if (data[0].size() > 12  || !isNumber(data[2]) || !isNumber(data[3]) ) {
        throw Exception("NAME LENGTH NOT VALID OR POSITION OR SPEED");
    }
    data[2] = data[2].substr(data[1].find('(') + 1);
    data[3] = data[3].substr(1, data[2].find(')') - 1);
    data[4] = data[4].substr(data[3].find(' ') + 1);
    if (!isFloat(data[2]) || !isFloat( data[3]) || !isNumber(data[4]))
        throw Exception("POSITION COMMEND DETAILS NOT VALID");
}

Model::~Model() {
    delete instance;
    delete factory1;
}

