
#ifndef HW3_EXCEPTION_CPP
#define HW3_EXCEPTION_CPP

#include <string>
#include <exception>
using namespace std;

/* EXCEPTION CLASS FOR THE PROGRAM */

class Exception: public std::exception {
protected:
    string err;

public:
    explicit Exception(string  e): err(std::move(e)){}
    string what() {return "ERROR: " + err;}
};


#endif //HW3_EXCEPTION_H
