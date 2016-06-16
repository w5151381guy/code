#ifndef BANKER_H
#define BANKER_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;
class banker{
public:
  void setrequest(string str);                        //set request
  void setneed();                                     //set need
  void setinitial();                                  //set initial process sequence
  void wait();                                        //let waiting process start
  void valuetype(string str,int count);               //string to int
  void setinput(int input[50],int size,int count);    //set input to vector
  void banker_algorithm(int pid);                     //banker's algorithm
  void safety_alogorithm(int pid);                    //safety algorithm
private:
  vector<int> avail;                   //array for available
  vector<vector<int> > max;            //array for maximum
  vector<vector<int> > allocated;      //array for allocated
  vector<int> request;                 //array for request
  vector<vector<int> > need;           //array for need
  vector<int> sequence;                //array of process sequence
  vector<vector<int> > waiting;        //array for waiting quene
};
#endif
