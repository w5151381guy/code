%{
  /*C Definition*/
  #include <stdio.h>
  #include <math.h>
  #include <stdlib.h>
  #define YYSTYPE double
  YYSTYPE ans = 0;
  extern int yylex();
  void yyerror(char *s);
  //double Varvalue(int i);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%right '^'
%left COS SIN EXP SQRT TAN LOG
%right NEG VAR ABS
%%
input
  : /*empty*/
  | input expression '\n' {printf("%f\n",ans = $2);}
  ;
expression
  : term {$$ = $1;}
  | expression '+' expression {$$ = $1 + $3;}
  | expression '-' expression {$$ = $1 - $3;}
  | expression '*' expression {$$ = $1 * $3;}
  | expression '/' expression {$$ = $1 / $3;}
  | expression '^' expression {$$ = pow($1,$3);}
  | NEG term  {$$ = - $2;}
  | SQRT term {$$ = sqrt($2);}
  | ABS term  {$$ = abs($2);}
  | LOG term  {$$ = log10($2);}
  | COS term  {$$ = cos($2*3.1415926/180);}
  | SIN term  {$$ = sin($2*3.1415926/180);}
  | TAN term  {$$ = tan($2*3.1415926/180);}
  | EXP term  {$$ = exp($2);}
  //| VAR { $$ = Varvalue($1); }
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
