%code requires {
      #include "python_ast_node.hpp"
      #include <iostream>
      #include <string>
      #include <stdio.h>
      #include <stdlib.h>
}
%union {
      	AstNode* astNode;
}


%{
int yydebug=1;
void yyerror(const char *);
AstNode* root = NULL;
int n_nodes = 0;
int n_nodess = 0;

extern FILE *yyin;
extern int yylex();
extern int yyparse();

%}
%error-verbose


%token <astNode> ARRAY NEWLINE EQUAL INPUT INDENTERROR DEDENT LT GT LTE GTE UMINUS
%token <astNode> CLASS TRY EXCEPT MATCH CASE WITH AS INT FLOAT STR BOOL LIST PASS
%token <astNode> DEF IF ELIF ELSE BREAK CONTINUE GLOBAL NONLOCAL YIELD RETURN WHILE FOR IN RANGE PRINT 
%token <astNode> ID INT_NUMBER FLOAT_NUMBER INDENT STRING


%type <astNode> prog statement statements elif_header elif_stmt elif_stmts elif_else elif_else_ if_header if_stmt NUMBER 
%type <astNode> func_elif_header func_elif_stmt func_elif_stmts func_else_stmt func_elif_else func_elif_else_ func_if_header 
%type <astNode> func_if_stmt func_for_stmt_ func_for_stmts func_for_block func_for_stmt func_while_stmt function_compound_stmt 
%type <astNode> function_sp_stmt function_stmt_ function_stmts function_block function
%type <astNode> args args_ arg argsp args_p argp while_stmt
%type <astNode> for_stmt range_args for_block for_stmts for_stmt_ for_sp_stmt for_compound_stmt for_if_stmt for_if_header for_elif_else_
%type <astNode> for_elif_else for_else_stmt for_elif_stmts for_elif_stmt for_elif_header
%type <astNode> function_call class class_block class_stmts class_stmt_ class_sp_stmt block stmts stmt simple_stmt compound_stmt
%type <astNode> assignment return_stmt yield_stmt global_stmt nonlocal_stmt relation_stmt expression 
%type <astNode> try_except_stmt except_clauses except_clause match_stmt case_statements case_statement final_case match_block
%type <astNode>  else_stmt data_type  
%type <astNode> with_statement with_statement_body with_body with_stmt_contents with_item inside_brackets target targets 

%nonassoc '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%%

/* Parser Grammar */

prog :/* for empty put % empty */ {$$ = NULL;}
     | statements {
               std::string name = "Prog" + std::to_string(n_nodes);
               ++n_nodes;
               $$ = new Prog("module");
               $$->add($1) ;
               root = $$;
               YYACCEPT;
    }
;

statements : statement {
                std::string nname = "statements" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new StatementsNode("Statements"); $$->add($1);
                                                }
           | statements NEWLINE statement { $1->add($3); $$ = $1;}
           | statements NEWLINE { $$ = $1;}
;


statement : if_stmt { $$ = $1;}
          | while_stmt {$$ = $1; }
          | for_stmt {$$ = $1; }
          | function {$$ = $1; }
          | function_call {$$ = $1; }
          | assignment {$$ = $1; }
          | class {$$ = $1; }
          | try_except_stmt {$$ = $1; }
          | match_stmt {$$ = $1; }
          | with_statement {$$ = $1; }
;

NUMBER : INT_NUMBER {
                $$ = $1;}
       | FLOAT_NUMBER {
                $$ = $1;}
;

//if
if_stmt : if_header block elif_else_ {
      std::string name = "if" + std::to_string(n_nodes);
      ++n_nodes;
      $$ = new IfStmtNode(name );
      $$->add($1);
      $$->add($2);
      $$->add($3);  
  }  
;

if_header : IF relation_stmt {$$ = $2;}
;

elif_else_ : /* empty */{ $$ = NULL ;}
           | elif_else { $$ = $1; }  
;

elif_else  : elif_stmts else_stmt { 
        std::string name = "elfels" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ElifElseNode(name);
        $$->add($1);
        $$->add($2); 
        }
         | elif_stmts {
        std::string name = "elf" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ElifElseNode(name); 
        $$->add($1); 
        }
        | else_stmt  { $$ = $1; }
;

else_stmt : ELSE block {
        std::string name = "els" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ElseNode(name);
        $$->add($2); }
;

elif_stmts : elif_stmt { $$ = $1; }
           | elif_stmts elif_stmt { 
        std::string name = "elfls" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ElifStmtsNode(name);
        $$->add($1); 
        $$->add($2);
         }
;

elif_stmt
  : elif_header block {
        std::string name = "elfelsw" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ElifStmtNode(name); 
        $$->add($1);
        $$->add($2); 
        }
;

elif_header 
  : ELIF relation_stmt {$$ = $2; }
;


//def
function : DEF ID '(' args ')' function_block {
             std::string name = "func" + std::to_string(n_nodes);
             ++n_nodes;
             IdentifierNode* idFunc = dynamic_cast<IdentifierNode*>($2);
             $$ = new FunctionNode(idFunc->value);
             $$->add($4);
             $$->add($6);          
        }
        | DEF ID '(' args ')' '-' GT data_type function_block { 
            std::string name = "func" + std::to_string(n_nodes);
             ++n_nodes;
             IdentifierNode* idFunc = dynamic_cast<IdentifierNode*>($2);
             $$ = new FunctionNode(idFunc->value);
             $$->add($4);
             $$->add($9);
        }
;

function_block : NEWLINE INDENT function_stmts DEDENT { $$ = $3;}
;

function_stmts : function_stmt_ { 
                std::string name = "funstmt" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FunctionStatementsNode(name); $$->add($1);
                }
               | function_stmts function_stmt_ {$1->add($2); $$ = $1;}
;

function_stmt_ : simple_stmt NEWLINE {$$ = $1;}
               | function_compound_stmt {$$ =$1;}
               | function_sp_stmt NEWLINE {$$ = $1; }
;

function_sp_stmt 
            : return_stmt {$$ = $1;}
            | global_stmt {$$ = $1;}
            | nonlocal_stmt {$$ = $1;}
            | yield_stmt {$$ = $1;}
;

function_compound_stmt
        : func_if_stmt {$$ = $1;}
        | func_while_stmt {$$ = $1;}
        | func_for_stmt {$$ = $1;}
        | try_except_stmt {$$ = $1;}
        | with_statement {$$ = $1;}
        | match_stmt {$$ = $1;}
        |function_call{$$ =$1;}
        | function {$$ = $1;}
;

//while
func_while_stmt : WHILE relation_stmt func_for_block { 
             std::string name = "funcWhile" + std::to_string(n_nodes);
             ++n_nodes;
             $$ = new FunctionOfWhileNode(name);
             $$->add($2);
             $$->add($3);
               }
;

func_for_stmt : FOR ID IN RANGE range_args func_for_block { 
            std::string name = "funcFor" + std::to_string(n_nodes);
             ++n_nodes;
             $$ = new FunctionOfForNode(name);
             $$->add($2);
             $$->add($5); 
             $$->add($6); 
        }
        | FOR ID IN ARRAY func_for_block { 
               std::string name = "funcFor" + std::to_string(n_nodes);
               ++n_nodes;
               $$ = new FunctionOfForNode("Function Of For");
               $$->add($5); 
        }
;

func_for_block
        : NEWLINE INDENT func_for_stmts DEDENT {$$ = $3; }
;

func_for_stmts   
        : func_for_stmt_ {
                std::string name = "funcForst" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FuncForStmtsNode(name); $$->add($1); }
        | func_for_stmts func_for_stmt_ { $1->add($2); $$ = $1; }
;

func_for_stmt_   
        : simple_stmt NEWLINE { $$ = $1 ;}
        | for_compound_stmt { $$ = $1 ;}
        | for_sp_stmt NEWLINE {}
        | function_sp_stmt {$$ = $1 ;}
;


func_if_stmt : func_if_header function_block func_elif_else_  {}                     
;

func_if_header : IF relation_stmt
        | IF '(' relation_stmt ')'  
;

func_elif_else_  :     {/* empty no next elif or else*/}
                 | func_elif_else { }
;

func_elif_else : func_elif_stmts func_else_stmt
               | func_elif_stmts
               | func_else_stmt
;

func_else_stmt : ELSE  function_block 
;

func_elif_stmts : func_elif_stmt
                | func_elif_stmts func_elif_stmt 
;

func_elif_stmt : func_elif_header function_block
;

func_elif_header : ELIF relation_stmt
                 | ELIF '(' relation_stmt ')'    
;


// args for function
args : { std::string name = "args" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new Args(name,"Args");
       }
    | args_  {  $$ = $1; }
;



args_  : arg {
        std::string name = "args" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new Args(name,"Args"); $$->add($1); }
       | args_ ',' arg { $1->add($3); $$ = $1; }
;



arg : ID {
        std::string nnname = "arg1" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new Arg (nnname);
        std::string nname = "iden" + std::to_string(n_nodes);
        ++n_nodes;
        $1->name=nname;
        //$$->add($1);
        }
    | ID ':' data_type {
        std::string nnname = "arg2" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new Arg (nnname); 
        std::string nname = "idenn" + std::to_string(n_nodes);
        ++n_nodes;
        $1->name=nname;
       // $$->add($1);
        //$$->add($3);
    }
;

// args for print function
argsp  
    : /* empty params */ {
        std::string name = "argspp" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ArgsPrint(name,"Argsp"); }
    | args_p { $$ = $1 ; }
;

args_p
    : argp {
          std::string name = "argp" + std::to_string(n_nodes);
                ++n_nodes;
               
        $$ = new ArgsPrint(name,"Argsp"); $$->add($1); }
    | args_p  argp { $1->add($2); $$ = $1 ;}

;



argp  
    : ID {$$ = $1; }
    | NUMBER { $$ = $1; }
    | STRING {$$ = $1; }
  
;


while_stmt
        : WHILE relation_stmt for_block { 
                  std::string name = "whlie" + std::to_string(n_nodes);
                  ++n_nodes;
                  $$ = new WhileStatementsNode(name);
                  $$->add($2);
                  $$->add($3);
 
        }
;


//for
range_args : '(' NUMBER ')' {
                std::string name = "rang" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new rangeArgsNode(name);
                $$->add($2);
        }
          | '(' NUMBER ',' NUMBER')' {
                std::string name = "rang1" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new rangeArgsNode("rang");
                $$->add($2);
                $$->add($4);
                          }
          | '(' NUMBER ',' NUMBER ',' NUMBER ')' {
                std::string name = "rang2" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new rangeArgsNode(name);
                $$->add($2);
                $$->add($4);
                $$->add($6);
        }
;

for_stmt : FOR ID IN RANGE range_args for_block { 
              std::string name = "for" + std::to_string(n_nodes);
                  ++n_nodes;
                  $$ = new ForStatementsNode(name);
                  $$->add($2);
                  $$->add($5); 
                  $$->add($6); 
            
        }
        | FOR ID IN ARRAY for_block { 
             std::string name = "for" + std::to_string(n_nodes);
                  ++n_nodes;
                  $$ = new ForStatementsNode("For ");
                  $$->add($2);
                  $$->add($4);
                  $$->add($5);  
        }
;


for_block : NEWLINE INDENT for_stmts DEDENT { $$ = $3 ;}
;

for_stmts : for_stmt_ {
                std::string name = "forstmts" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new ForBlockStatements(name); $$->add($1);}
          | for_stmts for_stmt_ {$1->add($2); $$ = $1;}
;

for_stmt_  : simple_stmt NEWLINE {$$ = $1 ;}
           | for_compound_stmt {$$ = $1;}
           | for_sp_stmt NEWLINE 
;

for_sp_stmt : BREAK
            | CONTINUE
;

for_compound_stmt : for_if_stmt {$$ = $1 ;}
                  | while_stmt {$$ = $1 ;}
                  | for_stmt {$$ = $1 ;}
                  | try_except_stmt {$$ = $1 ;}
                  | with_statement {$$ = $1 ;}
                  | match_stmt {$$ = $1 ;}
;


for_if_stmt : for_if_header for_block for_elif_else_  { 
                 std::string name = "forIf" + std::to_string(n_nodes);
                  ++n_nodes;
                  $$ = new ForIFStatements("For IF");
                  $$->add($1);
                  $$->add($2);
                  $$->add($3);  
                 }                     
;

for_if_header : IF relation_stmt { $$ = $1;}
              | IF '(' relation_stmt ')'  { $$ = $1 ;}
;

for_elif_else_ :   /* empty no next elif or else*/  {$$ = NULL ;}
               | for_elif_else { $$ = $1 ;}
;

for_elif_else : for_elif_stmts for_else_stmt {
                $$ = new ForElifElse("for elif else ");
                $$->add($1);
                $$->add($2);
        
        }
             | for_elif_stmts {
                $$ = new ForElifElse("for elif stmt ");
                $$->add($1);
                }
             | for_else_stmt {
                $$ = new ForElifElse("for else stmt ");
                $$->add($1);}
;

for_else_stmt   
        : ELSE  for_block {$$ = $2; }
;


for_elif_stmts  
        : for_elif_stmt {$$ = new ForElif("For Elif"); $$->add($1);}
        | for_elif_stmts for_elif_stmt {$1->add($2); $$ = $1;}
;

for_elif_stmt   
        : for_elif_header for_block {
                $$ = new ForElifStmt("For Elif Stmt");
                $$->add($1);
                $$->add($2);
        
        }
;

for_elif_header 
        : ELIF relation_stmt { $$ = $2 ;}
        | ELIF '(' relation_stmt ')'    {$$  = $3 ;}
;



function_call : ID '(' args ')' { 
                std::string name = "funcCall" + std::to_string(n_nodes);
                ++n_nodes;
                IdentifierNode* idFunc = dynamic_cast<IdentifierNode*>($1);
                $$ = new FunctionCallNode(idFunc->value);
                $$->add($3);
                              }
             | PRINT '(' argsp ')' {
                std::string name = "funcCallp" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FunctionCallNode(name);
                $$->add($3);
            
            }
            | PRINT '(' argsp ',' argsp ')' {
                std::string name = "funcCallp1" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FunctionCallNode(name);
                $$->add($3);
                $$->add($5);
            
            }
            | INPUT '(' STRING ')' {
                std::string name = "funcCalli" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FunctionCallNode(name);
                $$->add($3);
            }
;

class : CLASS ID class_block { 
         std::string name = "class" + std::to_string(n_nodes);
         ++n_nodes;
         IdentifierNode* idClass = dynamic_cast<IdentifierNode*>($2);
         $$ = new ClassNode(idClass->value);
         $$->add($3);
    }
;

class_block : NEWLINE INDENT class_stmts DEDENT { $$ = $3 ;}
;

class_stmts : class_stmt_ { 
        std::string name = "cls" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ClassStatementsNode(name); $$->add($1);}
           | class_stmts class_stmt_ { $1->add($2); $$ = $1;}
;

class_stmt_ : simple_stmt NEWLINE {$$ = $1 ;}
            | compound_stmt {$$ = $1 ;}
            | class_sp_stmt NEWLINE {$$ = $1 ;}
            | function {$$ = $1 ;}
;

class_sp_stmt : global_stmt { $$  = $1 ;}
;  


try_except_stmt : TRY block except_clauses { 
               std::string name = "try" + std::to_string(n_nodes);
               ++n_nodes;
               $$ = new TryStatementsNode(name); 
               $$->add($2);
               $$->add($3);
            }
;

except_clauses  : except_clause {
                std::string name = "excp" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new ExceptStatementsNode(name); $$->add($1);
            }
                | except_clauses except_clause {$1->add($2); $$ = $1;}
;

except_clause  : EXCEPT block {
                   std::string name = "exs" + std::to_string(n_nodes);
                   ++n_nodes;
                  $$ = new ExceptNode(name);
                  $$->add($2);
        }
;


match_stmt  
        : MATCH ID match_block { 
               std::string name = "match" + std::to_string(n_nodes);
               ++n_nodes;
               $$ = new MatchStatementsNode(name); 
               $$->add($2);
               $$->add($3);
        }
;

case_statements :
            case_statement {
                std::string name = "case" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new CaseStatementsNode(name); $$->add($1);
            }
               | case_statements case_statement {$1->add($2); $$ = $1;}
;

case_statement : CASE argp block {
                std::string name = "case2" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new CaseNode(name); 
                $$->add($2);
                $$->add($3);
            }
;

final_case : CASE '_' block {
        std::string name = "case3" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new FinalCaseNode(name);
        $$->add($3);
        }
;

match_block : NEWLINE INDENT case_statements final_case DEDENT {
        std::string name = "case3" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new MatchBlockNode(name);
        $$->add($3);
        $$->add($4);
         }
;

with_statement : WITH with_statement_body block  { 
               std::string name = "with" + std::to_string(n_nodes);
               ++n_nodes;
               $$ = new WithStatementsNode(name); 
               $$->add($2);
               $$->add($3);
        }
;

with_statement_body : with_body {   
                        std::string name = "withstmt" + std::to_string(n_nodes);
                         ++n_nodes;
                         $$ = new WithBodyNode(name); 
                         $$->add($1);
                         }
                    | with_body ',' with_statement_body {$1->add($3); $$ = $1; }         
;

with_body : with_stmt_contents {$$ = $1;}
          |'(' with_stmt_contents ')' {$$ = $2 ;}
;


with_stmt_contents : with_item { $$=$1;}
;

with_item : ID '(' inside_brackets ')' AS target { 
                std::string name = "withIt" + std::to_string(n_nodes);
                 ++n_nodes;
                 $$ = new WithItemNode(name); 
                 $$->add($1);
                 $$->add($3);
                 $$->add($5); }
        | expression { 
                 std::string name = "withIte" + std::to_string(n_nodes);
                 ++n_nodes;
                 $$ = new WithItemNode(name); 
                 $$->add($1);}
        | expression AS target{
                 std::string name = "withItem" + std::to_string(n_nodes);
                 ++n_nodes;
                 $$ = new WithItemNode(name); 
                 $$->add($1);
                 $$->add($3);
        }
;

inside_brackets : expression {std::string name = "bracket" + std::to_string(n_nodes);
                         ++n_nodes;
                         $$ = new bracketsNode(name); 
                         $$->add($1);}
                | expression ',' inside_brackets {$3->add($1); $$ = $3;}
;

target : '(' targets ')'  {
        std::string name = "target" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new TargetNode(name); 
        $$->add($2);
        }
      | target '.' ID 
        {std::string name = "target1" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new TargetNode(name); 
        $$->add($1);
        $$->add($3);
        }
      | ID {
        std::string name = "target2" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new TargetNode(name); 
        $$->add($1);
    }
;

targets : target { 
        std::string name = "tr" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new TargetInsideNode(name); 
        $$->add($1);
        }
        | targets ',' target{
         std::string name = "tr2" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new TargetInsideNode(name); 
        $$->add($1);
        $$->add($3);
    }
;





block : NEWLINE INDENT stmts DEDENT { $$ = $3; }
;

stmts : stmt { 
        std::string name = "stmts" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new StmtsNode(name); $$->add($1);}
    | stmts stmt {$1->add($2); $$ = $1;}
;

stmt : simple_stmt NEWLINE {$$ =$1;}
     | compound_stmt {$$ = $1;}
;


simple_stmt : assignment      {$$ = $1;}
            |function_call { $$ = $1 ;}
            |PASS {$$ = $1;}
;

compound_stmt : if_stmt    {$$ = $1;}
              | while_stmt {$$ = $1;}
              | for_stmt   {$$ = $1;}
              | try_except_stmt {$$ = $1;}
              | with_statement {$$ = $1;}
              | match_stmt {$$ = $1;}
;

assignment : ID '=' expression  { 
                std::string nnname = "assig" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new assignmentStatement(nnname);
                std::string nname = "iden" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1);
                $$->add($3);}
           | ID '=' ARRAY  {
                 $$ = new assignmentStatement("assign2");
                std::string nname = "iden" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1);
                $$->add($3);
        }
;

return_stmt : RETURN NUMBER {
                std::string name = "return" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new ReturnNode(name);
                $$->add($2);}
            | RETURN ID {   
                std::string name = "return2" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new ReturnNode(name);
                $$->add($2);}
            | RETURN STRING { 
                std::string name = "return3" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new ReturnNode(name);
                $$->add($2);
        }
;

yield_stmt : YIELD ID {
                std::string name = "yield" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new YieldNode(name);
                $$->add($2);
         }
;

global_stmt : GLOBAL ID {
                std::string name = "global" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new GlobalNode(name);
                $$->add($2);
                 }
;

nonlocal_stmt : NONLOCAL ID {
                std::string name = "nonlocal" + std::to_string(n_nodes);
                ++n_nodes; 
                $$ = new NonlocalNode(name);
                $$->add($2);
        }
;

relation_stmt : ID GT NUMBER    { 
                std::string name = "rel1" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new RelationStmtNode(name);
                std::string nname = "idenq" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1);
              
                $$->add($3);
        }
        | ID LT NUMBER    {
                std::string name = "rel2" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new RelationStmtNode(name);
                std::string nname = "idenw" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1);
            
                $$->add($3);}
        | ID GTE NUMBER   {
                std::string name = "rel3" + std::to_string(n_nodess);
                ++n_nodess;
                std::string nname = "idene" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$ = new RelationStmtNode(name);
                $$->add($1);
          
                $$->add($3);}
        | ID LTE NUMBER   {
                std::string name = "rel3" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new RelationStmtNode(name);
                std::string nname = "ident" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                            $$->add($1);
                        
                            $$->add($3);
        }
        | ID EQUAL NUMBER {
                std::string name = "rel4" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new RelationStmtNode(name);
                std::string nname = "idenu" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1);$$->add($3);}
        | ID EQUAL STRING {
                std::string name = "rel5" + std::to_string(n_nodess);
                ++n_nodess;
                $$ = new RelationStmtNode(name);
                std::string nname = "idenp" + std::to_string(n_nodes);
                ++n_nodes;
                $1->name=nname;
                $$->add($1); $$->add($3);}
;

expression : expression '+' expression     {
                std::string name = "plus" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new ExpressionPlusNode (name); $$->add($1); $$->add($3);}
        | expression '-' expression     { 
                std::string name = "minus" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new ExpressionMinusNode (name); $$->add($1); $$->add($3); }
        | expression '*' expression     { 
                std::string name = "mult" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new ExpressionMultNode (name); $$->add($1); $$->add($3); }
        | expression '/' expression     {
                std::string name = "dreve" + std::to_string(n_nodes);
                ++n_nodes;
                 $$ = new ExpressionDivisionNode (name); $$->add($1); $$->add($3);}
        | '|' expression %prec UMINUS  { }
        | '-' expression %prec UMINUS   { }
        | NUMBER                        { $$ = $1 ;}
        | STRING                        { $$ = $1 ;}
        | ID                            { $$ = $1 ;}
;

data_type : INT {
            std::string name = "int" + std::to_string(n_nodes);
            ++n_nodes;      
            $$ = new INTNode(name);
            $$ = $1 ;
        } 
        | FLOAT {
                std::string name = "float" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new FloatNode(name);
                 $$ = $1 ; 
        }
        | BOOL {
                std::string name = "bool" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new BoolNode(name);
                $$ = $1;        
        }
        | STR {
                std::string name = "STR6" + std::to_string(n_nodes);
                ++n_nodes;
                $$ = new STRNode("STR");
                $$ = $1 ;         
        }
        | LIST '[' INT ']'  {
        std::string name = "list" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ListNode(name);
        $$->add($3);
                 }
        | LIST '[' FLOAT ']'{
        std::string name = "list2" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ListNode(name);
        $$->add($3);
        }
        | LIST '[' STR ']'{
        std::string name = "list" + std::to_string(n_nodes);
        ++n_nodes;
        $$ = new ListNode(name);
        $$->add($3);
        }
;



%%


int main(int argc, char **argv){

        yyin=fopen(argv[1],"r");
        yyparse();

        if (root != NULL) {
        AST ast(root);
        ast.Print();
        }
        return 0;
}


void yyerror(const char* s) {
    std::cerr << "error in parser: " << s << std::endl;
}