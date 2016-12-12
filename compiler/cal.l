%{
  #include "y.tab.h"
  #include <stdio.h>
  #include <math.h>
  #include <stdlib.h>
%}
int returnVar(char *text);
void error();
/*regular expression*/
digit [0-9]
%%
{digit}+"."{digit}+    {yylval.num = atof(yytext); return NUMBER;}
{digit}+               {yylval.num = atof(yytext); return NUMBER;}
[Vv][Aa][Rr]{digit}+   {yylval.index = returnVar(yytext); return VAR;}
[ \t] {/*skip white space*/}
[\n]  {return '\n';}
[Cc][Oo][Ss]  {return COS;}
[Ss][Ii][Nn]  {return SIN;}
[Tt][Aa][Nn]  {return TAN;}
[Nn][Ee][Gg]  {return NEG;}
[Ll][Oo][Gg]  {return LOG;}
[Aa][Bb][Ss]  {return ABS;}
"++"          {return ADD;}
"--"          {return SUB;}
[Ss][Qq][Rr][Tt]  {return SQRT;}
. {return yytext[0];}
%%
int returnVar(char *text){
	return (text[3]-'0'); //char to int
}
int yywrap(){
  return 1;
}
