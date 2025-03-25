%{
#include "include/TreeNode.h"
#include "syntax.tab.h"
#include "include/error.h"
int yycolumn=1;
#define YY_USER_ACTION  \
    yylloc.first_line=yylloc.last_line=yylineno;  \
    yylloc.first_column=yycolumn;   \
    yylloc.last_column=yycolumn+yyleng-1;   \
    yycolumn+=yyleng;
%}

%option yylineno    

COMMENTSINGLE "//"
COMMENTMULTI "/*"

SEMI ;
COMMA ,
ASSIGNOP =
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !

EQ ==
NEQ !=
LE <=
LT <
GE >=
GT >

LP \(
RP \)
LB \[
RB \]
LC \{
RC \}

ID_ERROR [0-9][a-zA-Z0-9_]*
INTOCT_ERROR 0[0-7]*[89][0-9]*
INTHEX_ERROR 0[xX][0-9a-fA-F]*[g-zG-Z]*[0-9a-zA-Z]*
INTDEC_ERROR [1-9][0-9]*[a-zA-Z]*
FLOAT_ERROR ({INTDEC}\.[0-9]*[a-zA-Z]+)|(([0-9]*\.[0-9]*|[0-9]*\.[0-9]*)[Ee][+-]?[0-9]*[a-zA-Z]+)
INT_ERROR ({INTDEC_ERROR}|{INTOCT_ERROR}|{INTHEX_ERROR})

TYPE int|float
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while

INTOCT 0[1-7][0-7]*
INTHEX 0[xX][0-9a-fA-F]+
INTDEC (0|[1-9][0-9]*)
INT {INTDEC}|{INTOCT}|{INTHEX}
FLOAT ({INTDEC}\.[0-9]+)|(([0-9]+\.[0-9]*|[0-9]*\.[0-9]*)[Ee][+-]?[0-9]+)
ID [a-zA-Z_][a-zA-Z0-9_]*
SPACE [ \t\n\r]+

ERROR .
%%
{COMMENTSINGLE} { while (input() != '\n'); }
{COMMENTMULTI} {}

{INT} { yylval.node_ptr=create_node(INT,yylineno,0,1);return INT;}
{FLOAT} { yylval.node_ptr=create_node(FLOAT,yylineno,0,1); return FLOAT;}
{SEMI} {yylval.node_ptr=create_node(SEMI,yylineno,0,1); return SEMI;}
{COMMA} { yylval.node_ptr=create_node(COMMA,yylineno,0,1); return COMMA; }
{ASSIGNOP} {yylval.node_ptr=create_node(ASSIGNOP,yylineno,0,1); return ASSIGNOP; }
{PLUS} {yylval.node_ptr=create_node(PLUS,yylineno,0,1); return PLUS;}
{MINUS} {yylval.node_ptr=create_node(MINUS,yylineno,0,1); return MINUS;}
{STAR} { yylval.node_ptr=create_node(STAR,yylineno,0,1); return STAR; }
{DIV} { yylval.node_ptr=create_node(DIV,yylineno,0,1); return DIV; }
{AND} { yylval.node_ptr=create_node(AND,yylineno,0,1);return AND; }
{OR} { yylval.node_ptr=create_node(OR,yylineno,0,1); return OR; }
{DOT} {yylval.node_ptr=create_node(DOT,yylineno,0,1); return DOT;}
{NOT} { yylval.node_ptr=create_node(NOT,yylineno,0,1); return NOT; }
{TYPE} {yylval.node_ptr=create_node(TYPE,yylineno,0,1); return TYPE;}

{EQ} {  yylval.node_ptr=create_node(EQ,yylineno,0,1); return EQ;}
{NEQ} { yylval.node_ptr=create_node(NEQ,yylineno,0,1); return NEQ; }
{LE} {yylval.node_ptr=create_node(LE,yylineno,0,1); return LE;}
{LT} {  yylval.node_ptr=create_node(LT,yylineno,0,1); return LT;}
{GE} {yylval.node_ptr=create_node(GE,yylineno,0,1); return GE;  }
{GT} { yylval.node_ptr=create_node(GT,yylineno,0,1); return GT;}

{LP} { yylval.node_ptr=create_node(LP,yylineno,0,1); return LP; }
{RP} { yylval.node_ptr=create_node(RP,yylineno,0,1); return RP; }
{LB} {yylval.node_ptr=create_node(LB,yylineno,0,1); return LB;}
{RB} {yylval.node_ptr=create_node(RB,yylineno,0,1); return RB; }
{LC} { yylval.node_ptr=create_node(LC,yylineno,0,1); return LC; }
{RC} { yylval.node_ptr=create_node(RC,yylineno,0,1); return RC;}

{STRUCT} { yylval.node_ptr=create_node(STRUCT,yylineno,0,1); return STRUCT; }
{RETURN} { yylval.node_ptr=create_node(RETURN,yylineno,0,1); return RETURN;}
{IF} { yylval.node_ptr=create_node(IF,yylineno,0,1); return IF; }
{ELSE} {  yylval.node_ptr=create_node(ELSE,yylineno,0,1); return ELSE;}
{WHILE} {yylval.node_ptr=create_node(WHILE,yylineno,0,1); return WHILE;}
{SPACE} { yycolumn=1; }
{ID} { yylval.node_ptr=create_node(ID,yylineno,0,1); return ID; }

{ID_ERROR} { readError(create_node(ID_ERROR,yylineno,0,1)); }
{FLOAT_ERROR} { readError(create_node(FLOAT_ERROR,yylineno,0,1)); }
{ERROR} { readError(create_node(ERROR,yylineno,0,1)); has_error=1;}

%%