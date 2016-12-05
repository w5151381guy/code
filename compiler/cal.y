%{
  /*C Definition*/
  #include <stdio.h>
  #include <math.h>
  int yylex();
  float ans = 0;
  void yyerror(char *)
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%left '^'
%left NEGATIVE
%left COS SIN EXP SQRT TAN
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
  | '-' expression %prec NEGATIVE {$$ = -$2;}
  | COS term {$$ = cos($2);}
  | SIN term {$$ = sin($2);}
  | TAN term {$$ = tan($2);}
  | EXP term {$$ = exp($2);}
  ;
term
  : NUMBER {$$ = $1;}
  | '(' expression ')' {$$ = $2;}
  ;
%%
