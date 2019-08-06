#include"2018201034_4.cpp"
#include<stdio.h>

int main(){
    vector v;
    vector v1(3);
    vector v2(15);
    for(int i=1;i<15;i++){
        v1.push_back(i);
        cout << v1.getcapacity() << endl;
    } 
    cout << v1[2] << " " << v1[4] << " " << v1[8] << endl;
    v1.erase(0);
    v1.erase(5);
    v1.insert(0,1);
    v1.insert(4,5);
    v1.push_back(22);
    cout << v1.front() << " " << v1.back() << endl;
    for(int i=0;i<v1.size();i++) cout << v1[i] << " ";
    int x=v1.size();
    for(int i=1;i<x;i++){
        v1.pop_back();
        cout << v1.getcapacity() << endl;
    } 
    cout << endl;
    v1.clear();
    v1.push_back(712);
    for(int i=0;i<v1.size();i++) cout << v1[i] << " ";
    cout << endl;
    return 0;
}