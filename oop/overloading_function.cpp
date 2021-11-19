/*
Overloading saves us memory in the system. Creating new functions is more costly compared to overloading a single one.
Since they are memory-efficient, overloaded functions are compiled faster compared to different functions, 
especially if the list of functions is long.

An obvious benefit is that the code becomes simple and clean. We don’t have to keep track of different functions.

Compile and run: g++ overloading_function.cpp -o olf && ./olf
*/

#include <bits/stdc++.h>
using namespace std;

double product(double x, double y){
    return x*y;
}
double product(double x, double y, double z){
    return x*y*z;
}
int product(int x, int y){
    cout << "int" << endl;
    return x*y;
}

int main(){
    double x=2.3, y=5.1;
    int a=4, b=5, c=10;
    cout << product(x, y) << endl;
    cout << product(a, b) << endl;
    // cout << product(x, b) << endl; //its ambiguous, give error
}