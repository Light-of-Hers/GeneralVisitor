%{
    #include "node.h"
    #include <cstdlib>
    using namespace std;

    #include "parser.hh"
%}

%option nounput noyywrap

digit   [0-9]

%%

[+\-*/%\[\](){},;=<>!]  { return yytext[0]; }

{digit}+    { yylval.i = atoi(yytext); return NUM; }

[ \r\t] {}

\n { yylineno++; }

%%