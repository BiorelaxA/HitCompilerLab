%{
#include <stdio.h>
#include "include/CmmparserTypes.h"

extern int yylex();
void yyerror(const char *s);
%}


%union{
    TreeNode_ptr node_ptr;
}

%token   <node_ptr>INT // A sequence of digits without spaces
%token   <node_ptr>FLOAT // A real number consisting of digits and a decimal point, point must be surrounded by digits
%token   <node_ptr>ID // A sequence of letters, digits, and underscores, starting with a letter or underscore, at most 52 characters
%token   <node_ptr>SEMI // ;
%token   <node_ptr>COMMA // ,
%token   <node_ptr>ASSIGNOP // =
%token   <node_ptr>EQ NEQ LE LT GE GT // ==, !=, <=, <, >=, >
%token   <node_ptr>PLUS // +
%token   <node_ptr>MINUS // -
%token   <node_ptr>STAR // *
%token   <node_ptr>DIV // /
%token   <node_ptr>AND // &&
%token   <node_ptr>OR // ||
%token   <node_ptr>DOT // .
%token   <node_ptr>NOT // !
%token   <node_ptr>TYPE // int, float
%token   <node_ptr>LP // (
%token   <node_ptr>RP // )
%token   <node_ptr>LB // [
%token   <node_ptr>RB // ]
%token   <node_ptr>LC // {
%token   <node_ptr>RC // }
%token   <node_ptr>STRUCT // struct
%token   <node_ptr>RETURN // return
%token   <node_ptr>IF // if
%token   <node_ptr>ELSE // else
%token   <node_ptr>WHILE // while
%token   <node_ptr>ERROR
%token   <node_ptr>INT_ERROR 
%token   <node_ptr>ID_ERROR
%token   <node_ptr>FLOAT_ERROR

%type   <node_ptr>Program ExtDefList ExtDef ExtDecList
%type   <node_ptr>Specifier StructSpecifier OptTag Tag
%type   <node_ptr>VarDec FunDec VarList ParamDec
%type   <node_ptr>CompStm StmtList Stmt
%type   <node_ptr>DefList Def DecList Dec
%type   <node_ptr>Exp Args

// Define the precedence and associativity of the operators
%right ASSIGNOP
%left OR
%left AND
%left EQ NEQ LE LT GE GT
%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT LP RP LB RB LC RC

%nonassoc LELSE
%nonassoc ELSE
%nonassoc pri3
%nonassoc pri2
%nonassoc pri1
%nonassoc pri0

%%

// HIGH LEVEL GRAMMAR
Program:    
    ExtDefList                                {$$=create_node(PROGRAM,@$.first_line,1,0);add_children($$,1,$1);set_root_node($$);}       
    ;   

//global variale
ExtDefList:
    ExtDef ExtDefList                         {$$=create_node(EXT_DEF_LIST,@$.first_line,2,0);add_children($$,2,$1,$2);}       
    | /* empty */                             {$$=create_node(EXT_DEF_LIST,@$.first_line,0,0);}      
    ;

ExtDef:
    Specifier ExtDecList SEMI %prec pri0      {$$=create_node(EXT_DEF,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Specifier SEMI           %prec pri0      {$$=create_node(EXT_DEF,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |Specifier FunDec CompStm                 {$$=create_node(EXT_DEF,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Specifier FunDec SEMI    %prec pri0      {$$=create_node(EXT_DEF,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Specifier ExtDecList     %prec pri1      {$$=create_node(EXT_DEF,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |Specifier                %prec pri1      {$$=create_node(EXT_DEF,@$.first_line,1,0);add_children($$,1,$1);}
    |Specifier FunDec         %prec pri1      {$$=create_node(EXT_DEF,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |error SEMI               %prec pri2      {yyerrok;$$=create_node(EXT_DEF,@$.first_line,0,0);readError($$->linenum,$$->issemanticValue);has_error=1;}
    ;

ExtDecList:
    VarDec                                    {$$=create_node(EXT_DEC_LIST,@$.first_line,1,0);add_children($$,1,$1);}           
    |VarDec COMMA ExtDecList                  {$$=create_node(EXT_DEC_LIST,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}          
    |VarDec ExtDecList                        {$$=create_node(EXT_DEC_LIST,@$.first_line,2,0);add_children($$,2,$1,$2);}
    ;

//SPECIFIER
Specifier:
    TYPE                                      {$$=create_node(SPECIFIER,@$.first_line,1,0);add_children($$,1,$1);}
    |StructSpecifier                          {$$=create_node(SPECIFIER,@$.first_line,1,0);add_children($$,1,$1);}
    ;

StructSpecifier:
    STRUCT OptTag LC DefList RC               {$$=create_node(STRUCT_SPECIFIER,@$.first_line,5,0);add_children($$,5,$1,$2,$3,$4,$5);}
    |STRUCT Tag                               {$$=create_node(STRUCT_SPECIFIER,@$.first_line,2,0);add_children($$,2,$1,$2);}
    ;

OptTag:
    ID                                        {$$=create_node(OPT_TAG,@$.first_line,1,0);add_children($$,1,$1);}
    |/* empty */                              {$$=create_node(OPT_TAG,@$.first_line,0,0);}
    ;

Tag:
    ID                                        {$$=create_node(TAG,@$.first_line,1,0);add_children($$,1,$1);}
    ;

//DECLARATION
VarDec:
    ID                                        {$$=create_node(VAR_DEC,@$.first_line,1,0);add_children($$,1,$1);}
    |VarDec LB INT RB           %prec pri0    {$$=create_node(VAR_DEC,@$.first_line,4,0);add_children($$,4,$1,$2,$3,$4);}
    |VarDec LB INT              %prec pri1    {$$=create_node(VAR_DEC,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    ;

FunDec:
    ID LP VarList RP            %prec pri0    {$$=create_node(FUN_DEC,@$.first_line,4,0);add_children($$,4,$1,$2,$3,$4);}
    |ID LP RP                   %prec pri0    {$$=create_node(FUN_DEC,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |ID LP VarList              %prec pri1    {$$=create_node(FUN_DEC,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
;

VarList:
    ParamDec COMMA VarList      %prec pri0    {$$=create_node(VAR_LIST,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |ParamDec                                 {$$=create_node(VAR_LIST,@$.first_line,1,0);add_children($$,1,$1);}
    ;

ParamDec:
    Specifier VarDec                          {$$=create_node(PARAM_DEC,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |VarDec                                   {$$=create_node(PARAM_DEC,@$.first_line,1,0);add_children($$,1,$1);}
    ;

//STATEMENT
CompStm:
    LC DefList StmtList RC                    {$$=create_node(COMP_STM,@$.first_line,4,0);add_children($$,4,$1,$2,$3,$4);}
    ;

StmtList:
    Stmt StmtList                             {$$=create_node(STMT_LIST,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |/* empty */                              {$$=create_node(STMT_LIST,@$.first_line,0,0);}
    ;

Stmt:
    Exp SEMI                    %prec pri2    {$$=create_node(STMT,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |CompStm                                  {$$=create_node(STMT,@$.first_line,1,0);add_children($$,1,$1);}
    |RETURN Exp SEMI            %prec pri2    {$$=create_node(STMT,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |IF LP Exp RP Stmt          %prec LELSE   {$$=create_node(STMT,@$.first_line,5,0);add_children($$,5,$1,$2,$3,$4,$5);}
    |IF LP Exp RP Stmt ELSE Stmt              {$$=create_node(STMT,@$.first_line,7,0);add_children($$,7,$1,$2,$3,$4,$5,$6,$7);}
    |WHILE LP Exp RP Stmt                     {$$=create_node(STMT,@$.first_line,5,0);add_children($$,5,$1,$2,$3,$4,$5);}

    |error SEMI                 %prec pri3    {yyerrok;$$=create_node(SEMI,@$.first_line,0,0);readError($$->linenum,$$->issemanticValue);has_error=1;}
    ;


//LOCAL DEFINITION
DefList:
    Def DefList                               {$$=create_node(DEF_LIST,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |/* empty */                              {$$=create_node(DEF_LIST,@$.first_line,0,0);}
    ;

Def:
    Specifier DecList SEMI                    {$$=create_node(DEF,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    ;

DecList:
    Dec                                       {$$=create_node(DEC_LIST,@$.first_line,1,0);add_children($$,1,$1);}
    |Dec COMMA DecList                        {$$=create_node(DEC_LIST,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    ;

Dec:
    VarDec                                    {$$=create_node(DEC,@$.first_line,1,0);add_children($$,1,$1);}
    |VarDec ASSIGNOP Exp                      {$$=create_node(DEC,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    ;

//EXPRESSION

Exp:
    Exp ASSIGNOP Exp                           {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);} 
    |Exp AND Exp                               {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp OR Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp EQ Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp NEQ Exp                               {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp LT Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp LE Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp GT Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp GE Exp                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp PLUS Exp                              {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp MINUS Exp                             {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp STAR Exp                              {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp DIV Exp                               {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |LP Exp RP                                 {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |MINUS Exp                                 {$$=create_node(EXP,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |NOT Exp                                   {$$=create_node(EXP,@$.first_line,2,0);add_children($$,2,$1,$2);}
    |ID LP Args RP                             {$$=create_node(EXP,@$.first_line,4,0);add_children($$,4,$1,$2,$3,$4);}
    |ID LP RP                                  {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp LB Exp RB                             {$$=create_node(EXP,@$.first_line,4,0);add_children($$,4,$1,$2,$3,$4);}
    |Exp DOT ID                                {$$=create_node(EXP,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |ID                         %prec pri0     {$$=create_node(EXP,@$.first_line,1,0);add_children($$,1,$1);}
    |INT                        %prec pri0     {$$=create_node(EXP,@$.first_line,1,0);add_children($$,1,$1);}
    |FLOAT                      %prec pri0     {$$=create_node(EXP,@$.first_line,1,0);add_children($$,1,$1);}

    |error Exp                  %prec pri1     {yyerrok;$$=create_node(EXP,@$.first_line,0,0);readError($$->linenum,$$->issemanticValue);has_error=1;}
    ;

Args:
    Exp COMMA Args                          {$$=create_node(ARGS,@$.first_line,3,0);add_children($$,3,$1,$2,$3);}
    |Exp                                    {$$=create_node(ARGS,@$.first_line,1,0);add_children($$,1,$1);}
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr," ");
}