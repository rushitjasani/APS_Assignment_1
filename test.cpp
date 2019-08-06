#include <iostream>
#include "2018201034_4.cpp"

using namespace std;
int main(){
  vector v;
  cout<<"size"<<v.size()<<endl;
  for(int i=0;i<10;i++)
  v.push_back(i);
  cout<<"size"<<v.size()<<endl;
  v.insert(100,90);
  v.erase(2);
  for(int i=0;i<v.size();i++){
    cout<<v[i]<<" ";
  }
  cout<<endl;
  cout<<"Front"<<v.front()<<endl;
  cout<<"Back"<<v.back()<<endl;
  v.pop_back();
  cout<<"\nValue popped\n";
  for(int i=0;i<v.size();i++){
    cout<<v[i]<<" ";
  }
  cout<<endl;
  v.insert(4,20);
  cout<<"\value inserted\n";
  for(int i=0;i<v.size();i++){
    cout<<v[i]<<" ";
  }
  v.erase(3);
  cout<<"\nvalue erased\n";
  for(int i=0;i<v.size();i++){
    cout<<v[i]<<" ";
  }
  cout<<"\nsize is "<<v.size()<<endl;
  vector b;
  cout<<b.size()<<endl;
  for(int i=0;i<9;i++)
  b.push_back(3);
  cout<<b.size()<<endl;
  for(int i=0;i<8;i++){
    b.pop_back();
  }
  cout<<b.size()<<endl;
}
