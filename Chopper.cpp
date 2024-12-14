

#include "Chopper.h"
#include "Model.h"

Chopper::Chopper(string &i_name, string &i_type, const Point &i_location) :
                Vehicle(i_name, i_type, i_location) ,attack_range(FIRST_ATTACK_RANGE){
    update_state(Stopped);
}

void Chopper::go(int time) {
    if(get_state() == Stopped || get_state() == Parked){
        return;
    }
    if(type == "course"){
        double distance = get_speed();
        double xCor = ((distance) * cos(to_radians(getAngle()))) / 100 + getLocation().x ;
        double yCor = (distance * sin(to_radians(getAngle()))) / 100 + getLocation().y ;
        Point p = Point(xCor,yCor);
        updateLocation(p);
    }
    if(type == "position"){
        if(drive(1 , dest)){
            update_state(Parked);
        }

    }
}

void Chopper::attack(shared_ptr<Vehicle> truck) {
    if(!dynamic_pointer_cast<Truck>(truck)->can_attack()){
        if(Point::getDistance(getLocation() , truck->getLocation()) >= attack_range){
            dynamic_pointer_cast<Truck>(truck)->Under_attack();
            if(attack_range < 20 ) { attack_range++;}
            updateLocation(truck->getLocation());
            update_state(Stopped);
            attack_range++;
            cout << "\n attack succeed \n";
        } else{
            cout << "\n attack failed \n";
            if(attack_range < MAX_ATTACK_RANGE){
                attack_range--;
            }
        }
    }
    else{
        cout << "\n cannot attack \n";
    }
    if(attack_range < 0){ attack_range = 0;}
}

void Chopper::position_cmd(vector<string> &data) {
    check_position(data);
    Point p( stod(data[2]) , stod(data[3]));
    dest = p;
    if(stoi(data[4]) > MAX_SPEED){
        throw Exception("MAX SPEED FOR CHOPPER IS 170");
    }
    update_speed(stoi(data[4]));
    type = "position";
    update_state(Moving_to);

}

void Chopper::destination_cmd(vector<string> &data) {
    cout << "NO AVAILABLE FOR CHOPPER";
}

void Chopper::course_cmd(vector<string> &data) {
    check_course(data);
    update_speed(stoi(data[3]));
    setAngle(stod(data[2]));
    type = "course";
    update_state(Moving_to);

}

void Chopper:: check_course(vector<string> &data){
    if(data.size() != 4) {
        throw Exception("NEED 4 ARGUMENTS FOR COURSE COMMEND");
    }

    if (!isNumber(data[2]) || !isNumber( data[3]) ){
        throw Exception("COURSE COMMEND DETAILS NOT VALID");}
}

void Chopper:: check_position(vector<string> &data){
    if(data.size() != 5) {
        throw Exception("NEED 5 ARGUMENTS FOR POSITION COMMEND");
    }
    data[2] = data[2].substr(data[1].find('(') + 1);
    data[3] = data[3].substr(1, data[2].find(')') - 1);
    data[4] = data[4].substr(data[3].find(' ') + 1);
    if (!isFloat(data[2]) || !isFloat( data[3]) || !isNumber(data[4]))
        throw Exception("POSITION COMMEND DETAILS NOT VALID");
}

void Chopper::print() {
    cout << "Chopper" << " " << getName() << " at (" << getLocation().x << ", " << getLocation().y << ") , ";
    if(get_state() == Moving_to){
        cout << "Heading on course " << getAngle() << " deg, speed " << get_speed() <<  " km/h"<< endl ;
    }
    else if(get_state() == Parked){
        cout << "Parking " << endl;
    } else if(get_state() == Stopped){
        cout << "Stopped" <<endl;
    }
}
