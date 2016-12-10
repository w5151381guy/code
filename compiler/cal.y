%{
  /*C Definition*/
  #include <stdio.h>
  #include <math.h>
  #include <stdlib.h>
  double ans = 0;
  int VarArray[20]; //Var array
  extern int yylex();
  void yyerror(char *s);
  int SetVar(int value);
  int PutVar(int var, int value);
  int tempVar, head = 1;
%}
%union {
  float num;
  int index;
  float line;
}
%type <num> expression;
%type <num> term;
%token <num> NUMBER;
%token <index> VAR;
%left SIN COS NEG ABS LOG ADD SUB TAN SQRT
%token ERROR1
%token <line> LINE

%left '='
%left '+' '-'
%left '*' '/' '%'
%right '^'
%right UMINUS
%%
input
  : /*empty*/
  | input expression '\n' {printf("%f\n",ans = $2);}
  | input '\n'
  ;
expression
  : term {$$ = $1;}
  | expression '+' expression {$$ = $1 + $3;}
  | expression '-' expression {$$ = $1 - $3;}
  | expression '*' expression {$$ = $1 * $3;}
  | expression '/' expression {$$ = $1 / $3;}
  | expression '^' expression {$$ = pow($1,$3);}
  | expression '=' expression {$$ = $3 ; PutVar(tempVar,$3);}
  | NEG term  {$$ = -$2;}
  | SQRT term {$$ = sqrt($2);}
  | ABS term  {$$ = fabs($2);}
  | LOG term  {$$ = log10($2);}
  | COS term  {$$ = cos($2);}
  | SIN term  {$$ = sin($2);}
  | TAN term  {$$ = tan($2);}
  | ADD term  {$$ = ($2+1);}
  | SUB term  {$$ = ($2-1);}
  | '-' expression %prec UMINUS {$$ = -$2;}
  | VAR {$$ = SetVar($1);}
  ;
term
  : NUMBER {$$ = $1;}
  | '(' expression ')' {$$ = $2;}
  ;
%%
int SetVar(int value){
  /*first read set value = 0; second time find value and return*/
  if(head == 1){
    tempVar = value;
    head = 0;
  }
  if(VarArray[value] == 0)
    VarArray[value] = 0;
  return VarArray[value];
}
int PutVar(int var, int value){
  /*put value int VarArray*/
  head = 1;
  VarArray[var] = value;
}
void yyerror(char *s){
  printf("Line %d:%s\n",LINE,s);
}
int main(){
  yyparse();
  return 0;
}
