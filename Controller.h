

#ifndef HW3_CONTROLLER_H
#define HW3_CONTROLLER_H

#include "Model.h"
#include "ObjectFactory.h"
#include "Exception.cpp"
#include <iostream>
#include <algorithm>

using namespace std;

/* CONTROLLER CLASS USES FOR INTERACTION WITH USER-MODEL
 * MVC
 */


class Controller {
    Model* model;
    int time;

public:
    Controller() : model(Model::getInstance()), time(0) {
        int x =5 ;
    }; /// DEFAULT CONSTRUCTOR INIT CONTROLLER AND MODEL
    void init(int size, const char **files);                /// INIT PROGRAM WITH THE FIRST FILES
    void user_interaction();                                /// CONTROL INTERACTION BETWEEN USER AND MODEL
    void ParseCommend(vector<vector<string>> &all_data);    /// PARSE COMMANDS ACCORDING TYPES USES MODEL
};
#endif
