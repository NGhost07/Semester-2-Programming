#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Point {
private:
    float x,y;
public:
    Point(){ // Default constructor (no parameters)
        this->x = 0;
        this->y = 0;
    }
    Point (float xx, float yy){// constructor with parameters
        this->x = xx;
        this->y = yy;
    }
    Point(const Point &copyCon){ //Copy constructor
        this->x = copyCon.getX();
        this->y = copyCon.getY();
    }
    void setX(float xx){
        this->x = xx;
    }
    void setY(float yy){
        this->y = yy;
    }
    float getX()const{
        return this->x;
    }
    float getY()const{
        return this->y;
    }
    void operator=(const Point &ope){ //operator=
        this->x = ope.getX();
        this->y = ope.getY();
    }
    void printPoint(){
        cout << "(" << x << ";" << y << ")  ";
    }
    ~Point(){ //Destructor
        //cout << "Called destructor!" << endl;
    };
};

class Polyline{// duong gap khuc
protected:
    vector<Point> v;
    float DBTP(Point A, Point B){ // Distance Between Two Points
        return sqrtf(powf(A.getX()-B.getX(),2)+powf(A.getY()-B.getY(),2));
    }
public:
    Polyline(){
    }
    Polyline(Point m[], int s){ // Constructor with parameters
        for (int i=0; i<s; i++)
            v.push_back(m[i]);
    }
    Polyline(vector<Point> &vv){ // Constructor with parameter is vector
        v = vv;
    }
    Polyline(Polyline const &t){// Copy constructor
        this->v = t.v;
    }
    float getLength(){ // get legth of the polyline
        float l=0;
        for (int i=0; i<v.size()-1; i++) {
            l += DBTP(v[i], v[i+1]);
        }return l;
    }
    void printAllPoints(){
        for (int i=0; i<v.size(); i++) {
            v[i].printPoint();
        }cout << endl;
    }
    void operator=(const Polyline &u){
        this->v = u.v;
    }
    ~Polyline(){
    }
};

class ClosedPolyline : public Polyline{//duong gap khuc khep kin
public:
    ClosedPolyline() : Polyline(){
    }
    ClosedPolyline(Point m[], int k) : Polyline(m,k){
    }
    ClosedPolyline(vector<Point> &m) : Polyline(m){
    }
    ClosedPolyline(ClosedPolyline const &k) : Polyline(k){
    }// coppy
    float getLengthClose(){
        float l = getLength();
        return l += DBTP(v.front(), v.back());
    }
    ~ClosedPolyline(){
    }
};

class Polygons : public ClosedPolyline{//Da giac
public:
    Polygons() : ClosedPolyline(){
    }
    Polygons(Point m[], int k) : ClosedPolyline(m,k){
    }
    Polygons(vector<Point> &m) : ClosedPolyline(m){
    }
    Polygons(Polygons const &k) : ClosedPolyline(k){
    }
    void type(){
        if (v.size() < 3)
            cout << "This is a Polyline" << endl;
        if (v.size() == 3)
            cout << "This is a Trianggle" << endl;
        else
            cout << "This is Polyline with " << v.size() << " edges!" << endl;
    }
    float perimeter(){ // perimeter of Polygons
        float p = getLengthClose();
        return p;
    }
    float area(){ // Applies only to convex polygons
        float s = 0, t = 0;
        Point a = v.front(), b = v.back();
        for (int i = 0 ; i<v.size()-1; i++) {
            t = v[i].getX()*v[i+1].getY()-v[i].getY()*v[i+1].getX();
            s += t;
        }
        s = s + (b.getX()*a.getY()-b.getY()*a.getX());
        s = abs(s)/2;
        return s;
    }
    ~Polygons(){
    }
};

class Triangle : public Polygons{//tam giac
public:
    Triangle() : Polygons(){
    }
    Triangle(Point m[], int k) : Polygons(m, k){
        if (k!=3) {
            cout << "\nThis is not Triangle!" << endl;
            exit(0);
        }else
            cout << "\nThis is Triangle!" << endl;
    }
    Triangle(vector<Point> &vv) : Polygons(vv){
        if (v.size()!=3) {
            cout << "\nThis is not Triangle!" << endl;
            exit(0);
        }else
            cout << "\nThis is Triangle!" << endl;
    }
    Triangle(Triangle const &t) : Polygons(t){
    }
    ~Triangle(){
    }
};

class Trapezoid : public Polygons{//hinh thang
public:
    Trapezoid() : Polygons(){
    }
    Trapezoid(Point m[], int k) : Polygons(m,k){
            if (k!=4) {
                cout << "\nThis is not Trapezoid!" << endl;
                exit(0);
            }else
                cout << "\nThis is Trapezoid!" << endl;
    }
    Trapezoid(vector<Point> &vv) : Polygons(vv){
        if (v.size()!=4) {
            cout << "\nThis is not Trapezoid!" << endl;
            exit(0);
        }else
            cout << "\nThis is Trapezoid!" << endl;
    }
    Trapezoid(Trapezoid const &p) : Polygons(p){ // copy
    }
    ~Trapezoid(){
    }
};

class RegularPolygon : public Polygons{// da giac deu
public:
    RegularPolygon() : Polygons(){
    }
    RegularPolygon(Point m[], int k) : Polygons(m,k){
        float t = DBTP(v[0], v[1]);
        for (int i = 1; i<v.size()-1 ; i++) {
            if (DBTP(v[i], v[i+1]) != t) {
                cout << "\nThis is not Regular Polygon!" << endl;
                exit(0);
            }else
                cout << "\nThis is Regular Polygon with " << v.size() << "edges!" << endl;
        }
    }
    RegularPolygon(vector<Point> &m) : Polygons(m){
        float t = DBTP(m[0], m[1]);
        for (int i = 1; i<m.size()-1 ; i++) {
            if (DBTP(m[i], m[i+1]) != t) {
                cout << "\nThis is not Regular Polygon!" << endl;
                exit(0);
            }else
                cout << "\nThis is Regular Polygon with " << m.size() << "edges!" << endl;
        }
    }
    RegularPolygon(RegularPolygon const &t) : Polygons(t){ //copy
    }
    ~RegularPolygon(){
    }
};

int main(int argc, const char * argv[]) {
    // Point
    Point A1; // Default constructor (no parameters)
    cout << "A1: "; A1.printPoint();
    Point B1(2, 5); // Constructor with parameters
    cout << "B1: "; B1.printPoint();
    Point copy(B1); // Copy constructor
    cout << "copy: "; copy.printPoint();
    Point assignment = A1; // Operator=
    cout << "assignment: "; assignment.printPoint();

    Point A(-2,1), B(4,5), C(3,-2), D(-3,-1);
    Point m[4] = {A, B, C, D};
    //Polyline
    Polyline polyline(m, 4);
    cout << "\n\nAll points of Polyline: "; polyline.printAllPoints();
    cout << "Length of Polyline: " << polyline.getLength() << endl;
    Polyline copyPolyline(polyline); //copy
    cout << "All points of copy Polyline: "; copyPolyline.printAllPoints();
    cout << "Length of copy Polyline: " << copyPolyline.getLength() << endl;
    //Closed Polyline
    ClosedPolyline cPolyline(m,4);
    cout << "\nAll points of ClosedPolyline: "; cPolyline.printAllPoints();
    cout << "Length of ClosedPolyline: " << cPolyline.getLengthClose() << endl;
    //Polygons
    cout << endl;
    Polygons polygon(m,4);
    cout << "All points of Polygons: "; polygon.printAllPoints();
    polygon.type();
    cout << "Perimeter of Polygons: " << polygon.perimeter() << endl;
    cout << "Area of Polygons: " << polygon.area() << endl;
    //Triangle
    Point n[3] = {A,B,C};
    Triangle triangle(n, 3);
    cout << "All points of Triangle: "; triangle.printAllPoints();
    cout << "Perimeter of Triangle: " << triangle.perimeter() << endl;
    cout << "Area of Triangle: " << triangle.area() << endl;
    //Trapezoid
    Trapezoid trapozoid(m,4);
    cout << "All points of Trapezoid: "; trapozoid.printAllPoints();
    cout << "Perimeter of Trapezoid: " << trapozoid.perimeter() << endl;
    cout << "Area of Trapezoid: " << trapozoid.area() << endl;
    //RegularPolygon
    Point A2(0,2), B2(2,0), C2(0,-2), D2(-2,0);
    Point t[4] = {A2, B2, C2, D2};
    RegularPolygon rePolygon(t,4);
    cout << "All points of Regular Polygon: "; rePolygon.printAllPoints();
    cout << "Perimeter of Regular Polygon: " << rePolygon.perimeter() << endl;
    cout << "Area of Regular Polygon: " << rePolygon.area() << endl;
    return 0;
}
