#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
using namespace std;
void OPT(vector<string> str,int frame){
  vector<string> str1;              //vector to compare every page
  vector<vector<string> > vec;      //vector for print every page
  int counter = 0;                  //counter for page fault
  str1.push_back(str[0]);
  vec.push_back(str1);
  counter++;
  for(int i = 1 ; i < str.size() ; i++){
    bool check = false;
    for(int j = 0 ; j < str1.size() ; j++){
      if(str[i] == str1[j])
        check = true;
    }
    if(check == false){
      counter++;
      if(str1.size() < frame)
        str1.push_back(str[i]);
      else{
        int count[frame];
        /*count the position of frame*/
        for(int k = 0 ; k < frame ; k++){
          for(int l = i + 1 ; l < str.size() ; l++){
            if(str1[k] == str[l]){
              count[k] = l - i;
              break;
            }
          }
        }
        int p = 0;
        /*find the position to replace*/
        for (int k = 1; k < frame; k++){
          if (count[k] > count[p])
              p = k;
        }
        str1[p] = str[i];
      }
    }
    vec.push_back(str1);
  }
  cout << counter << endl;
  for(int i = 0 ; i < vec.size() ; i++){
    sort(vec[i].begin(),vec[i].end());
    for(int j = vec[i].size() - 1 ; j >= 0 ; j--)
      cout << vec[i][j] << " ";
    cout << endl;
  }
}
void LRU(vector<string> str,int frame){
  vector<string> str1;              //vector to compare every page
  vector<vector<string> > vec;      //vector for print every page
  int counter = 0;                  //counter for page fault
  str1.push_back(str[0]);
  vec.push_back(str1);
  counter++;
  for(int i = 1 ; i < str.size() ; i++){
    bool check = false;
    for(int j = 0 ; j < str1.size() ; j++){
      if(str[i] == str1[j]){
        check = true;
        str1.insert(str1.end(),str[i]);
        str1.erase(str1.begin() + j);
      }
    }
    if(check == false){
      counter++;
      if(str1.size() < frame)
        str1.push_back(str[i]);
      else{
        str1.erase(str1.begin());
        str1.push_back(str[i]);
      }
    }
    vec.push_back(str1);
  }
  cout << counter << endl;
  for(int i = 0 ; i < vec.size() ; i++){
    sort(vec[i].begin(),vec[i].end());
    for(int j = vec[i].size() - 1 ; j >= 0 ; j--)
      cout << vec[i][j] << " ";
    cout << endl;
  }
}
int main(int argc,char *argv[]){
  fstream file;
  file.open(argv[2],ios::in);
  string input;
  vector<string> str;        //vector string for input
  int length,frame;          //length = reference string length
  file >> length >> frame;
  while(file >> input)
    str.push_back(input);
  int mode = atoi(argv[1]);
  if(mode == 0)
    OPT(str,frame);
  else
    LRU(str,frame);
  return 0;
}
