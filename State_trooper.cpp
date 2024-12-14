
#include "State_trooper.h"
#include "Model.h"


State_trooper::State_trooper(string &i_name, string &i_type, const Point &i_location) :
        Vehicle(i_name, i_type,i_location) {
    update_speed(90);
}

void State_trooper:: set_course(shared_ptr<Warehouse> first_loc){
    warehouse_course.clear();
    map<string,shared_ptr<Warehouse>>& w = Model::getInstance()->getAllWarehouses();
    vector<string> visited = {first_loc->getName()};
    Point curr_location = getLocation();
    string curr_warehouse = first_loc->getName();
    warehouse_course.push_back({curr_warehouse , 0});
    float min_dis = INTMAX_MAX;
    string destination;
    for (auto& loop: w) {
        for(auto& curr_warehouse: w) {
            if (find(visited.begin(), visited.end(), curr_warehouse.first) != visited.end()) continue;
            double curr_dis = Point::getDistance(curr_location,curr_warehouse.second->getLocation());
            if (curr_dis < min_dis) {
                min_dis = curr_dis;
                destination = curr_warehouse.first;}
        }
        if(find(visited.begin() , visited.end() , destination) == visited.end()) {
            warehouse_course.push_back({destination , 0});
            visited.push_back(destination);
            curr_location = w[destination]->getLocation();
            min_dis = INTMAX_MAX;
        }
    }

    in = first_loc;
    next = make_shared<Warehouse>(Model::getInstance()->getWarehouse(warehouse_course[1].first));
}

void  State_trooper::go (int time){
    if(get_state() == Stopped){
        return;
    }
    if(driving_type == "position"){
        drive(1 , position);
        return;
    }
    if(driving_type == "course"){
        float X = 10000 * cos(getAngle()) +getLocation().x;
        float Y = 10000 * sin(getAngle()) +getLocation().y;
        Point P(X , Y);
        drive(1 , P);
        return;
    }
    double dis = Point::getDistance(getLocation() , next->getLocation());

    if(!drive(1 , next->getLocation())){
        return;
    }
    else{
        in = next;
        string next_i = get_next(in.get()->getName());
        next = make_shared<Warehouse>(Model::getInstance()->getWarehouse(next_i));
        double k_m = (get_speed() - dis)/100;
        drive(k_m , next->getLocation());
        return;
    }


}

void State_trooper:: print(){
    cout << "State_trooper " << getName() << " at (" << getLocation().x << ", " << getLocation().y
         << ") , ";
    if(get_state() == Stopped) cout << Stopped<< endl;
    else {
        cout<< "Heading to " << next.get()->getName() << endl;
    }
}

void State_trooper:: destination_cmd(vector<string>& data){
    shared_ptr<Warehouse> a = make_shared<Warehouse>(Model::getInstance()->getWarehouse(data[2]));
    set_course(a);
}

void State_trooper::course_cmd(vector<string>& data) {
    check_course(data);
    setAngle(stod(data[2]));
    driving_type = "course";
    update_state(Moving_to);
}

void State_trooper:: check_course(vector<string> &data){
    if(data.size() != 3) {
        throw Exception(getName() + " NEED 3 ARGUMENTS FOR COURSE COMMEND");
    }

    if (!isNumber(data[2])  ){
        throw Exception(getName() + " COURSE COMMEND DETAILS NOT VALID");}
}

string State_trooper::get_next(const string& name) {
    for (int i = 0; i < warehouse_course.size(); i++) {
        if (name == warehouse_course[i].first) {
            return move(warehouse_course[(i + 1) % warehouse_course.size()].first);
        }
    }
    return "non";
}

void State_trooper::position_cmd(vector <string> &data) {
    check_position(data);
    Point p( stod(data[2]) , stod(data[3]));
    position = p;
    driving_type = "position";
    update_state(Moving_to);

}

void State_trooper:: check_position(vector<string> &data){
    if(data.size() != 4) {
        throw Exception("NEED 4 ARGUMENTS FOR POSITION COMMEND");
    }
    data[2] = data[2].substr(data[1].find('(') + 1);
    data[3] = data[3].substr(1, data[2].find(')') - 1);
    if (!isFloat(data[2]) || !isFloat( data[3]) )
        throw Exception("POSITION COMMEND DETAILS NOT VALID");
}
