

#include <iterator>
#include "Controller.h"

void Controller::init(int size, const char **files) {
    ///  initializing first files
    vector<string> input;
    for (int i = 1; i < size; i++) {
        input.emplace_back(files[i]);
    }
    for (int i = 0; i < input.size(); i++) {
        try {
            /// INPUT FILES
            if (input[i] == "-w") {
                i++;
                model->initWareHouse(input[i]);
            }
            if (input[i] == "-t") {
                for (int j = ++i; j < input.size(); j++) {
                    model->initTruck(input[j]);
                }
            }
        }

        catch (Exception &e) { ///////ERROR ON INIT THE PROGRAM , EXIT
            cout << e.what();
            exit(0);
        }
    }
}

void Controller::ParseCommend(vector<vector<string>>& all_data){

    for (auto& data : all_data) {
        try {
            if (data[0] == "create") {
                model->createElm(data);
            }
            else if ( data.size() >= 3 && data[1] == "course" ) {
                model->course(data, data[0]);
            }
            else if (data.size() >= 3 && data[1] == "destination" ) {
                model->destination(data, data[0]);
            }
            else if (data.size() >= 3 && data[1] == "position" ) {
                model->position(data, data[0]);
            }
            else if (data.size() >= 3 &&data[1] == "attack" ) {
                model->attack(data, data[0]);
            }
            else if (data.size() >= 3 &&data[0] == "stop") {
                model->stop();
            }
            else{
                cout  << "COMMEND NOT FOUND" <<endl;
            }
        }
        catch (Exception& e ) {
            cout << endl << e.what() <<endl;
        }
    }
}

void Controller::user_interaction() {
    vector<vector<string>> all_data;
    model = Model::getInstance();
    try{
        while (true) {
            vector<string> details;
            string input;
            cout << endl << "Time " << time << ": " << " Enter commend: ";
            getline(cin ,  input);
            if (input.empty() || input == "\r" || input == "\n") {
                cout << "command not found" << endl;
                continue;
            }
            stringstream s(input);
            istream_iterator<std::string> begin(s);
            istream_iterator<std::string> end;
            vector<string> data(begin, end);
            if(data[0] == "exit") exit(1);


            if (data[0] == "default" || data[0] == "size" || data[0] == "zoom" || data[0] == "pan" ||
                data[0] == "show" ) {
                model->view(data);
                continue;

            }
            if(data[0] == "status"){
                cout << endl;
                model->print();
                continue;

            }
            if(data[0] != "go"){
                all_data.push_back(data);
                continue;

            }
            if(data[0] == "go"){
                cout << endl;
                ParseCommend(all_data);
                model->go(time+1);
                time++;
                all_data.clear();
                continue;

            }
        }}
    catch (Exception& e ){
        cerr << endl << e.what()<< endl;

    }
}
