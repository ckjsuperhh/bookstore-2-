#include<iostream>
#include"cmd.h"
using namespace std;

[[noreturn]] int main() {
   string str;
   cmd::initialise();
   while (true) {
      try {
         bool ok=true;
         while (getline(cin,str)) {
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
