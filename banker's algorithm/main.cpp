#include "banker.h"
using namespace std;
int main(){
  banker bank;
  string str;
  int count = 0;                //count number of comment out
  while(getline(cin,str,'\n')){
    if(str[0] == '#')
      count++;
    else{
      if(count == 4)            //special case for request
        bank.setrequest(str);
      else
        bank.valuetype(str,count);
    }
  }
  cout << "-FIN-" << endl;
  return 0;
}
