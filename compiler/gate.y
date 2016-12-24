%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  extern int yylex();
  extern char *yytext;
  char input[100];
  int counter = 0;
  int ans[2];
  int inputcounter = 0;
  int outputcounter = 0;
  int temp1[100] = {'\0'};    //set tempValue1 = NULL
  int temp2[100] = {'\0'};    //set tempValue2 = NULL
  int input1[100];   //set primary number
  int input2[100];   //set primary number
  int recordIndex[100] = {0};      //record buff value
  int number(int value);
  int number2(int value);
  void putValue(int value1);
  void print();
  int record(int value);
  int *calNOT(int value);
  int *calAND(int value1 ,int value2);
  int *calOR(int value ,int value2);
  int *calNAND(int value ,int value2);
  int *calXOR(int value ,int value2);
  int *calNOR(int value ,int value2);
  int *calNXOR(int value, int value2);
  void yyerror(char *s);
%}
%union{
  int num;
}
%type <num> expression
%token <num> NUMBER
%token INPUT OUTPUT
%right '='
%token BUFF NOT AND OR NAND XOR NOR NXOR End_Of_File
%%
start
  : /*empty*/
  | start expression '\n' {}
  | start '\n'            {}
  ;
expression
  : NUMBER {$$ = $1;}
  | INPUT {input1[inputcounter] = 1; input2[inputcounter] = 0; inputcounter++;}
  | OUTPUT {outputcounter++;}
  | expression '=' expression {$$=$3; putValue($1);}
  | BUFF '(' expression ')' {$$=record($3);}
  | NOT '(' expression ')'  {$$=*calNOT($3);}
  | AND '(' expression ',' expression ')'  {$$=*calAND($3,$5);}
  | OR '(' expression ',' expression ')'   {$$=*calOR($3,$5);}
  | NAND '(' expression ',' expression ')' {$$=*calNAND($3,$5);}
  | XOR '(' expression ',' expression ')'  {$$=*calXOR($3,$5);}
  | NOR '(' expression ',' expression ')'  {$$=*calNOR($3,$5);}
  | NXOR '(' expression ',' expression ')' {$$=*calNXOR($3,$5);}
  | End_Of_File {print();}
  ;
%%
int number(int value){
  /*cut value*/
  int length = floor(log10(value)) + 1;
  int digit = 1;
  for(int i=1;i<length;i++)
    digit *= 10;
  return value/digit;
}
int number2(int value){
  int length = floor(log10(value)) + 1;
  int digit = 1;
  for(int i=1;i<length;i++)
    digit *= 10;
  int head = value/digit;
  return value - (head * digit);
}
int *calNOT(int value){
  int head = number(value);
  int num = number2(value);
  if(head == 3){
    ans[0] = !input1[num];
    ans[1] = !input2[num];
  }
  else{
    if(temp1[num] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
    }
    else{
      ans[0] = !temp1[num];
      ans[1] = !temp2[num];
    }
  }
  return ans;
}
int *calAND(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = input1[num1] & input1[num2];
    ans[1] = input2[num1] & input2[num2];
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = temp1[num1] & input1[num2];
      ans[1] = temp2[num1] & input2[num2];
    }
    if(head1 < head2 && check == 1){
      ans[0] = input1[num1] & temp1[num2];
      ans[1] = input2[num1] & temp2[num2];
    }
    else{
      ans[0] = temp1[num1] & temp1[num2];
      ans[1] = temp2[num1] & temp2[num2];
    }
  }
  return ans;
}
int *calOR(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = input1[num1] | input1[num2];
    ans[1] = input2[num1] | input2[num2];
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = temp1[num1] | input1[num2];
      ans[1] = temp2[num1] | input2[num2];
    }
    if(head1 < head2 && check == 1){
      ans[0] = input1[num1] | temp1[num2];
      ans[1] = input2[num1] | temp2[num2];
    }
    else{
      ans[0] = temp1[num1] | temp1[num2];
      ans[1] = temp2[num1] | temp2[num2];
    }
  }
  return ans;
}
int *calNAND(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = !(input1[num1] & input1[num2]);
    ans[1] = !(input2[num1] & input2[num2]);
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = !(temp1[num1] & input1[num2]);
      ans[1] = !(temp2[num1] & input2[num2]);
    }
    if(head1 < head2 && check == 1){
      ans[0] = !(input1[num1] & temp1[num2]);
      ans[1] = !(input2[num1] & temp2[num2]);
    }
    else{
      ans[0] = !(temp1[num1] & temp1[num2]);
      ans[1] = !(temp2[num1] & temp2[num2]);
    }
  }
  return ans;
}
int *calXOR(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = input1[num1] ^ input1[num2];
    ans[1] = input2[num1] ^ input2[num2];
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = temp1[num1] ^ input1[num2];
      ans[1] = temp2[num1] ^ input2[num2];
    }
    if(head1 < head2 && check == 1){
      ans[0] = input1[num1] ^ temp1[num2];
      ans[1] = input2[num1] ^ temp2[num2];
    }
    else{
      ans[0] = temp1[num1] ^ temp1[num2];
      ans[1] = temp2[num1] ^ temp2[num2];
    }
  }
  return ans;
}
int *calNXOR(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = !(input1[num1] ^ input1[num2]);
    ans[1] = !(input2[num1] ^ input2[num2]);
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = !(temp1[num1] ^ input1[num2]);
      ans[1] = !(temp2[num1] ^ input2[num2]);
    }
    if(head1 < head2 && check == 1){
      ans[0] = !(input1[num1] ^ temp1[num2]);
      ans[1] = !(input2[num1] ^ temp2[num2]);
    }
    else{
      ans[0] = !(temp1[num1] ^ temp1[num2]);
      ans[1] = !(temp2[num1] ^ temp2[num2]);
    }
  }
  return ans;
}
int *calNOR(int value1 ,int value2){
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = 1;
  if(head1 == 3 && head2 == 3){
    ans[0] = !(input1[num1] | input1[num2]);
    ans[1] = !(input2[num1] | input2[num2]);
  }
  else{
    if(temp1[num1] == '\0' || temp1[num2] == '\0'){
      input[counter++] = *yytext;
      ans[0] = -1; ans[1] = -1;
      check = 0;
    }
    if(head1 > head2 && check == 1){
      ans[0] = !(temp1[num1] | input1[num2]);
      ans[1] = !(temp2[num1] | input2[num2]);
    }
    if(head1 < head2 && check == 1){
      ans[0] = !(input1[num1] | temp1[num2]);
      ans[1] = !(input2[num1] | temp2[num2]);
    }
    else{
      ans[0] = !(temp1[num1] | temp1[num2]);
      ans[1] = !(temp2[num1] | temp2[num2]);
    }
  }
  return ans;
}
int record(int value){
  int num = number2(value);
  recordIndex[num] = 1;
  return recordIndex[num];
}
void putValue(int value1){
  int head1 = number(value1);
  int num1 = number2(value1);
  if(head1 != 4){
    temp1[num1] = ans[0];
    temp2[num1] = ans[1];
  }
}
void print(){
  int counter = 0;
  int arr1[10], arr2[10];
  for(int i = 0 ;; i++){
    if(counter == outputcounter)
      break;
    if(recordIndex[i] == 1){
      arr1[counter] = temp1[i];
      arr2[counter] = temp2[i];
      counter++;
    }
  }
  printf("For all input is 1\nAns:");
  for(int i = 0 ; i < counter ; i++){
    printf("%d",arr1[i]);
  }
  printf("\n");
  printf("For all input is 0\nAns:");
  for(int i = 0 ; i < counter ; i++){
    printf("%d",arr2[i]);
  }
  printf("\n");
}
void yyerror(char *s){
  
}
int main(){
  yyparse();
  return 0;
}
