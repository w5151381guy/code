%{
  /*C Definition*/
  #include <stdio.h>
  #include <math.h>
  #include <stdlib.h>
  double ans = 0;
  extern int yylex();
  void yyerror(char *s);
%}
%union {
  float num;
  int index;
}
%type <num> expression;
%type <num> term;
%token <num> NUMBER;
%token <index> VAR;
%token SIN COS NEG ABS LOG ADD SUB TAN SQRT
%token ERROR1

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
  | ADD expression {$$ = $2+1;}
  | SUB expression {$$ = $2-1;}
  | NEG term  {$$ = -$2;}
  | SQRT term {$$ = sqrt($2);}
  | ABS term  {$$ = fabs($2);}
  | LOG term  {$$ = log10($2);}
  | COS term  {$$ = cos($2*3.1415926/180);}
  | SIN term  {$$ = sin($2*3.1415926/180);}
  | TAN term  {$$ = tan($2*3.1415926/180);}
  | ADD term  {$$ = ($2+1);}
  | SUB term  {$$ = ($2-1);}
  | '-' expression %prec UMINUS {$$ = -$2;}
  ;
term
  : NUMBER {$$ = $1;}
  | '(' expression ')' {$$ = $2;}
  ;
%%
int line;
void yyerror(char *s){
  printf("Line %d:%s\n",line,s);
}
int main(){
  yyparse();
  return 0;
}
