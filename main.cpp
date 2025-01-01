#include<iostream>
#include"cmd.h"
using namespace std;

[[noreturn]] int main() {
   string str;
   // int cnt=0;
   cmd::initialise();
   while (true) {
      try {
         bool ok=true;
         while (getline(cin,str)) {
            // cout<<++cnt<<std::endl;
            // cout<<str<<std::endl;
            ok=false;
            cmd::analyse(str);
         }
         if (ok) {
            return 0;
         }
      }catch (...) {
         cout<<"Invalid\n";
      }
   }
}
