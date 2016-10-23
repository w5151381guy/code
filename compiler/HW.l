%{
/*c definition*/
#define ID 1
#define INTEGER_LITERAL 2
#define FLOAT 3
#define EXPONENTIAL 4
#define STRING 5
#define comma 6
#define semicolon 7
#define left_parenthesis 8
#define right_parenthesis 9
#define BEGINSYM 10
#define END 11
#define READ 12
#define WRITE 13
#define IF 14
#define THEN 15
#define ELSE 16
#define ENDIF 17
#define FOR 18
#define TO 19
#define ENDFOR 20
#define WHILE 21
#define ENDWHILE 22
#define REPEAT 23
#define REPEATEND 24
#define DECLARE 25
#define AS 26
#define INTEGER 27
#define REAL 28
#define BOOL 29
#define SCANEOF 30
#define ASSIGNMENT 31       // :=
#define ADDITION 32         // +
#define SUBTRACTION 33      // -
#define MULTIPLICATION 34   // *
#define DIVISION 35         // /
#define NOT_EQUAL 36        // !=
#define GREATER_THAN 37     // >
#define LESS_THAN 38        // <
#define GREATER_OR_EQUAL 39 // >=
#define LESS_OR_EQUAL 40    // <=
#define EQUAL 41            // ==
#define INCREMENT 42        // ++
#define DECREMENT 43        // --
#define REMAINDER 44        // %
#define AND 45              // &&
#define OR 46               // ||
#define NOT 49              // !
#define ADD_ASSIGN 50       // +=
#define SUB_ASSIGN 51       // -=
#define MULTI_ASSIGN 52     // *=
#define DIVI_ASSIGN 53      // /=
#define REMAIN_ASSIGN 54    // %=
#define ILLEGAL 55
%}

/*regular expression*/
Digit [0-9]
Letter [a-zA-Z]
Name {Letter}{Letter}*
IntLit {Digit}+
Illegal_ID {IntLit}{Name}
Id {Letter}({Letter}|{Digit}|_)*
%x Comment1
%x Comment2
%%

%option yylineno;
\n {yylineno++;}
"%%" {BEGIN Comment1;}
"{%" {BEGIN Comment2;}
<Comment1>\n                          {yylineno++; BEGIN INITIAL;}
<Comment1>.                           {}
<Comment2>\n                          {yylineno++;}
<Comment2>.                           {}
<Comment2>"%}"                        {BEGIN INITIAL;}
[Bb][Ee][Gg][Ii][Nn]                  {return(BEGINSYM);}
[Ee][Nn][Dd]                          {return(END);}
[Rr][Ee][Aa][Dd]                      {return(READ);}
[Ww][Rr][Ii][Tt][Ee]                  {return(WRITE);}
[Ii][Ff]                              {return(IF);}
[Tt][Hh][Ee][Nn]                      {return(THEN);}
[Ee][Ll][Ss][Ee]                      {return(ELSE);}
[En][Nn][Dd][Ii][Ff]                  {return(ENDIF);}
[Ff][Oo][Rr]                          {return(FOR);}
[Tt][Oo]                              {return(TO);}
[Ee][Nn][Dd][Ff][Oo][Rr]              {return(ENDFOR);}
[Ww][Hh][Ii][Ll][Ee]                  {return(WHILE);}
[Ee][Nn][Dd][Ww][Hh][Ii][Ll][Ee]      {return(ENDWHILE);}
[Rr][Ee][Pp][Ee][Aa][Tt]              {return(REPEAT);}
[Rr][Ee][Pp][Ee][Aa][Tt][Ee][Nn][Dd]  {return(REPEATEND);}
[Dd][Ee][Cc][Ll][Aa][Rr][Ee]          {return(DECLARE);}
[Aa][Ss]                              {return(AS);}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]          {return(INTEGER);}
[Rr][Ee][Aa][Ll]                      {return(REAL);}
[Bb][Oo][Oo][Ll]                      {return(BOOL);}
[Ss][Cc][Aa][Nn][Ee][Oo][Ff]          {return(SCANEOF);}
[,.][,.]                              {return(ILLEGAL);}
[*/][*/+]                             {return(ILLEGAL);}
[*/+][*/]                             {return(ILLEGAL);}
[+][-]|[-][+]                         {return(ILLEGAL);}

[ \t\n]              {/* skip white spaces */}
{Name}               {return(ID);}
{Id}                 {return(ID);}
{Illegal_ID}         {return(ILLEGAL);}
["]{Id}              {return(ILLEGAL);}
\"[^\"\n]*\" {stripquotes(); return(STRING);}


","                  {return(comma);}
";"                  {return(semicolon);}
"("                  {return(left_parenthesis);}
")"                  {return(right_parenthesis);}

":="                 {return(ASSIGNMENT);}
"+"                  {return(ADDITION);}
"-"                  {return(SUBTRACTION);}
"*"                  {return(MULTIPLICATION);}
"/"                  {return(DIVISION);}
"!="                 {return(NOT_EQUAL);}
">"                  {return(GREATER_THAN);}
"<"                  {return(LESS_THAN);}
">="                 {return(GREATER_OR_EQUAL);}
"<="                 {return(LESS_OR_EQUAL);}
"=="                 {return(EQUAL);}
"++"                 {return(INCREMENT);}
"--"                 {return(DECREMENT);}
"%"                  {return(REMAINDER);}
"&&"                 {return(AND);}
"||"                 {return(OR);}
"!"                  {return(NOT);}
"+="                 {return(ADD_ASSIGN);}
"-="                 {return(SUB_ASSIGN);}
"*="                 {return(MULTI_ASSIGN);}
"/="                 {return(DIVI_ASSIGN);}
"%="                 {return(REMAIN_ASSIGN);}

":="+                {return(ILLEGAL);}
">"+"="+             {return(ILLEGAL);}
"="+">"+             {return(ILLEGAL);}
">"+"<"+|"<"+">"+    {return(ILLEGAL);}

(0)+{IntLit}         {return(ILLEGAL);}
{IntLit}             {return(INTEGER_LITERAL);}
({Name}{IntLit}[.]{IntLit})? {return(ILLEGAL);}
({Name}[.]{IntLit})? {return(ILLEGAL);}
({IntLit}[.]{IntLit}{Name})? {return(ILLEGAL);}
({IntLit}[.]{Name})? {return(ILLEGAL);}
[.]{IntLit}? {return(ILLEGAL);}
{IntLit}[.]? {return(ILLEGAL);}
({IntLit}[.]{IntLit})? {return(FLOAT);}
({IntLit}[.]{IntLit})([Ee][+-]?{IntLit}{Name})? {return(ILLEGAL);}
({IntLit}[.]{IntLit})([Ee][+-]?{IntLit})? {return(EXPONENTIAL);}
%%

/*c program*/
stripquotes()
{
  /* handling string within a quoted string */
  int frompos, topos=0, numquotes = 2;
  for(frompos=1; frompos<yyleng; frompos++){
    yytext[topos++] = yytext[frompos];
  }
  yyleng -= numquotes;
  yytext[yyleng] = '\0';
}

/*main function*/
int main(){
  int i;
  i = yylex();
  while (i>0 && i < 56) {
    if(i == 55)
      printf("Line %d:\"%s\" is an illegal identifier.\n",yylineno,yytext);
    else
      printf("Token number:%d,value:\"%s\",line %d.\n",i,yytext,yylineno);
    i = yylex();
  }
}
