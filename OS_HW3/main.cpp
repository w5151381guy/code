#include <iostream>
#include <string>
#include <vector>
using namespace std;
void OPT(vector<string> str){

}
void LRU(vector<string> str){

}
int main(int argc,char *argv[]){
  string input;
  vector<string> str;        //vector string for input
  int length,frame;          //length = reference string length
  cin >> length >> frame;
  for(int i = 0 ; i < length ; i++){
    cin >> input;
    str.push_back(input);
  }
  if(argv[1] == 0)
    OPT(str);
  else
    LRU(str);
  return 0;
}
