#include <iostream>
#include <fstream>
#include <vector>

// 1 = yellow, 2 = green, 3 = orange, 4 = blue, 5 = pink, 6 = white

using namespace std;

class Rubik{
public:
    vector<vector<int>> U;
    vector<vector<int>> D;
    vector<vector<int>> F;
    vector<vector<int>> R;
    vector<vector<int>> B;
    vector<vector<int>> L;
    vector<string> pro2;
public:
    Rubik(){
        U.assign(3, {1,1,1});
        D.assign(3, {6,6,6});
        F.assign(3, {2,2,2});
        R.assign(3, {3,3,3});
        B.assign(3, {4,4,4});
        L.assign(3, {5,5,5});
    }
    Rubik(vector<vector<int>> tmp){
        U[0] = tmp[0]; U[1] = tmp[1]; U[2] = tmp[2];
        L[0] = tmp[3]; L[1] = tmp[4]; L[2] = tmp[5];
        F[0] = tmp[6]; F[1] = tmp[7]; F[2] = tmp[8];
        R[0] = tmp[9]; R[1] = tmp[10]; R[2] = tmp[11];
        B[0] = tmp[12]; B[1] = tmp[13]; B[2] = tmp[14];
        D[0] = tmp[15]; D[1] = tmp[16]; D[2] = tmp[17];
    }
    void print(){
        vector<vector<int>> tmp(3, vector<int>(12));
        for (int i=0; i<3; i++) {
            for (int j=0; j<12; j++) {
                if (j>=3 && j<6) {
                    tmp[i][j] = U[i][j-3];
                }
                if(tmp[i][j] == 0){
                    cout << "   ";
                }else{
                    cout << tmp[i][j] << "  ";
                }
            }cout << endl;
        }
        for (int i=0; i<3; i++) {
            for (int j=0; j<12; j++) {
                if (j>=0 && j<3) {
                    cout << L[i][j] << "  ";
                }
                else if(j>=3 && j<6){
                    cout << F[i][j-3] << "  ";
                }
                else if(j>=6 && j<9){
                    cout << R[i][j-6] << "  ";
                }
                else if(j>=9 && j<12){
                    cout << B[i][j-9] << "  ";
                }
            }cout << endl;
        }
        for (int i=0; i<3; i++) {
            for (int j=0; j<12; j++) {
                if (j>=3 && j<6) {
                    tmp[i][j] = D[i][j-3];
                }
                if(tmp[i][j] == 0){
                    cout << "   ";
                }else{
                    cout << tmp[i][j] << "  ";
                }
            }cout << endl;
        }cout << endl;
    }
    void swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
    }
    void mix_rubik(vector<string> s){
        for (auto i: s) {
            if (i == "U")
                u();
            else if (i == "D")
                d();
            else if (i == "F")
                f();
            else if (i == "R")
                r();
            else if (i == "L")
                l();
            else if (i == "B")
                b();
            else if (i == "U'")
                cu();
            else if (i == "D'")
                cd();
            else if (i == "F'")
                cf();
            else if (i == "R'")
                cr();
            else if (i == "L'")
                cl();
            else if (i == "B'")
                cb();
        }
    }
    void u(){ ///
        for (int i=0; i<2; i++) {
            swap(U[0][0], U[1][0]); swap(U[1][0], U[2][0]);
            swap(U[2][0], U[2][1]); swap(U[2][1], U[2][2]);
            swap(U[2][2], U[1][2]); swap(U[1][2], U[0][2]);
            swap(U[0][2], U[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(L[0][0], L[0][1]); swap(L[0][1], L[0][2]);
            swap(L[0][2], F[0][0]); swap(F[0][0], F[0][1]);
            swap(F[0][1], F[0][2]); swap(F[0][2], R[0][0]);
            swap(R[0][0], R[0][1]); swap(R[0][1], R[0][2]);
            swap(R[0][2], B[0][0]); swap(B[0][0], B[0][1]);
            swap(B[0][1], B[0][2]);
        }
        pro2.push_back("U");
    }
    void d(){ ///
        for (int i=0; i<2; i++) {
            swap(D[0][0], D[1][0]); swap(D[1][0], D[2][0]);
            swap(D[2][0], D[2][1]); swap(D[2][1], D[2][2]);
            swap(D[2][2], D[1][2]); swap(D[1][2], D[0][2]);
            swap(D[0][2], D[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(L[2][0], B[2][2]); swap(B[2][2], B[2][1]);
            swap(B[2][1], B[2][0]); swap(B[2][0], R[2][2]);
            swap(R[2][2], R[2][1]); swap(R[2][1], R[2][0]);
            swap(R[2][0], F[2][2]); swap(F[2][2], F[2][1]);
            swap(F[2][1], F[2][0]); swap(F[2][0], L[2][2]);
            swap(L[2][2], L[2][1]);
        }
        pro2.push_back("D");
    }
    void f(){///
        for (int i=0; i<2; i++) {
            swap(F[0][0], F[1][0]); swap(F[1][0], F[2][0]);
            swap(F[2][0], F[2][1]); swap(F[2][1], F[2][2]);
            swap(F[2][2], F[1][2]); swap(F[1][2], F[0][2]);
            swap(F[0][2], F[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(U[2][0], L[0][2]); swap(L[0][2], L[1][2]);
            swap(L[1][2], L[2][2]); swap(L[2][2], D[0][0]);
            swap(D[0][0], D[0][1]); swap(D[0][1], D[0][2]);
            swap(D[0][2], R[2][0]); swap(R[2][0], R[1][0]);
            swap(R[1][0], R[0][0]); swap(R[0][0], U[2][2]);
            swap(U[2][2], U[2][1]);
        }
        pro2.push_back("F");
    }
    void r(){ ///
        for (int i=0; i<2; i++) {
            swap(R[0][0], R[1][0]); swap(R[1][0], R[2][0]);
            swap(R[2][0], R[2][1]); swap(R[2][1], R[2][2]);
            swap(R[2][2], R[1][2]); swap(R[1][2], R[0][2]);
            swap(R[0][2], R[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(U[2][2], F[0][2]); swap(F[0][2], F[1][2]);
            swap(F[1][2], F[2][2]); swap(F[2][2], D[0][2]);
            swap(D[0][2], D[1][2]); swap(D[1][2], D[2][2]);
            swap(D[2][2], B[2][0]); swap(B[2][0], B[1][0]);
            swap(B[1][0], B[0][0]); swap(B[0][0], U[0][2]);
            swap(U[0][2], U[1][2]);
        }
        pro2.push_back("R");
    }
    void l(){ ///
        for (int i=0; i<2; i++) {
            swap(L[0][0], L[1][0]); swap(L[1][0], L[2][0]);
            swap(L[2][0], L[2][1]); swap(L[2][1], L[2][2]);
            swap(L[2][2], L[1][2]); swap(L[1][2], L[0][2]);
            swap(L[0][2], L[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(U[0][0], B[0][2]); swap(B[0][2], B[1][2]);
            swap(B[1][2], B[2][2]); swap(B[2][2], D[2][0]);
            swap(D[2][0], D[1][0]); swap(D[1][0], D[0][0]);
            swap(D[0][0], F[2][0]); swap(F[2][0], F[1][0]);
            swap(F[1][0], F[0][0]); swap(F[0][0], U[2][0]);
            swap(U[2][0], U[1][0]);
        }
        pro2.push_back("L");
    }
    void b(){ ///
        for (int i=0; i<2; i++) {
            swap(B[0][0], B[1][0]); swap(B[1][0], B[2][0]);
            swap(B[2][0], B[2][1]); swap(B[2][1], B[2][2]);
            swap(B[2][2], B[1][2]); swap(B[1][2], B[0][2]);
            swap(B[0][2], B[0][1]);
        }
        for (int i=0; i<3; i++) {
            swap(L[0][0], U[0][0]); swap(U[0][0], U[0][1]);
            swap(U[0][1], U[0][2]); swap(U[0][2], R[0][2]);
            swap(R[0][2], R[1][2]); swap(R[1][2], R[2][2]);
            swap(R[2][2], D[2][2]); swap(D[2][2], D[2][1]);
            swap(D[2][1], D[2][0]); swap(D[2][0], L[2][0]);
            swap(L[2][0], L[1][0]);
        }
        pro2.push_back("B");
    }
    void cu(){ ///
        for (int i=0; i<2; i++) {
            swap(U[0][0], U[0][1]); swap(U[0][1], U[0][2]);
            swap(U[0][2], U[1][2]); swap(U[1][2], U[2][2]);
            swap(U[2][2], U[2][1]); swap(U[2][1], U[2][0]);
            swap(U[2][0], U[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(L[0][0], B[0][2]); swap(B[0][2], B[0][1]);
            swap(B[0][1], B[0][0]); swap(B[0][0], R[0][2]);
            swap(R[0][2], R[0][1]); swap(R[0][1], R[0][0]);
            swap(R[0][0], F[0][2]); swap(F[0][2], F[0][1]);
            swap(F[0][1], F[0][0]); swap(F[0][0], L[0][2]);
            swap(L[0][2], L[0][1]);
        }
        pro2.push_back("U'");
    }
    void cd(){ ///
        for (int i=0; i<2; i++) {
            swap(D[0][0], D[0][1]); swap(D[0][1], D[0][2]);
            swap(D[0][2], D[1][2]); swap(D[1][2], D[2][2]);
            swap(D[2][2], D[2][1]); swap(D[2][1], D[2][0]);
            swap(D[2][0], D[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(L[2][0], L[2][1]); swap(L[2][1], L[2][2]);
            swap(L[2][2], F[2][0]); swap(F[2][0], F[2][1]);
            swap(F[2][1], F[2][2]); swap(F[2][2], R[2][0]);
            swap(R[2][0], R[2][1]); swap(R[2][1], R[2][2]);
            swap(R[2][2], B[2][0]); swap(B[2][0], B[2][1]);
            swap(B[2][1], B[2][2]);
        }
        pro2.push_back("D'");
    }
    void cf(){ ///
        for (int i=0; i<2; i++) {
            swap(F[0][0], F[0][1]); swap(F[0][1], F[0][2]);
            swap(F[0][2], F[1][2]); swap(F[1][2], F[2][2]);
            swap(F[2][2], F[2][1]); swap(F[2][1], F[2][0]);
            swap(F[2][0], F[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(L[0][2], U[2][0]); swap(U[2][0], U[2][1]);
            swap(U[2][1], U[2][2]); swap(U[2][2], R[0][0]);
            swap(R[0][0], R[1][0]); swap(R[1][0], R[2][0]);
            swap(R[2][0], D[0][2]); swap(D[0][2], D[0][1]);
            swap(D[0][1], D[0][0]); swap(D[0][0], L[2][2]);
            swap(L[2][2], L[1][2]);
        }
        pro2.push_back("F'");
    }
    void cr(){ ///
        for (int i=0; i<2; i++) {
            swap(R[0][0], R[0][1]); swap(R[0][1], R[0][2]);
            swap(R[0][2], R[1][2]); swap(R[1][2], R[2][2]);
            swap(R[2][2], R[2][1]); swap(R[2][1], R[2][0]);
            swap(R[2][0], R[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(U[2][2], U[1][2]); swap(U[1][2], U[0][2]);
            swap(U[0][2], B[0][0]); swap(B[0][0], B[1][0]);
            swap(B[1][0], B[2][0]); swap(B[2][0], D[2][2]);
            swap(D[2][2], D[1][2]); swap(D[1][2], D[0][2]);
            swap(D[0][2], F[2][2]); swap(F[2][2], F[1][2]);
            swap(F[1][2], F[0][2]);
        }
        pro2.push_back("R'");
    }
    void cl(){ ///
        for (int i=0; i<2; i++) {
            swap(L[0][0], L[0][1]); swap(L[0][1], L[0][2]);
            swap(L[0][2], L[1][2]); swap(L[1][2], L[2][2]);
            swap(L[2][2], L[2][1]); swap(L[2][1], L[2][0]);
            swap(L[2][0], L[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(B[0][2], U[0][0]); swap(U[0][0], U[1][0]);
            swap(U[1][0], U[2][0]); swap(U[2][0], F[0][0]);
            swap(F[0][0], F[1][0]); swap(F[1][0], F[2][0]);
            swap(F[2][0], D[0][0]); swap(D[0][0], D[1][0]);
            swap(D[1][0], D[2][0]); swap(D[2][0], B[2][2]);
            swap(B[2][2], B[1][2]);
        }
        pro2.push_back("L'");
    }
    void cb(){ ///
        for (int i=0; i<2; i++) {
            swap(B[0][0], B[0][1]); swap(B[0][1], B[0][2]);
            swap(B[0][2], B[1][2]); swap(B[1][2], B[2][2]);
            swap(B[2][2], B[2][1]); swap(B[2][1], B[2][0]);
            swap(B[2][0], B[1][0]);
        }
        for (int i=0; i<3; i++) {
            swap(L[0][0], L[1][0]); swap(L[1][0], L[2][0]);
            swap(L[2][0], D[2][0]); swap(D[2][0], D[2][1]);
            swap(D[2][1], D[2][2]); swap(D[2][2], R[2][2]);
            swap(R[2][2], R[1][2]); swap(R[1][2], R[0][2]);
            swap(R[0][2], U[0][2]); swap(U[0][2], U[0][1]);
            swap(U[0][1], U[0][0]);
        }
        pro2.push_back("B'");
    }
    ~Rubik(){
    }
};

class Solve{
public:
    Rubik temp;
    Solve (Rubik &tmp) : temp(tmp){
    };
    void whiteCross(){
        while (temp.U[0][1]!=6 || temp.U[1][0]!=6 || temp.U[1][2]!=6 || temp.U[2][1]!=6) {
            // side D
            if (temp.D[0][1] == 6) {
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.f(); temp.f();
            }
            if (temp.D[1][0] == 6) {
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.l(); temp.l();
            }
            if (temp.D[2][1] == 6) {
                while (temp.U[0][1] == 6)
                    temp.u();
                temp.b(); temp.b();
            }
            if (temp.D[1][2] == 6) {
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.r(); temp.r();
            }
            // side F
            if (temp.F[1][0] == 6) {
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.cl();
            }
            if (temp.F[1][2] == 6) {
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.r();
            }
            if (temp.F[0][1] == 6) {
                temp.f();
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.r();
            }
            if (temp.F[2][1] == 6) {
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.f();
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.cl();
            }
            // side L
            if (temp.L[0][1] == 6) {
                temp.l();
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.f();
            }
            if (temp.L[1][0] == 6) {
                while (temp.U[0][1] == 6)
                    temp.u();
                temp.cb();
            }
            if (temp.L[1][2] == 6) {
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.f();
            }
            if (temp.L[2][1] == 6) {
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.cl();
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.f();
            }
            // side R
            if (temp.R[0][1] == 6) {
                temp.cr();
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.cf();
            }
            if (temp.R[1][0] == 6) {
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.cf();
            }
            if (temp.R[1][2] == 6) {
                while (temp.U[0][1] == 6)
                    temp.u();
                temp.b();
            }
            if (temp.R[2][1] == 6) {
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.r();
                while (temp.U[2][1] == 6)
                    temp.u();
                temp.cf();
            }
            // side B
            if (temp.B[0][1] == 6) {
                temp.b();
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.l();
            }
            if (temp.B[1][0] == 6) {
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.cr();
            }
            if (temp.B[1][2] == 6) {
                while (temp.U[1][0] == 6)
                    temp.u();
                temp.l();
            }
            if (temp.B[2][1] == 6) {
                while (temp.U[0][1] == 6)
                    temp.u();
                temp.b();
                while (temp.U[1][2] == 6)
                    temp.u();
                temp.cr();
            }
        }
        while (temp.F[0][1] != temp.F[1][1] || temp.U[2][1] != 6)
            temp.u();
        temp.f(); temp.f();
        while (temp.R[0][1] != temp.R[1][1] || temp.U[1][2] != 6)
            temp.u();
        temp.r(); temp.r();
        while (temp.B[0][1] != temp.B[1][1] || temp.U[0][1] != 6)
            temp.u();
        temp.b(); temp.b();
        while (temp.L[0][1] != temp.L[1][1] || temp.U[1][0] != 6)
            temp.u();
        temp.l(); temp.l();
    }
    void complete_first_floor(){
        if (temp.L[2][2] == 6 || temp.F[2][0] == 6 || temp.D[0][0] == 6) {
            while (temp.U[2][0] == 6 || temp.F[0][0] == 6 || temp.L[0][2] == 6)
                temp.u();
            temp.cl(); temp.cu(); temp.l();
        }
        if (temp.F[2][2] == 6 || temp.D[0][2] == 6 || temp.R[2][0] == 6) {
            while (temp.U[2][2] == 6 || temp.F[0][2] == 6 || temp.R[0][0] == 6)
                temp.u();
            
            temp.r(); temp.u(); temp.cr();
        }
        if (temp.R[2][2] == 6 || temp.D[2][2] == 6 || temp.B[2][0] == 6) {
            while (temp.U[0][2] == 6 || temp.R[0][2] == 6 || temp.B[0][0] == 6)
                temp.u();
            temp.b(); temp.u(); temp.cb();
        }
        if (temp.L[2][0] == 6 || temp.D[2][0] == 6 || temp.B[2][2] == 6) {
            while (temp.U[0][0] == 6 || temp.L[0][0] == 6 || temp.B[0][2] == 6)
                temp.u();
            temp.l(); temp.u(); temp.cl();
        }
        
        while (!((temp.U[2][2]==2 && temp.F[0][2]==3 && temp.R[0][0]==6) ||
               (temp.U[2][2]==2 && temp.F[0][2]==6 && temp.R[0][0]==3) ||
               (temp.U[2][2]==3 && temp.F[0][2]==2 && temp.R[0][0]==6) ||
               (temp.U[2][2]==3 && temp.F[0][2]==6 && temp.R[0][0]==2) ||
               (temp.U[2][2]==6 && temp.F[0][2]==2 && temp.R[0][0]==3) ||
                 (temp.U[2][2]==6 && temp.F[0][2]==3 && temp.R[0][0]==2)))
            temp.u();
        while (temp.F[2][2]!=2 || temp.R[2][0]!=3 || temp.D[0][2]!=6){
            temp.r(); temp.u(); temp.cr(); temp.cu();
        }
        while (!((temp.U[0][2]==3 && temp.R[0][2]==4 && temp.B[0][0]==6) ||
                 (temp.U[0][2]==3 && temp.R[0][2]==6 && temp.B[0][0]==4) ||
                 (temp.U[0][2]==4 && temp.R[0][2]==3 && temp.B[0][0]==6) ||
                 (temp.U[0][2]==4 && temp.R[0][2]==6 && temp.B[0][0]==3) ||
                 (temp.U[0][2]==6 && temp.R[0][2]==3 && temp.B[0][0]==4) ||
                 (temp.U[0][2]==6 && temp.R[0][2]==4 && temp.B[0][0]==3)))
            temp.u();
        while (temp.R[2][2]!=3 || temp.B[2][0]!=4 || temp.D[2][2]!=6) {
            temp.b(); temp.u(); temp.cb(); temp.cu();
        }
        while (!((temp.U[2][0]==2 && temp.F[0][0]==5 && temp.L[0][2]==6) ||
                 (temp.U[2][0]==2 && temp.F[0][0]==6 && temp.L[0][2]==5) ||
                 (temp.U[2][0]==5 && temp.F[0][0]==2 && temp.L[0][2]==6) ||
                 (temp.U[2][0]==5 && temp.F[0][0]==6 && temp.L[0][2]==2) ||
                 (temp.U[2][0]==6 && temp.F[0][0]==2 && temp.L[0][2]==5) ||
                 (temp.U[2][0]==6 && temp.F[0][0]==5 && temp.L[0][2]==2)))
            temp.u();
        while (temp.L[2][2]!=5 || temp.F[2][0]!=2 || temp.D[0][0]!=6) {
            temp.f(); temp.u(); temp.cf(); temp.cu();
        }
        while (!((temp.U[0][0]==4 && temp.L[0][0]==5 && temp.B[0][2]==6) ||
                 (temp.U[0][0]==4 && temp.L[0][0]==6 && temp.B[0][2]==5) ||
                 (temp.U[0][0]==5 && temp.L[0][0]==4 && temp.B[0][2]==6) ||
                 (temp.U[0][0]==5 && temp.L[0][0]==6 && temp.B[0][2]==4) ||
                 (temp.U[0][0]==6 && temp.L[0][0]==4 && temp.B[0][2]==5) ||
                 (temp.U[0][0]==6 && temp.L[0][0]==5 && temp.B[0][2]==4) ))
            temp.u();
        while (temp.L[2][0]!=5 || temp.B[2][2]!=4 || temp.D[2][0]!=6) {
            temp.l(); temp.u(); temp.cl(); temp.cu();
        }
    }
    void complete_second_floor(){
        if (temp.F[1][2] != 1 && temp.R[1][0] != 1) { // 1 yellow
            while (!((temp.L[0][1]==1 && temp.U[1][0]!=1) ||
                (temp.L[0][1]!=1 && temp.U[1][0]==1)))
                temp.u();
            temp.r(); temp.cu(); temp.cr(); temp.cu(); temp.cf(); temp.u(); temp.f();
        }
        if (temp.R[1][2] != 1 && temp.B[1][0] != 1) {
            while (!((temp.U[2][1]==1 && temp.F[0][1]!=1) ||
                     (temp.U[2][1]!=1 && temp.F[0][1]==1)))
                temp.u();
            temp.b(); temp.cu(); temp.cb(); temp.cu(); temp.cr(); temp.u(); temp.r();
        }
        if (temp.F[1][0] != 1 && temp.L[1][2] != 1) {
            while (!((temp.U[0][1]==1 && temp.B[0][1]!=1) ||
                     (temp.U[0][1]!=1 && temp.B[0][1]==1)))
                temp.u();
            temp.f(); temp.cu(); temp.cf(); temp.cu(); temp.cl(); temp.u(); temp.l();
        }
        if (temp.L[1][0] != 1 && temp.B[1][2] != 1) {
            while (!((temp.U[1][2]==1 && temp.R[0][1]!=1) ||
                     (temp.U[1][2]!=1 && temp.R[0][1]==1)))
                temp.u();
            temp.l(); temp.cu(); temp.cl(); temp.cu(); temp.cb(); temp.u(); temp.b();
        }
        while (1) {
            if (temp.L[1][0]==5 && temp.L[1][2]==5 && temp.F[1][0]==2 && temp.F[1][2]==2 &&
                temp.R[1][0]==3 && temp.R[1][2]==3 && temp.B[1][0]==4 && temp.B[1][2]==4) {
                return;
            }
            if (temp.F[0][1]==2 && temp.U[2][1]!=1) {
                if (temp.U[2][1]==5) {
                    temp.cu(); temp.cl(); temp.u(); temp.l();
                    temp.u(); temp.f(); temp.cu(); temp.cf();
                }
                else if(temp.U[2][1]==3){
                    temp.u(); temp.r(); temp.cu(); temp.cr();
                    temp.cu(); temp.cf(); temp.u(); temp.f();
                }
            }
            if (temp.R[0][1]==3 && temp.U[1][2]!=1) {
                if (temp.U[1][2]==2) {
                    temp.cu(); temp.cf(); temp.u(); temp.f();
                    temp.u(); temp.r(); temp.cu(); temp.cr();
                }
                else if(temp.U[1][2]==4){
                    temp.u(); temp.b(); temp.cu(); temp.cb();
                    temp.cu(); temp.cr(); temp.u(); temp.r();
                }
            }
            if (temp.B[0][1]==4 && temp.U[0][1]!=1) {
                if (temp.U[0][1]==3) {
                    temp.cu(); temp.cr(); temp.u(); temp.r();
                    temp.u(); temp.b(); temp.cu(); temp.cb();
                }
                else if(temp.U[0][1]==5){
                    temp.u(); temp.l(); temp.cu(); temp.cl();
                    temp.cu(); temp.cb(); temp.u(); temp.b();
                }
            }
            if (temp.L[0][1]==5 && temp.U[1][0]!=1) {
                if (temp.U[1][0]==2) {
                    temp.u(); temp.f(); temp.cu(); temp.cf();
                    temp.cu(); temp.cl(); temp.u(); temp.l();
                }
                else if (temp.U[1][0]==4){
                    temp.cu(); temp.cb(); temp.u(); temp.b();
                    temp.u(); temp.l(); temp.cu(); temp.cl();
                }
            }
            temp.u();
        }
    }
    void yellowCross(){
        while (!(temp.U[0][1]==1 && temp.U[1][0]==1 && temp.U[1][2]==1 && temp.U[2][1]==1)){
            if (temp.U[0][1]==1 && temp.U[2][1]==1) {
                temp.u();
                temp.f(); temp.r(); temp.u(); temp.cr(); temp.cu(); temp.cf();
                return;
            }
            if (temp.U[1][0]==1 && temp.U[1][2]==1) {
                temp.f(); temp.r(); temp.u(); temp.cr(); temp.cu(); temp.cf();
                return;
            }
            if ((temp.U[0][1]==1 && temp.U[1][0]==1) || (temp.U[0][1]==1 && temp.U[1][2]==1) || (temp.U[1][0]==1 && temp.U[2][1]==1) || (temp.U[1][2]==1 && temp.U[2][1]==1)) {
                while (!(temp.U[0][1]==1 && temp.U[1][0]==1))
                    temp.u();
                temp.f(); temp.r(); temp.u(); temp.cr(); temp.cu(); temp.cf();
                temp.f(); temp.r(); temp.u(); temp.cr(); temp.cu(); temp.cf();
                return;
            }
            else{ // only 1 dot yellow
                temp.f(); temp.r(); temp.u(); temp.cr(); temp.cu(); temp.cf();
            }
        }
        
    }
    void complete_side_yellow(){
        if (temp.U[0][0]==1 && temp.U[0][2]==1 && temp.U[2][0]==1 && temp.U[2][2]==1)
            return;
        while (!((temp.U[0][0]==1 && temp.U[0][2]==1 && temp.F[0][0]==1 && temp.F[0][2]==1) ||
                 (temp.U[0][2]==1 && temp.U[2][2]==1 && temp.F[0][0]==1 && temp.B[0][2]==1) ||
                 (temp.U[0][0]==1 && temp.U[2][2]==1 && temp.F[0][0]==1 && temp.R[0][2]==1) ||
                 (temp.L[0][0]==1 && temp.L[0][2]==1 && temp.R[0][0]==1 && temp.R[0][2]==1) ||
                 (temp.L[0][0]==1 && temp.L[0][2]==1 && temp.F[0][2]==1 && temp.B[0][0]==1) ||
                 (temp.U[2][0]==1 && temp.L[0][0]==1 && temp.R[0][0]==1 && temp.B[0][0]==1) ||
                 (temp.U[2][0]==1 && temp.F[0][2]==1 && temp.R[0][2]==1 && temp.B[0][2]==1)))
            temp.u();
        if ((temp.U[0][0]==1 && temp.U[0][2]==1 && temp.F[0][0]==1 && temp.F[0][2]==1) ||
            (temp.U[0][2]==1 && temp.U[2][2]==1 && temp.F[0][0]==1 && temp.B[0][2]==1) ||
            (temp.U[0][0]==1 && temp.U[2][2]==1 && temp.F[0][0]==1 && temp.R[0][2]==1)) {
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
            while (temp.U[2][0]!=1)
                temp.u();
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
            while (temp.U[2][0]!=1)
                temp.u();
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
        }
        if ((temp.L[0][0]==1 && temp.L[0][2]==1 && temp.R[0][0]==1 && temp.R[0][2]==1) ||
            (temp.L[0][0]==1 && temp.L[0][2]==1 && temp.F[0][2]==1 && temp.B[0][0]==1)) {
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
            while (temp.U[2][0]!=1)
                temp.u();
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
        }
        if ((temp.U[2][0]==1 && temp.L[0][0]==1 && temp.R[0][0]==1 && temp.B[0][0]==1)) {
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
            while (temp.U[2][0]!=1)
                temp.u();
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
        }
        if (temp.U[2][0]==1 && temp.F[0][2]==1 && temp.R[0][2]==1 && temp.B[0][2]==1) {
            temp.r(); temp.u(); temp.cr(); temp.u();
            temp.r(); temp.u(); temp.u(); temp.cr();
        }
        
    }
    void complete_corner_3rdfloor(){
        if (temp.L[0][0]==temp.L[0][2] && temp.F[0][0]==temp.F[0][2] &&
            temp.R[0][0]==temp.R[0][2] && temp.B[0][0]==temp.B[0][2]) {
            while (temp.F[0][0]!=2)
                temp.u();
            return;
        }
        if(temp.L[0][0]!=temp.L[0][2] && temp.F[0][0]!=temp.F[0][2] &&
            temp.R[0][0]!=temp.R[0][2] && temp.B[0][0]!=temp.B[0][2]) {
            while (!(temp.L[0][2]==5 && temp.F[0][0]==2))
                temp.u();
            temp.r(); temp.u(); temp.cr(); temp.cf(); temp.r(); temp.u();
            temp.cr(); temp.cu(); temp.cr(); temp.f(); temp.r(); temp.r();
            temp.cu(); temp.cr(); temp.cu();
        }
        while (temp.F[0][0]!=2)
            temp.u();
        if (temp.F[0][2]==2) {
            if (temp.B[0][0]==4 && temp.B[0][2]==4)
                return;
            else{
                temp.b(); temp.u(); temp.cb(); temp.cr(); temp.b(); temp.u();
                temp.cb(); temp.cu(); temp.cb(); temp.r(); temp.b(); temp.b();
                temp.cu(); temp.cb(); temp.cu();
                return;
            }
        }
        while (temp.L[0][0]!=5)
            temp.u();
        if (temp.L[0][2]==5) {
            if (temp.R[0][0]==3 && temp.R[0][2]==3)
                return;
            temp.r(); temp.u(); temp.cr(); temp.cf(); temp.r(); temp.u();
            temp.cr(); temp.cu(); temp.cr(); temp.f(); temp.r(); temp.r();
            temp.cu(); temp.cr(); temp.cu();
            return;
        }
        while (temp.R[0][0]!=3)
            temp.u();
        if (temp.R[0][2]==3) {
            if (temp.L[0][0]==5 && temp.L[0][2]==5)
                return;
            temp.l(); temp.u(); temp.cl(); temp.cb(); temp.l(); temp.u();
            temp.cl(); temp.cu(); temp.cl(); temp.b(); temp.l(); temp.l();
            temp.cu(); temp.cl(); temp.cu();
            return;
        }
        while (temp.B[0][0]!=4)
            temp.u();
        if (temp.B[0][2]==4) {
            if (temp.F[0][0]==2 && temp.F[0][2]==2)
                return;
            temp.f(); temp.u(); temp.cf(); temp.cl(); temp.f(); temp.u();
            temp.cf(); temp.cu(); temp.cf(); temp.l(); temp.f(); temp.f();
            temp.cu(); temp.cf(); temp.cu();
            return;
        }
    }
    void complete_rubik(){
        if (temp.F[0][1]==2 && temp.L[0][1]==5 && temp.R[0][1]==3 && temp.B[0][1]==4)
            return;
        if (temp.F[0][1]!=2 && temp.L[0][1]!=5 && temp.R[0][1]!=3 && temp.B[0][1]!=4) {
            temp.r(); temp.r(); temp.u(); temp.r(); temp.u(); temp.cr();
            temp.cu(); temp.cr(); temp.cu(); temp.cr(); temp.u(); temp.cr();
        }
        if (temp.B[0][1]==4) {
            while (!(temp.L[0][1]==5 && temp.F[0][1]==2 && temp.R[0][1]==3)) {
                temp.r(); temp.r(); temp.u(); temp.r(); temp.u(); temp.cr();
                temp.cu(); temp.cr(); temp.cu(); temp.cr(); temp.u(); temp.cr();
            }
        }
        if (temp.L[0][1]==5) {
            while (!(temp.B[0][1]==4 && temp.F[0][1]==2 && temp.R[0][1]==3)) {
                temp.b(); temp.b(); temp.u(); temp.b(); temp.u(); temp.cb();
                temp.cu(); temp.cb(); temp.cu(); temp.cb(); temp.u(); temp.cb();
            }
        }
        if (temp.F[0][1]==2) {
            while (!(temp.L[0][1]==5 && temp.B[0][1]==4 && temp.R[0][1]==3)) {
                temp.l(); temp.l(); temp.u(); temp.l(); temp.u(); temp.cl();
                temp.cu(); temp.cl(); temp.cu(); temp.cl(); temp.u(); temp.cl();
            }
        }
        if (temp.R[0][1]==3) {
            while (!(temp.L[0][1]==5 && temp.B[0][1]==4 && temp.F[0][1]==2)) {
                temp.f(); temp.f(); temp.u(); temp.f(); temp.u(); temp.cf();
                temp.cu(); temp.cf(); temp.cu(); temp.cf(); temp.u(); temp.cf();
            }
        }
    }
    void quick_solve(){
        whiteCross();
        complete_first_floor();
        complete_second_floor();
        yellowCross();
        complete_side_yellow();
        complete_corner_3rdfloor();
        complete_rubik();
    }
    void printRR (){
        temp.print();
        cout << endl;
    }
    void printPro(){
        for (auto i: temp.pro2)
            cout << i << "  ";
        cout << endl;
    }
    ~Solve(){
    }
};

int main(int argc, const char * argv[]) {
    ifstream fin("/Users/tranhoangnam/Desktop/Programing/lab6/lab6/lab6/in.txt");
    string s;
    vector<string> SS;
    for (int i=0; i<10; i++) {
        fin >> s;
        SS.push_back(s);
    }
    cout << endl;
    Rubik A;
    A.mix_rubik(SS);
    A.print();
    Solve RRubik(A);
    //RRubik.whiteCross();
    //RRubik.complete_first_floor();
    //RRubik.complete_second_floor();
    //RRubik.yellowCross();
    //RRubik.complete_side_yellow();
    //RRubik.complete_corner_3rdfloor();
    //RRubik.complete_rubik();
    RRubik.quick_solve();
    RRubik.printRR();
    RRubik.printPro();
    return 0;
}
