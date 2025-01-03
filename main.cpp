#include<iostream>
#include"cmd.h"
using namespace std;

[[noreturn]] int main() {
   string str;
   cmd::initialise();
   while (true) {
      try {
         bool ok=true;
         while (getline(cin,str) and not cin.eof()) {
            ok=false;
            cmd::analyse(str);
         }
         if (ok or cin.eof()) {
            exit(0);
         }
      }catch (...) {
         cout<<"Invalid\n";
      }
   }
}
