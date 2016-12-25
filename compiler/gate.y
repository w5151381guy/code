%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  extern int yylex();
  extern char *yytext;
  int operator[10000];
  int notseq[10000];
  int seq1[10000],seq2[10000],seq3[10000];
  int counter = 0;
  int ans[2];
  int inputcounter = 0;
  int outputcounter = 0;
  int temp1[10000] = {'\0'};    //set tempValue1 = NULL
  int temp2[10000] = {'\0'};    //set tempValue2 = NULL
  int input1[10000];   //set primary number
  int input2[10000];   //set primary number
  int recordIndex[10000] = {0};      //record buff value
  int number(int value);
  int number2(int value);
  void putValue(int value1);
  void print();
  void check();
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
  | End_Of_File {check();}
  ;
%%
int number(int value){
  /*cut value if value = 301 return 3*/
  int length = floor(log10(value)) + 1;
  int digit = 1;
  for(int i=1;i<length;i++)
    digit *= 10;
  return value/digit;
}
int number2(int value){
  /*cut value if value = 301 return 1*/
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
      operator[counter] = 0;
      notseq[counter] = value;
      ans[0] = -1; ans[1] = -1;
    }
    else{
      ans[0] = !temp1[num];
      ans[1] = !temp2[num];
    }
  }
  return ans;
}
int checkNull(int head1, int head2, int num1, int num2){
  /*check if tempvalue is null*/
  int check = 0;
  if(head1 == 5 && head2 == 5 && (temp1[num1] == '\0' || temp1[num2] == '\0'))
    check = 1;
  if(head1 > head2 && temp1[num1] == '\0')
    check = 1;
  if(head1 < head2 && temp1[num2] == '\0')
    check = 1;
  return check;
}
int *calAND(int value1 ,int value2){
  /*logic AND calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 1;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = input1[num1] & input1[num2];
      ans[1] = input2[num1] & input2[num2];
    }
    if(head1 == 5 && head2 == 5){
      ans[0] = temp1[num1] & temp1[num2];
      ans[1] = temp2[num1] & temp2[num2];
    }
    if(head1 > head2){
      ans[0] = temp1[num1] & input1[num2];
      ans[1] = temp2[num1] & input2[num2];
    }
    if(head1 < head2){
      ans[0] = input1[num1] & temp1[num2];
      ans[1] = input2[num1] & temp2[num2];
    }
  }
  return ans;
}
int *calOR(int value1 ,int value2){
  /*logic OR calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 2;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = input1[num1] | input1[num2];
      ans[1] = input2[num1] | input2[num2];
    }
    if(head1 == 5 && head2 == 5){
      ans[0] = temp1[num1] | temp1[num2];
      ans[1] = temp2[num1] | temp2[num2];
    }
    if(head1 > head2){
      ans[0] = temp1[num1] | input1[num2];
      ans[1] = temp2[num1] | input2[num2];
    }
    else{
      ans[0] = input1[num1] | temp1[num2];
      ans[1] = input2[num1] | temp2[num2];
    }
  }
  return ans;
}
int *calNAND(int value1 ,int value2){
  /*logic NAND calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 3;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = !(input1[num1] & input1[num2]);
      ans[1] = !(input2[num1] & input2[num2]);
    }
    if(head1 == 5 && head2 == 5){
      ans[0] = !(temp1[num1] & temp1[num2]);
      ans[1] = !(temp2[num1] & temp2[num2]);
    }
    if(head1 > head2){
      ans[0] = !(temp1[num1] & input1[num2]);
      ans[1] = !(temp2[num1] & input2[num2]);
    }
    else{
      ans[0] = !(input1[num1] & temp1[num2]);
      ans[1] = !(input2[num1] & temp2[num2]);
    }
  }
  return ans;
}
int *calXOR(int value1 ,int value2){
  /*logic XOR calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 4;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = input1[num1] ^ input1[num2];
      ans[1] = input2[num1] ^ input2[num2];
    }
    if(head1 == head2){
      ans[0] = temp1[num1] ^ temp1[num2];
      ans[1] = temp2[num1] ^ temp2[num2];
    }
    if(head1 > head2){
      ans[0] = temp1[num1] ^ input1[num2];
      ans[1] = temp2[num1] ^ input2[num2];
    }
    else{
      ans[0] = input1[num1] ^ temp1[num2];
      ans[1] = input2[num1] ^ temp2[num2];
    }
  }
  return ans;
}
int *calNXOR(int value1 ,int value2){
  /*logic NXOR calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 5;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = !(input1[num1] ^ input1[num2]);
      ans[1] = !(input2[num1] ^ input2[num2]);
    }
    if(head1 == 5 && head2 == 5){
      ans[0] = !(temp1[num1] ^ temp1[num2]);
      ans[1] = !(temp2[num1] ^ temp2[num2]);
    }
    if(head1 > head2){
      ans[0] = !(temp1[num1] ^ input1[num2]);
      ans[1] = !(temp2[num1] ^ input2[num2]);
    }
    else{
      ans[0] = !(input1[num1] ^ temp1[num2]);
      ans[1] = !(input2[num1] ^ temp2[num2]);
    }
  }
  return ans;
}
int *calNOR(int value1 ,int value2){
  /*logic NOR calculate*/
  int head1 = number(value1);
  int head2 = number(value2);
  int num1 = number2(value1);
  int num2 = number2(value2);
  int check = checkNull(head1,head2,num1,num2);
  if(check == 1){
    operator[counter] = 6;
    seq1[counter] = value1;
    seq2[counter] = value2;
    ans[0] = -1; ans[1] = -1;
  }
  else{
    if(head1 == 3 && head2 == 3){
      ans[0] = !(input1[num1] | input1[num2]);
      ans[1] = !(input2[num1] | input2[num2]);
    }
    if(head1 == 5 && head2 == 5){
      ans[0] = !(temp1[num1] | temp1[num2]);
      ans[1] = !(temp2[num1] | temp2[num2]);
    }
    if(head1 > head2){
      ans[0] = !(temp1[num1] | input1[num2]);
      ans[1] = !(temp2[num1] | input2[num2]);
    }
    else{
      ans[0] = !(input1[num1] | temp1[num2]);
      ans[1] = !(input2[num1] | temp2[num2]);
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
  if(head1 != 4 && ans[0] != -1){
    temp1[num1] = ans[0];
    temp2[num1] = ans[1];
  }
  if(ans[0] == -1)
    seq3[counter] = value1;
  counter++;
}
void print(){
  int counter = 0;
  int arr1[10000], arr2[10000];
  for(int i = 0 ;; i++){
    if(counter == outputcounter)
      break;
    if(recordIndex[i] == 1){
      arr1[counter] = temp1[i];
      arr2[counter] = temp2[i];
      counter++;
    }
  }
  printf("For all inputs are 1\nAns:");
  for(int i = 0 ; i < counter ; i++){
    printf("%d",arr1[i]);
  }
  printf("\nFor all inputs are 0\nAns:");
  for(int i = 0 ; i < counter ; i++){
    printf("%d",arr2[i]);
  }
  printf("\n");
}
void check(){
  /*0 -> NOT 1 -> AND 2 -> OR 3 -> NAND 4 -> XOR 5 -> NXOR 6 -> NOR*/
  int count = counter;
  counter = 0;
  for(int i=0;i<count;i++){
    switch(operator[i]){
      case 0:calNOT(notseq[i]);break;
      case 1:calAND(seq1[i],seq2[i]);break;
      case 2:calOR(seq1[i],seq2[i]);break;
      case 3:calNAND(seq1[i],seq2[i]);break;
      case 4:calXOR(seq1[i],seq2[i]);break;
      case 5:calNXOR(seq1[i],seq2[i]);break;
      case 6:calNOR(seq1[i],seq2[i]);break;
      putValue(seq3[i]);
    }
  }
  if(counter != 0)
    check();
  else
    print();
}
void yyerror(char *s){

}
int main(){
  yyparse();
  return 0;
}
