//
// Created by User on 6/22/2022.
//

#ifndef HW3_VALIDATION_H
#define HW3_VALIDATION_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

void is_warehouse_valid(const string& file, vector<vector<string>> &data);
void is_truck_valid(const string &file, vector<vector<string>> &data);
void split_string(const string& file, vector<vector<string>> &data) ;
bool isAlpha(const string& str) ;
bool isFloat(const string& s) ;
bool isNumber(const string& s) ;
bool is_time(string &s);

#endif //HW3_NEW_VALIDATION_H
