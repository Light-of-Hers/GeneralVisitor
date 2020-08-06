%{
  #include "node.h"

  extern int yylex();
  extern void yyerror(Node**, const char *);
%}

%start top

%union {
  int i;
  Node *node;
}

%token<i> NUM

%parse-param { Node** node }

%type<node> term0 term1 term2

%%

top:
    %empty { *node = nullptr; }
  | term0 ';' { *node = $1; YYACCEPT; }
  ;

term0:
    term0 '+' term1  { $$ = new AddNode ($1, $3); }
  | term0 '-' term1  { $$ = new SubNode ($1, $3); }
  | term1 { $$ = $1; }
  ;

term1:
    term2 '*' term1 { $$ = new MulNode ($1, $3); }
  | term2 '/' term1 { $$ = new DivNode ($1, $3); }
  | term2 { $$ = $1; }
  ;

term2:
    NUM { $$ = new NumNode ($1); }
  | '(' term0 ')' { $$ = $2; }
  ;

%%