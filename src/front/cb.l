%{
#include"Token.h"
%}


letter [A-Za-z_]
digit      [0-9]
Ident        {letter}({letter}|{digit})*

IntConst   {digit}+

%%



void  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Void,yytext);
             }

int  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Int,yytext);
             }

const  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Const,yytext);
             }

while  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(While,yytext);
             }

if  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(If,yytext);
             }

else  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Else,yytext);
             }

return  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Return,yytext);
             }

break  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Break,yytext);
             }

continue  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Continue,yytext);
             }
'\+'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Add,yytext);
             }

'-'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Sub,yytext);
             }

'\*'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Mul,yytext);
             }

'/'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Div,yytext);
             }

'%'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Mod,yytext);
             }

'<'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Lt,yytext);
             }

'<='  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Le,yytext);
             }

'>='  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Ge,yytext);
             }

'>'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Gt,yytext);
             }

'=='  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Eq,yytext);
             }

'!='  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Ne,yytext);
             }

'&&'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(And,yytext);
             }

'\|\|'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Or,yytext);
             }

'='  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Assign,yytext);
             }

','  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Comma,yytext);
             }

';'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Semi,yytext);
             }

'!'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(Not,yytext);
             }

'\('  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(LPar,yytext);
             }

'\)'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(RPar,yytext);
             }

'\['  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(LBrk,yytext);
             }

'\]'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(RBrk,yytext);
             }

'\{'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(LBrc,yytext);
             }

'\}'  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(RBrc,yytext);
             }


{Ident}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
              lex_next(ID,yytext);
             }


{IntConst}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(IntConst,yytext);
             }


.  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

      }


%%

int yywrap(void )
{
    return 1;
}

int main()
{
   yylex();
}