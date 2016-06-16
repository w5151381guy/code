#include "banker.h"
using namespace std;
void banker::valuetype(string str,int count){
  /*string to integer*/
  stringstream ss(str);
  string sub_str;
  int size = 0;
  int input[50];
  while(getline(ss,sub_str,' ')){
    ss >> input[size++];
  }
  setinput(input,size,count);
}
void banker::setinput(int input[50],int size,int count){
  /*count = 1 -> available ; count = 2 -> maximum ; count = 3 -> allocated*/
  vector<int> vec;
  if(count == 1){
    for(int i = 0 ; i < size ; i++)
      avail.push_back(input[i]);
  }
  if(count == 2){
    for(int i = 0 ; i < size ; i++)
      vec.push_back(input[i]);
    max.push_back(vec);
    vec.clear();
  }
  if(count == 3){
    for(int i = 0 ; i < size ; i++)
      vec.push_back(input[i]);
    allocated.push_back(vec);
    vec.clear();
    if(allocated.size() == max.size())
      setneed();
  }
}
void banker::setneed(){
  vector<int> vec;
  int Need;
  for(size_t i = 0 ; i < max.size() ; i++){
    for(size_t j = 0 ; j < max[i].size() ; j++){
      Need = max[i][j] - allocated[i][j];
      vec.push_back(Need);
    }
    need.push_back(vec);
    vec.clear();
  }
  setinitial();
}
void banker::setinitial(){
  /*check whether need <= available*/
  int count,sequen[50],waiting[50];
  int size1 = 0,size2 = 0;
  int counter = 0;                //count how many time of need > available
  for(size_t i = 0 ; i < need.size() ; i++){
    count = 0;
    for(size_t j = 0 ; j < need[i].size() ; j++){
      if(need[i][j] > avail[j])
        count++;
    }
    if(count != 0){
      counter++;
      waiting[size2++] = i;
    }
    else
      sequen[size1++] = i;
  }
  if(counter == need.size()){
    cout << "Initial state: " << "unsafe" << endl;
    exit(0);
  }
  else{
    cout << "Initial state: " << "safe, (";
    for(int i = 0 ; i < size1 ; i++){
      sequence.push_back(sequen[i]);
      if(i == size1 - 1 && size2 == 0)
        cout << sequen[i] << ")" << endl;
      else
        cout << sequen[i] << ",";
    }
    for(int i = 0 ; i < size2 ; i++){
      sequence.push_back(waiting[i]);
      if(i == size2 - 1)
        cout << waiting[i] << ")" << endl;
      else
        cout << waiting[i] << ",";
    }
  }
}
void banker::setrequest(string str){
  /*allocated -> 1 ; release -> 0*/
  request.clear();
  stringstream ss(str);
  string sub_str;
  int pid,resource;
  ss >> pid;
  request.push_back(pid);
  while(getline(ss,sub_str,' ')){
    ss >> resource;
    request.push_back(resource);
  }
  request.pop_back();
  if(str[str.length() - 1] == 'a')
    request.push_back(1);
  else
    request.push_back(0);
  cout << "(";
  for(int i = 0 ; i < request.size() - 1; i++){
    if(i == request.size() - 2)
      cout << request[i] << "): ";
    else
      cout << request[i] << ",";
  }
  banker_algorithm(pid);
}
void banker::banker_algorithm(int pid){
  /*request process to allocated*/
  if(request[request.size() - 1] == 1){
    bool check = true;
    for(int i = 0 ; i < avail.size() ; i++){
      if(request[i + 1] > need[pid][i]){
        check = false;
        cout << "Not granted, Request > Need, discard request" << endl;
        break;
      }
      if(request[i + 1] > avail[i]){
        check = false;
        waiting.push_back(request);
        cout << "Not granted, Request > Available, put to waiting_quene" << endl;
        break;
      }
    }
    if(check == true){
      for(int i = 0 ; i < allocated[pid].size() ; i++){
        avail[i] = avail[i] - request[i + 1];        //available = available - request
        need[pid][i] = need[pid][i] - request[i + 1];  //need = need - request
        allocated[pid][i] = allocated[pid][i] + request[i + 1];  //allocated = allocated + request
      }
      cout<<"granted,(";
      int count = 0;
      for(int i = 0 ; i < need[pid].size() ; i++){
        if(need[pid][i] == 0)
          count++;
      }
      if(count == need[pid].size())
        sequence.erase(sequence.begin() + pid - 1);
      for(int i=0;i<sequence.size();i++){
        if(i==sequence.size()-1)
          cout<<sequence[i]<<")"<<endl;
        else
          cout<<sequence[i]<<",";
      }
      //safety_alogorithm(pid);
    }
  }
  /*request process to release*/
  else{
    bool check = true;
    for(int i = 0 ; i < allocated[pid].size() ; i++){
      if(request[i + 1] > allocated[pid][i])
        check = false;
    }
    if(check == true){
      for(int i = 0 ; i < allocated[pid].size() ; i++){
        allocated[pid][i] = allocated[pid][i] - request[i + 1];   //allocated = allocated - request
        avail[i] = avail[i] + request[i + 1];        //available = available + request
      }
      cout << "granted, release granted" << endl;
      wait();
    }
    else
      cout << "Not granted, Request > Allocated, discard request" << endl;
  }
}
void banker::safety_alogorithm(int pid){
  vector<int> work;
  vector<bool> finish;
  work.clear();finish.clear();
  int count = 0;
  /*set work,initial value = available*/
  for(int i = 0 ; i < avail.size() ; i++)
    work[i] = avail[i];
  /*set finish,initial state = false*/
  for(int i = 0 ; i < sequence.size() ; i++)
    finish[i] = false;
  /*check whether need < work,if yes -> finish = true,else -> finish = false*/
  for(int i = 0 ; i < need[pid].size() ; i++){
    if(need[pid][i] <= work[i])
      count++;
  }
  if(count == need[pid].size()){
    for(int i = 0 ; i < need[pid].size() ; i++)
      work[i] = work[i] + allocated[pid][i];     //work = work + allocated
    finish[pid] = true;
  }
  /*check if every process can work success*/
  for(int i = 0 ; i < sequence.size() ; i++){
    count = 0;
    for(int j = 0 ; j < need[sequence[i]].size() ; j++){
      if(need[sequence[i]][j] <= work[j] && sequence[i] != pid)
        count++;
    }
    if(count == need[sequence[i]].size()){
      for(int j = 0 ; j < need[sequence[i]].size() ; j++)
        work[j] = work[j] + allocated[sequence[i]][j];     //work = work + allocated
      finish[sequence[i]] = true;
    }
  }
  int counter = 0;
  /*check if every process of finish is true*/
  for(int i = 0 ; i < finish.size() ; i++){
    if(finish[i] == true)
      counter++;
  }
  if(counter == finish.size()){
    counter = 0;
    cout << "granted, (" ;
    for(int i = 0 ; i < need[pid].size() ; i++){
      if(need[pid][i] == 0)
        counter++;
    }
    if(counter == need[pid].size())
      sequence.erase(sequence.begin() + pid - 1);
    for(int i = 0 ; i < sequence.size() ; i++){
        if(i == sequence.size() - 1)
          cout << sequence[i] << ")" << endl;
        else
          cout << sequence[i] << ",";
    }
  }
  else{
    waiting.push_back(request);
    cout << "Not granted, process will be unsafe, put to waiting_quene" << endl;
    /*recovery allocated need available*/
    for(int i = 0 ; i < avail.size() ; i++){
      avail[i] = avail[i] + request[i + 1];        //available = available + request
      need[pid][i] = need[pid][i] + request[i + 1];  //need = need + request
      allocated[pid][i] = allocated[pid][i] - request[i + 1];  //allocated = allocated - request
    }
  }
}
void banker::wait(){
  if(waiting.size() != 0){
    for(int i = 0 ; i < waiting.size() ; i++){
      cout << "(";
      for(int j = 0 ; j < waiting[i].size() ; j++){
        request[j] = waiting[i][j];
        if(j == request.size() - 2)
          cout << request[j] << "): ";
        else if(j < request.size() - 2)
          cout << request[j] << ",";
      }
      banker_algorithm(request[0]);
    }
    waiting.clear();
  }
}
