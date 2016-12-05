%{
  #include "cal.tab.h"
  #include <stdio.h>
%}

%%
[0-9]+
%%
int yywrap(){
  return 1;
}
