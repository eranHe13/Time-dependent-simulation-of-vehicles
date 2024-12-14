

#include "Truck.h"
#include "Model.h"


Truck::Truck( string &i_name,  string &i_type, const Point &i_location):
        Vehicle(i_name , i_type , i_location), inventory_amount(0){}

void Truck::init( vector<vector<string> >& data ){
    for(auto& s : data){
        update_course(s);
        order_course.push_back(s[0]);
    }

    Warehouse& from  = Model::getInstance()->getWarehouse(data[0][0]);
    Warehouse& to  = Model::getInstance()->getWarehouse(data[1][0]);
    set_speed(from , to );
    update_state(Parked);
    for(const auto& a: course){
        inventory_amount+=a.second.second;
    }
    from.update("sub" , inventory_amount);
    curr_dest_warehouse = make_shared<Warehouse>(to);
    curr_park_warehouse = make_shared<Warehouse>(from);
}

void Truck:: update_course(vector<string>& data ){
    if(data.size() == 2){ // FIRST WAREHOUSE NOT HAS ARRIVING TIME AND INVENTORY AMOUNT
        int living_hour = stoi(data[1].substr( 0, data[1].find(':')));
        int living_min = stoi(data[1].substr(  data[1].find(':')+1));
        Time T(-1,-1,living_hour , living_min);
        course.insert({data[0], {T, 0}});
    }
    else{ // NOT FIRST WAREHOUSE HAS ARRIVING TIME AND INVENTORY AMOUNT
        Time T(data[1] , data[3]);
        course.insert({data[0] , {T , stoi(data[2])}});
    }

}

void Truck:: set_speed( Warehouse& from , Warehouse& to ){
    double dis = Point::getDistance(from.getLocation() , to.getLocation());
    const float t  = Time :: get_Travel_time(course.at(order_course[0]).first,course.at(order_course[1]).first);
    double speed = dis / t;
    update_speed(speed);
}

void Truck:: updateInventory(){
    if(course.at(order_course[0]).second == 0 && curr_park_warehouse->getName() == order_course[0]) return;
    int sub_amount = course.at(curr_park_warehouse->getName()).second;
    //curr_park_warehouse->operator+=(sub_amount);
    string name = curr_park_warehouse->getName();
    Model::getInstance()->getWarehouse(name).update("add" , sub_amount);
    //curr_park_warehouse->operator+=(sub_amount);
    //curr_park_warehouse->update("add",sub_amount);
    inventory_amount-= sub_amount;
}

bool Truck:: checkEndCourse(int time){
    if(get_state() == Off_road) return true;
    if(curr_park_warehouse->getName() == order_course[0] && order_course.size() ==1 &&
        course.at(curr_park_warehouse->getName() ) .first.get_living_time().hour <= time ){
        update_state(Off_road);
        return true;
    }
    return false;
}

bool Truck::needTOleave(int time){
    if(get_state() == Moving_to) return true;
    if(get_state() == Parked){
        int min = course.at(curr_park_warehouse->getName()).first.get_living_time().hour;
        return (min <= time);
    }
    return false;
}

void Truck:: arrived(int time){
    update_state(Parked);
    curr_park_warehouse = curr_dest_warehouse;
    updateInventory();
    order_course.erase(order_course.begin());
    if(checkEndCourse(time)){return;}
    curr_dest_warehouse = make_shared<Warehouse>(Model::getInstance()->getWarehouse(order_course[1]));
    updateLocation(curr_park_warehouse->getLocation());
    set_speed(*curr_park_warehouse , *curr_dest_warehouse);
}

void Truck:: tryToDrive(int time){
    double dis = Point::getDistance(getLocation() , curr_dest_warehouse->getLocation());
    if(dis <= get_speed()){
        arrived(time);
        go(time);
        return;
    }
    else{
        drive(1 , curr_dest_warehouse->getLocation());
    }

}

void Truck::go(int time) {
    if(get_state() == Stopped || get_state() == Off_road || checkEndCourse(time)) {
        return;
    }
    double dis = Point::getDistance(getLocation() , curr_dest_warehouse->getLocation());
    if (needTOleave(time)) {
        if(get_state() == Parked){
            if(needTOleave(time)){
                tryToDrive( time);
                return;
            }
        }
        if(get_state() == Moving_to){
          if(dis <= get_speed()){
              arrived(time);
              go(time);
              return;
          }
          else{
              drive(1 , curr_dest_warehouse->getLocation());
          }

        }
    }
    else{ return;}}

void Truck:: print(){
    cout << "Truck" << " " << getName() << " at (" << getLocation().x << ", " << getLocation().y << ") , ";
    if(get_state() == Moving_to){
        cout << "Heading to " << curr_dest_warehouse->getName() << ", Crates = " << inventory_amount << endl;
    }
    else if(get_state() == Parked){
        cout << "Parking in  " << curr_park_warehouse->getName() << ", Crates = " << inventory_amount << endl;
    } else if(get_state() == Off_road){
        cout << "End Course : Parking in  " << curr_park_warehouse->getName() << ", Crates = " << inventory_amount << endl;
    }
    else if(get_state() == Stopped){
        cout << "Stopped" <<  endl;
    }
}

bool Truck::can_attack() {
    for(const auto &obj : Model::getInstance()->getObjects()){
        if(dynamic_cast<State_trooper*>(obj.second.get())){
            if(Point::getDistance(getLocation() , obj.second->getLocation()) <=10 ){
                return true;
            }
        }
    }
    return false;
}

void Truck::Under_attack() {
    inventory_amount = 0 ;
    update_state(Off_road);
}

