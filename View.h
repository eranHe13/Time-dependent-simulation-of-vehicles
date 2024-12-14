

#ifndef HW3_VIEW_H
#define HW3_VIEW_H
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>


using namespace std;
#define MIN_SIZE 6
#define MAX_SIZE 30
#define DEFAULT_SIZE 25
#define DEFAULT_SCALE 2.0
#define DEFAULT_ORIGIN (-10)
#define MAX_SHOW 100


typedef enum{
    DEFAULT,
    SIZE,
    ZOOM,
    PAN,
    SHOW
} command;

using location = pair<int , int >;

class View {
private:
    int size;
    double scale;
    pair<double, double> origin;
    map<string, command> commands;
    map <location , string > objects;
public:
    View();

    void operator()(const string& command, const vector<string>& vars);

    /**
     * print to the screen the details of the map
     */
    void show() const;

    /**
     * setting the map to its default parameters
     */
    void set_default();

    friend std::ostream &operator<<(std::ostream &os, const View &view);

    /**
     * Getters & Setters
     */
    int getSize() const;

    void setSize(int size);

    double getScale() const;

    void setScale(double scale);

    const pair<double, double> &getOrigin() const;

    void setOrigin(double x, double y);

    bool is_show_able() const;

    void print_x_axis() const;

    void getCords(int& x,int& y,double x_obj ,double y_obj);

    void update();

    void show_map() const ;
};


#endif //HW3_VIEW_H
