
%option yylineno
%{
    #include<iostream>
	#include <string>
	#include "codeGenerator.hpp"

	#include "Memory/lookupTab.hpp"
    #include "Conditions.hpp"
    #include "errorHandler.hpp"
    #include "Expressions.hpp"
    #include "Values.hpp"
	#include "bison.tab.hpp"
using namespace std;
%}

%x COM
%option noyywrap
%%
"VAR"              	 { return VAR; }
"BEGIN"                 { return BEGIN_; }
"END"                   { return END; }

"READ"                  { return READ; }
"WRITE"                 { return WRITE; }


"PLUS"                  { return PLUS; }
"MINUS"                 { return MINUS; }
"TIMES"                 { return TIMES; }
"DIV"                   { return DIV; }
"MOD"                   { return MOD; }


"IF"                    { return IF; }
"THEN"                  { return THEN; }
"ELSE"                  { return ELSE; }
"ENDIF"                 { return ENDIF; }


"WHILE"                 { return WHILE; }
"DO"                    { return DO; }
"ENDWHILE"		 { return ENDWHILE; }
"REPEAT"                { return REPEAT; }
"UNTIL"		 { return UNTIL; }

"FOR"                   { return FOR; }
"FROM"                  { return FROM; }
"TO"                    { return TO; }
"DOWNTO"                { return DOWNTO; }
"ENDFOR"                { return ENDFOR; }



"EQ"                    { return EQ; }
"NEQ"                   { return NEQ; }
"LE"                    { return LE; }
"GE"                    { return GE; }
"LEQ"                   { return LEQ; }
"GEQ"                   { return GEQ; }


"ASSIGN"                { return ASSIGN; }

[\;\,\:\[\]]				{return yytext[0];}
[_a-z]+		{ 
                            yylval.pid = new string(yytext);
                            return pidentifier;
                        }
("-"?[0-9]+)               { yylval.numb = atol(yytext); return num; }
[ \t\r\n]      ;
"("	{ BEGIN(COM); }
.	{ECHO;}
<COM>{
	[^\)]               ;
    ")"                 BEGIN(INITIAL);

}

%%

