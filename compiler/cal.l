%{
  #include "cal.tab.h"
  #include <stdio.h>
  int lineno = 0;
%}

/*regular expression*/
digit [0-9]
%%
{digit}+"."{digit}+ {sscanf(yytext,"%lf",&yylval); return NUMBER;}
{digit}+            {sscanf(yytext,"%lf",&yylval); return NUMBER;}
"var"[0-9]          {sscanf(yytext,"%s",&yylval); return VAR; }
[Cc][Oo][Ss]  {return COS;}
[Ss][Ii][Nn]  {return SIN;}
[Tt][Aa][Nn]  {return TAN;}
[Nn][Ee][Gg]  {return NEG;}
[Ll][Oo][Gg]  {return LOG;}
[Aa][Bb][Ss]  {return ABS;}
[Ss][Qq][Rr][Tt]  {return SQRT;}
[Ee]   {return EXP;}
[Pp][Ii]  {yylval = 3.1415926; return NUMBER;}
[ \t] {/*skip white space*/}
[\n] {lineno++; return '\n';}
. {return yytext[0];}
%%
int yywrap(){
  return 1;
}
