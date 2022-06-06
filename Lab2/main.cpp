#include<iostream>
#include <math.h>
#include <vector>

using namespace std;

class Polynominal{
private:
    vector<double> p;
public:
    Polynominal(){ // Contructor with no parameter
    }
    Polynominal(vector<double> a):p(a){ // Contructor with no parameter
    }
    Polynominal(const Polynominal &t){ // copy Constructor
        this->p = t.p;
    }
    Polynominal operator = (const Polynominal &t);
    bool operator == (const Polynominal &t) const;
    bool operator != (const Polynominal &t) const;
    Polynominal operator + (const Polynominal &t);
    Polynominal operator - (const Polynominal &t);
    Polynominal operator - ();
    void operator += (const Polynominal &t);
    void operator -= (const Polynominal &t);
    Polynominal operator * (const int number);
    Polynominal operator / (const int number);
    void operator *= (const int number);
    void operator /= (const int number);
    Polynominal operator >> (const int number);
    Polynominal operator << (const int number);
    double operator [] (const int index);
    void printP(){
        for (int i=0; i<this->p.size(); i++)
            cout << p[i] << "   ";
        cout << endl;
    }
    ~Polynominal(){ // Destructor
    }
};

Polynominal Polynominal::operator=(const Polynominal &t){
    this->p = t.p;
    return *this;
}

bool Polynominal::operator==(const Polynominal &t) const{
    if (this->p.size() != t.p.size()) {
        return false;
    }
    else{
        for (int i=0; i<p.size(); i++) {
            if (p[i] != t.p[i]) {
                return false;
            }
        }
    }return true;
};

bool Polynominal::operator!=(const Polynominal &t) const{
    if (this->p.size() != t.p.size())
        return true;
    else{
        for (int i=0; i<p.size(); i++) {
            if (p[i] != t.p[i])
                return true;
        }
    }return false;
}

Polynominal Polynominal::operator+(const Polynominal &t){
    Polynominal Z;
    if(this->p.size() < t.p.size()){
        Z.p = t.p;
        for(int i = 0; i < this->p.size(); i++){
            Z.p[i] += this->p[i];
        }
    }
    else{
        Z.p = this->p;
        for(int i = 0; i < t.p.size(); i++){
            Z.p[i] += t.p[i];
        }
    }
    return Z;
}

Polynominal Polynominal::operator-(const Polynominal &t){
    Polynominal Z;
    if(this->p.size() < t.p.size()){
        Z.p = t.p;
        for(int i = 0; i < Z.p.size(); i++)
            Z.p[i] *= -1;
        for(int i = 0; i < this->p.size(); i++)
            Z.p[i] += this->p[i];
    }
    else{
        Z.p = this->p;
        for(int i = 0; i < t.p.size(); i++)
            Z.p[i] -= t.p[i];
    }
    return Z;
}

Polynominal Polynominal::operator-(){
    Polynominal Z;
    Z.p = this->p;
    for(int i = 0; i < Z.p.size(); i++){
        Z.p[i] *= -1;
    }
    return Z;
}

void Polynominal::operator+=(const Polynominal &t){
    for(int i = 0; i < min(t.p.size(), this->p.size()); i++)
        this->p[i] += t.p[i];
    if(t.p.size() > this->p.size()){
        for(int i = (int)this->p.size(); i < t.p.size(); i++)
            this->p.push_back(t.p[i]);
    }
}

void Polynominal::operator-=(const Polynominal &t){
    for(int i = 0; i < min(t.p.size(), this->p.size()); i++)
        this->p[i] -= t.p[i];
    if(t.p.size() > this->p.size()){
        for(int i = (int)this->p.size(); i < t.p.size(); i++)
            this->p.push_back(-t.p[i]);
    }
}

Polynominal Polynominal::operator*(const int number){
    Polynominal Z;
    Z.p = this->p;
    for(int i = 0; i < Z.p.size(); i++)
        Z.p[i] *= number;
    return Z;
}

Polynominal Polynominal::operator/(const int number){
    Polynominal Z;
    Z.p = this->p;
    for(int i = 0; i < Z.p.size(); i++)
        Z.p[i] /= number;
    return Z;
}

void Polynominal::operator*=(const int number){
    for(int i = 0; i < this->p.size(); i++)
        this->p[i] *= number;
    return;
}

void Polynominal::operator/=(const int number){
    for(int i = 0; i < this->p.size(); i++)
        this->p[i] /= number;
    return;
}

Polynominal Polynominal::operator>>(const int number){
    reverse(this->p.begin(), this->p.end());
    for(int i = 0; i < number; i++)
        this->p.push_back(1);
    reverse(this->p.begin(), this->p.end());
    return *this;
}

Polynominal Polynominal::operator<<(const int number){
    reverse(this->p.begin(), this->p.end());
    for(int i = 0; i < number; i++)
        this->p.pop_back();
    reverse(this->p.begin(), this->p.end());
    return *this;
}

double Polynominal::operator[](const int index){
    if(index >= this->p.size())
        return 0.00;
    return this->p[index];
}

int main(){
    vector<double> a = {1, 2, 3, 4};
    vector<double> b = {5,6};
    Polynominal A(a);
    Polynominal B(b);
    Polynominal C = A; // =
    cout << "C: "; C.printP();
    A==B ? cout << "A = B" << endl : cout << "A # B" << endl;//==
    A!=C ? cout << "A # C" << endl : cout << "A = C" << endl;//!=
    Polynominal D = A+B;//+
    cout << "D: "; D.printP();
    Polynominal E = A-B;
    cout << "E: "; E.printP();
    B+=C;
    cout << "new B: "; B.printP();
    B-=C;
    cout << "new B: "; B.printP();
    cout << A[2] << endl;
    //...
    return 0;
}
