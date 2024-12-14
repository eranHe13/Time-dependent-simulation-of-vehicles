
#include "Controller.h"


int main(int argc, const char **argv) {
    try {
        if(argc < 5) { throw Exception("NOT ENOUGH FILES TO INIT PROGRAM");}
    }
    catch (Exception& e){
        cout << e.what();
        exit(1);
    }
    Controller C ;
    try{
        C.init(argc, argv);
    }
    catch (Exception& e){
        cout << e.what();
        exit(1);
    }
    C.user_interaction();


    return 0;
}
