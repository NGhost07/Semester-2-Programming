#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "pugixml.hpp"
#include "pugiconfig.hpp"

using namespace std;
using namespace pugi;

pair<double, double> get_coordi(string s){ // string -> float
    vector<string> VS;
    string s1 = s;
    size_t pos = 0;
    string token;
    while ((pos = s1.find(",")) != string::npos) {
        token = s1.substr(0, pos);
        VS.push_back(token);
        s1.erase(0, pos + 1);
    }
    VS.push_back(s1);
    pair<double, double> result;
    result.first = stod(VS.front());
    result.second = stod(VS.back());
    return result;
}

vector<string> detached_string(string s){ // 123,323 -> 123 and 323
    string s1 = s;
    vector<string> VS;
    size_t pos = 0;
    string token;
    while ((pos = s1.find(",")) != string::npos || (pos = s1.find(".")) != string::npos) {
        token = s1.substr(0, pos);
        VS.push_back(token);
        s1.erase(0, pos + 1);
    }
    VS.push_back(s1);
    return VS;
}

bool check_used(vector<string> a, string b){
    for (auto i: a) {
        if (b == i)
            return true;
    }return false;
}

vector<string> get_routes(string _type){
    vector<string> routes;
    xml_document doc;
    doc.load_file("/Users/tranhoangnam/Desktop/Programing/lab3/lab3/data.xml");
    for (auto i=doc.child("dataset").first_child(); i; i=i.next_sibling()) {
        string type = i.child("type_of_vehicle").child_value();
        if (type == _type) {
            string tmp = i.child("routes").child_value();
            vector<string> s = detached_string(tmp);
            for (auto j : s){
                if (check_used(routes, j) == false)
                    routes.push_back(j);
            }
        }
    }return routes;
}

vector<int> get_number_stops(string _type){
    xml_document doc;
    doc.load_file("/Users/tranhoangnam/Desktop/Programing/lab3/lab3/data.xml");
    vector<string> routes = get_routes(_type);
    vector<int> stops;
    stops.assign(routes.size(), 0);
    for (auto j=doc.child("dataset").first_child(); j; j=j.next_sibling()) {
        string type = j.child("type_of_vehicle").child_value();
        if (type == _type) {
            string tmp = j.child("routes").child_value();
            vector<string> s = detached_string(tmp);
            for (auto k: s)
                for (int i=0; i<routes.size(); i++)
                    if (k == routes[i])
                        stops[i] ++;
        }
    }return stops;
}

vector<vector<pair<double, double>>> local_of_stops(string _type){
    xml_document doc;
    doc.load_file("/Users/tranhoangnam/Desktop/Programing/lab3/lab3/data.xml");
    vector<vector<pair<double, double>>> result;
    vector<string> routes = get_routes(_type);
    result.resize(routes.size());
    for (auto j=doc.child("dataset").first_child(); j; j=j.next_sibling()) {
        string type = j.child("type_of_vehicle").child_value();
        if (type == _type) {
            string tmp = j.child("routes").child_value();
            vector<string> s = detached_string(tmp);
            for (auto k: s) {
                for (int i=0; i<routes.size(); i++) {
                    if (k == routes[i]) {
                        string tmp1 = j.child("coordinates").child_value();
                        pair<double, double> coor = get_coordi(tmp1);
                        result[i].push_back(coor);
                    }
                }
            }
        }
    }return result;
}

double route_length_of_stop(vector<pair<double, double>> a){
    double result = 0;
    for (int i=0; i<a.size()-1; i++) {
        result += sqrt(pow(a[i+1].first-a[i].first, 2)+pow(a[i+1].second-a[i].second, 2));
    }return result;
}

class Tramvai{
protected:
    vector<string> routes;
    vector<int> n_stops;
    vector<pair<string, int>> routes_and_stops;
    vector<pair<string, vector<pair<double, double>>>> routes_and_local_of_stops;
public:
    Tramvai(){
        routes = get_routes("Трамвай");
        n_stops = get_number_stops("Трамвай");
        for (int i=0; i<routes.size(); i++) {
            pair<string, int> temp;
            temp.first = routes[i];
            temp.second = n_stops[i];
            routes_and_stops.push_back(temp);
        }
        vector<vector<pair<double, double>>> tmp1 = local_of_stops("Трамвай");
        for (int i=0; i<routes.size(); i++) {
            pair<string, vector<pair<double, double>>> tmp2;
            tmp2.first = routes[i];
            tmp2.second = tmp1[i];
            routes_and_local_of_stops.push_back(tmp2);
        }
    }
    vector<pair<string, int>> get_routes_and_stops(){
        return routes_and_stops;
    }
    pair<string, int> biggest_stop(){
        int cnt = -1;
        pair<string, int> tmp;
        for (auto i: routes_and_stops) {
            if (i.second > cnt) {
                cnt = i.second;
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    vector<pair<string, double>> routes_length(){
        vector<vector<pair<double, double>>> local_stops = local_of_stops("Трамвай");
        vector<pair<string, double>> result;
        for (int i=0; i<routes.size(); i++) {
            pair<string, double> tmp;
            tmp.first = routes[i];
            tmp.second = route_length_of_stop(local_stops[i]);
            result.push_back(tmp);
        }
        return result;
    }
    pair<string, double> longest_route(){
        pair<string, double> tmp;
        tmp.second = -1;
        vector<pair<string, double>> routesLength = routes_length();
        for (auto i: routesLength) {
            if (i.second > tmp.second) {
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    ~Tramvai(){
    }
};

class Trolleybus : protected Tramvai{
public:
    Trolleybus(){
        routes = get_routes("Троллейбус");
        n_stops = get_number_stops("Троллейбус");
        for (int i=0; i<routes.size(); i++) {
            pair<string, int> temp;
            temp.first = routes[i];
            temp.second = n_stops[i];
            routes_and_stops.push_back(temp);
        }
        vector<vector<pair<double, double>>> tmp1 = local_of_stops("Троллейбус");
        for (int i=0; i<routes.size(); i++) {
            pair<string, vector<pair<double, double>>> tmp2;
            tmp2.first = routes[i];
            tmp2.second = tmp1[i];
            routes_and_local_of_stops.push_back(tmp2);
        }
    }
    vector<pair<string, int>> get_routes_and_stops(){
        return routes_and_stops;
    }
    pair<string, int> biggest_stop(){
        int cnt = -1;
        pair<string, int> tmp;
        for (auto i: routes_and_stops) {
            if (i.second > cnt) {
                cnt = i.second;
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    vector<pair<string, double>> routes_length(){
        vector<vector<pair<double, double>>> local_stops = local_of_stops("Троллейбус");
        vector<pair<string, double>> result;
        for (int i=0; i<routes.size(); i++) {
            pair<string, double> tmp;
            tmp.first = routes[i];
            tmp.second = route_length_of_stop(local_stops[i]);
            result.push_back(tmp);
        }
        return result;
    }
    pair<string, double> longest_route(){
        pair<string, double> tmp;
        tmp.second = -1;
        vector<pair<string, double>> routesLength = routes_length();
        for (auto i: routesLength) {
            if (i.second > tmp.second) {
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    ~Trolleybus(){
    }
};

class Avtobus : protected Tramvai{
public:
    Avtobus(){
        routes = get_routes("Автобус");
        n_stops = get_number_stops("Автобус");
        for (int i=0; i<routes.size(); i++) {
            pair<string, int> temp;
            temp.first = routes[i];
            temp.second = n_stops[i];
            routes_and_stops.push_back(temp);
        }
        vector<vector<pair<double, double>>> tmp1 = local_of_stops("Автобус");
        for (int i=0; i<routes.size(); i++) {
            pair<string, vector<pair<double, double>>> tmp2;
            tmp2.first = routes[i];
            tmp2.second = tmp1[i];
            routes_and_local_of_stops.push_back(tmp2);
        }
    }
    vector<pair<string, int>> get_routes_and_stops(){
        return routes_and_stops;
    }
    pair<string, int> biggest_stop(){
        int cnt = -1;
        pair<string, int> tmp;
        for (auto i: routes_and_stops) {
            if (i.second > cnt) {
                cnt = i.second;
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    vector<pair<string, double>> routes_length(){
        vector<vector<pair<double, double>>> local_stops = local_of_stops("Автобус");
        vector<pair<string, double>> result;
        for (int i=0; i<routes.size(); i++) {
            pair<string, double> tmp;
            tmp.first = routes[i];
            tmp.second = route_length_of_stop(local_stops[i]);
            result.push_back(tmp);
        }
        return result;
    }
    pair<string, double> longest_route(){
        pair<string, double> tmp;
        tmp.second = -1;
        vector<pair<string, double>> routesLength = routes_length();
        for (auto i: routesLength) {
            if (i.second > tmp.second) {
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    ~Avtobus(){
    }
};

class Streets{
private:
    vector<string> name_streets;
    vector<int> number_stops;
    vector<pair<string, int>> streets_stops;
public:
    Streets(){
        xml_document doc;
        doc.load_file("/Users/tranhoangnam/Desktop/Programing/lab3/lab3/data.xml");
        name_streets.push_back(doc.child("dataset").first_child().child("the_official_name").child_value());
        for (auto i=doc.child("dataset").first_child(); i; i=i.next_sibling()) {
            string tmp = i.child("the_official_name").child_value();
            if (check_used(name_streets, tmp) == false)
                name_streets.push_back(tmp);
        }
        number_stops.assign(name_streets.size(), 0);
        for (auto i=doc.child("dataset").first_child(); i; i=i.next_sibling()) {
            string tmp = i.child("the_official_name").child_value();
            for (int k=0; k<name_streets.size(); k++)
                if (tmp == name_streets[k])
                    number_stops[k] ++;
        }
        for (int i=0; i<name_streets.size(); i++) {
            pair<string, int> tmp;
            tmp.first = name_streets[i];
            tmp.second = number_stops[i];
            streets_stops.push_back(tmp);
        }
    }
    vector<string> get_name(){
        return name_streets;
    }
    vector<int> get_stops(){
        return number_stops;
    }
    pair<string, int> most_number_stop(){
        pair<string, int> tmp;
        tmp.second = -1;
        for (auto i: streets_stops) {
            if (i.second > tmp.second) {
                tmp.first = i.first;
                tmp.second = i.second;
            }
        }return tmp;
    }
    ~Streets(){
    }
};

void print_all_vehicle(){
    xml_document doc;
    doc.load_file("/Users/tranhoangnam/Desktop/Programing/lab3/lab3/data.xml");
    vector<string> name_Vehicles;
    name_Vehicles.push_back(doc.child("dataset").child("transport_station").child("type_of_vehicle").child_value());
    for (auto i=doc.child("dataset").first_child(); i; i=i.next_sibling()) {
        string tmp = i.child("type_of_vehicle").child_value();
        if (tmp != name_Vehicles.back())
            name_Vehicles.push_back(tmp);
    }// get name Vehicles
    for (auto i: name_Vehicles)
        cout << i << "  ";
    cout << endl << endl;// print name Vehicles
}

int main(int arngc, const char * argv[]) {
    setlocale(LC_ALL, "Россия");
    
    print_all_vehicle();
    
    Tramvai tramvai;
    Trolleybus troleybus;
    Avtobus abtobus;
    cout << "Задание 1: " << endl;
    pair<string, int> temp;
    temp = tramvai.biggest_stop();
    cout << "The route with the largest number of stops for Tramvai: "<<endl;
    cout << temp.first << " with " << temp.second << " stops"<< endl << endl;
    temp = troleybus.biggest_stop();
    cout << "The route with the largest number of stops for Trolleybus: "<<endl;
    cout << temp.first << " with " << temp.second << " stops"<< endl << endl;
    temp = abtobus.biggest_stop();
    cout << "The route with the largest number of stops for Avtobus: "<<endl;
    cout << temp.first << " with " << temp.second << " stops"<< endl << endl << endl;
    
    cout << "Задание 2: " << endl;
    pair<string, double> temp2;
    temp2 = tramvai.longest_route();
    cout << "The longest route (based on coordinates) for Tramvai: " << endl;
    cout << temp2.first << " with " << temp2.second<< endl << endl;
    temp2 = troleybus.longest_route();
    cout << "The longest route (based on coordinates) for Trolleybus: " << endl;
    cout << temp2.first << " with " << temp2.second << endl << endl;
    temp2 = abtobus.longest_route();
    cout << "The longest route (based on coordinates) for Avtobus: "  << endl;
    cout << temp2.first << " with " << temp2.second << endl << endl << endl;

    cout << "Задание 3: " << endl;
    Streets streets;
    temp = streets.most_number_stop();
    cout << "The street has the most stops: " ;
    cout << temp.first << " with " << temp.second << " stops" << endl << endl;
    return 0;
}
