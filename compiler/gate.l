%{
  #include "y.tab.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
%}

%x Comment
%%

"#"                  {BEGIN Comment;}
<Comment>.           {}
<Comment>\n          {BEGIN INITIAL;}
[0-9]+               {yylval.num = atoi(yytext); return NUMBER;}
[Ii][Nn][Pp][Uu][Tt]"("[0-9]+")"      {return INPUT;}
[Oo][Uu][Tt][Pp][Uu][Tt]"("[0-9]+")"  {return OUTPUT;}
[Bb][Uu][Ff][Ff]     {return BUFF;}
[Nn][Aa][Nn][Dd]     {return NAND;}
[Nn][Xx][Oo][Rr]     {return NXOR;}
[Nn][Oo][Tt]         {return NOT;}
[Aa][Nn][Dd]         {return AND;}
[Xx][Oo][Rr]         {return XOR;}
[Nn][Oo][Rr]         {return NOR;}
[Oo][Rr]             {return OR;}
[ \t]                {/*skip white space*/}
[\n]                 {return '\n';}
<<eof>>              {return End_Of_File;}
. {return yytext[0];}
%%
int yywrap(){
  return 1;
}
