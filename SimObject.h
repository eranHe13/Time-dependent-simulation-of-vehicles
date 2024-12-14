

#ifndef HW3_SIMOBJECT_H
#define HW3_SIMOBJECT_H
#include <string>
#include <ostream>
#include "Geometry.h"
using namespace std;

/*
 * BASE OBJECT OF THE PROGRAM
 * HAS :
 *      NAME
 *      LOCATION
 *      SPECIFIC OBJECTS INHERITORS FROM THIS CLASS
 * */
class Model;
class SimObject {
private:
    string type; // TYPE OF THE OBJECT
    string name; // NAME OF THE OBJECT
    Point location; // CURRENT LOCATION OF THE OBJECT (GEOMETRY::STRUCT POINT)
public:
    SimObject( string& i_name , string& i_type , const Point& i_location); // CONSTRUCTOR
    const string& getName(); // GETTER FOR THE NAME
    virtual Point& getLocation(); // GETTER FOR THE LOCATION
    void updateLocation(Point& loc); // UPDATE LOCATION

};


#endif //HW3_SIMOBJECT_H
