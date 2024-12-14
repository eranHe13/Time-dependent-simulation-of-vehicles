

#include "View.h"
#include "Model.h"
View::View()
:size(DEFAULT_SIZE),
scale(DEFAULT_SCALE),
origin(make_pair(-10,-10))
{
    commands["default"] = DEFAULT;
    commands["size"] = SIZE;
    commands["zoom"] = ZOOM;
    commands["pan"] = PAN;
    commands["show"] = SHOW;
}

void View::set_default() {
    setSize(DEFAULT_SIZE);
    setScale(DEFAULT_SCALE);
    setOrigin(DEFAULT_ORIGIN, DEFAULT_ORIGIN);
}

void View::show() const {
    cout << "Display size: " << size << ", scale: " << scale
    << ", origin: (" << origin.first << "," << origin.second << ")" << endl;
    show_map();
}

/**
 * showing the map
 */
void View:: show_map() const {
    if(!is_show_able()){
        cerr << "ERROR: can't display on this sizes please change";
        return;
    }
    string dot = ". ";
    int int_scale = static_cast<int>(scale);
    int origin_x = static_cast<int>(origin.first);
    int origin_y = static_cast<int>(origin.second);
    int X = origin_x;
    int Y = origin_y + size*int_scale-int_scale;
    int is_Y_firstLine = 0 ;

    for (; Y >= origin_y ; Y -= int_scale) {
        cout << setw(5);

        if(!is_Y_firstLine){
            cout << Y;
            if(to_string(Y).size() == 3)
                cout << setw(1);
            else
                cout << setw(2);
        }
        else
            cout << setw(7);

        for(X = origin_x; X <= size * int_scale + origin_x - int_scale; X += int_scale) {
            if(objects.find(make_pair(X,Y)) != objects.end()){
                cout << objects.at(make_pair(X,Y));}
            else {
                cout << dot;
            }
        }
        cout << endl;
        is_Y_firstLine == 2 ? is_Y_firstLine = 0 : is_Y_firstLine++;
    }
    is_Y_firstLine = 0;
    for(X = origin_x; X <= size * int_scale + origin_x - int_scale; X += int_scale)
    {
        if(!is_Y_firstLine)
            cout << setw(6)<< X;

        is_Y_firstLine == 2 ? is_Y_firstLine = 0 : is_Y_firstLine++;
    }
    cout << endl;


}
void View::print_x_axis() const{
    int edge_x = ceil(origin.first + size * scale - scale);
    int x_axis = (int) origin.first;
    while(x_axis <= edge_x){
        string s(6 - to_string(x_axis).length(), ' ');
        s += to_string(x_axis);
        cout << s;
        x_axis += scale * 3;
    }
    cout << endl;
}

bool View::is_show_able() const{
    double edge_x = origin.first + size * scale - scale;
    double edge_y = origin.second + size * scale - scale;
    bool res =  !(abs(origin.first) > MAX_SHOW || abs(origin.second) > MAX_SHOW ||
      abs(edge_x) > MAX_SHOW || abs(edge_y) > MAX_SHOW);
    return res;

}

int View::getSize() const {
    return size;
}

void View::setSize(int size) {
    View::size = size;
}

double View::getScale() const {
    return scale;
}

void View::setScale(double scale) {
    View::scale = scale;
}

const pair<double, double> &View::getOrigin() const {
    return origin;
}

void View::setOrigin(double x, double y) {
    origin.first = x;
    origin.second = y;
}

std::ostream &operator<<(std::ostream &os, const View &view) {
    os << "size: " << view.size << " scale: " << view.scale << " origin: " << view.origin.first;
    return os;
}

/**
 * preform the commands for the view obj
 * assuming the vars are already have been validated
 * @param cmd - the command to be execute
 * @param vars - vars for the different commands
 */
void View::operator()(const string& cmd, const vector<string>& vars){
    switch(commands[cmd]){
        case DEFAULT:
            set_default();
            break;
        case SIZE: {
            if(!isNumber(vars[1]) || vars[1] == "1"){ throw Exception("var not valid.");}
            int _size = stoi(vars[1]);
            setSize(_size);
        }
            break;
        case ZOOM: {
            if(!isNumber(vars[1])){ throw Exception("var not valid.");}
            double _scale = stod(vars[1]);
            setScale(_scale);
        }
            break;
        case PAN: {
            double _x = stod(vars[1]);
            double _y = stod(vars[2]);
            setOrigin(_x, _y);
        }
            break;
        case SHOW:
            show();
            break;
    }
}

void View::getCords(int& x,int& y,double x_obj ,double y_obj) {
    x = static_cast<int>(x_obj);
    y = static_cast<int>(y_obj);
    x -= x % static_cast<int>(scale);
    y -= y % static_cast<int>(scale);
}
void View::update() {
    objects.clear();
    int x,y;
    string name;
    const SimObjectMap& o = Model::getInstance()->getObjects();
    for(const auto& obj:o)
    {
        getCords(x,y,obj.second->getLocation().x ,obj.second->getLocation().y );
        name = obj.first.substr(0,2);

        objects.insert({make_pair(x,y),name});
    }
}