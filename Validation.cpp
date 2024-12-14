
#include "Validation.h"
#include "Exception.cpp"

void is_warehouse_valid(const string& file, vector<vector<string>> &data) {
    split_string(file, data);
    for (vector<string> &d: data) {
        if (d.size() < 4) throw Exception("the number of argument not valid in " + file);
        if (!isAlpha(d[0]) || d[0].size() > 12) throw Exception("data - " + d[0] + " in " + file + " not valid");
        d[1] = d[1].substr(d[1].find('(') + 1);
        d[2] = d[2].substr(1, d[2].find(')') - 1);
        d[3] = d[3].substr(d[3].find(' ') + 1);
        if (!isFloat(d[1]) || !isFloat(d[2]) || !isNumber(d[3]))
            throw Exception("data location or the amount in " + file + " not valid");
    }

}

void is_truck_valid(const string &file, vector<vector<string>> &data) {
    split_string(file, data);
    int index = 0;
    for (vector<string> &d: data) {
        if (index == 0) {
            if (d.size() != 2) throw Exception("the number of argument not valid in " + file);
            if (!isAlpha(d[0])) throw Exception("data - " + d[0] + " in " + file + " not valid");
            if (!is_time(d[1]))throw Exception("the time not valid in " + file);
            index = 1;
        } else {
            if (d.size() != 4) throw Exception("the number of argument not valid in " + file);
            if (!isAlpha(d[0])) throw Exception("data - " + d[0] + " in " + file + " not valid");
            if (!is_time(d[1]) || !is_time(d[3]))throw Exception("the time not valid in " + file);
            if (!isNumber(d[2])) throw Exception("the amount is not valid in " + file);
        }

    }
}

bool isFloat(const string& s) {
    char point = '.';
    if (!s.find(point)) return false;
    for (const char &c: s) {
        if (c == point || c =='-') continue;
        if (!isdigit(c))return false;
    }
    return true;
}

bool isNumber(const string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]) == false)
            return false;
    }
    if(s.size() == 0) return false;
    return true;
}

bool isAlpha(const string& str) {
    for (const char &c: str) {
        if (!isalpha(c)) return false;
    }
    return true;
}

void split_string(const string& file, vector<vector<string>> &data) {
    ifstream my_file(file);             /// OPEN FILE
    if (!my_file) {
        throw Exception(" ERROR: file " + file + " cannot open\n");
    }
    string s;
    while (getline(my_file, s)) {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(s);
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        data.push_back(tokens);
    }
    my_file.close();
}

bool is_time(string &s) {
    if (s.find('\r')) { s = s.substr(0, s.find('\r')); }
    if (s.find(':') == string::npos) {
        return false;}
    for (const char &d: s) {
        if (d == ':') continue;
        if (!isdigit(d)) return false;
    }
    return true;
}