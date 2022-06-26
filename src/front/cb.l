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
             lex_next(TokenType::Void,yytext);
             }

int  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Int,yytext);
             }

const  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Const,yytext);
             }

while  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::While,yytext);
             }

if  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::If,yytext);
             }

else  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Else,yytext);
             }

return  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Return,yytext);
             }

break  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Break,yytext);
             }

continue  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Continue,yytext);
             }

"=="       {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Eq,yytext);
             }

"="       {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Assign,yytext);
             }



"\+"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Add,yytext);
             }

"-" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Sub,yytext);
             }

"\*" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Mul,yytext);
             }

"/" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Div,yytext);
             }

"%" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Mod,yytext);
             }

"<"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Lt,yytext);
             }

"<=" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Le,yytext);
             }

">=" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Ge,yytext);
             }

">"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Gt,yytext);
             }



"!=" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Ne,yytext);
             }

"&&" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::And,yytext);
             }

"\|\|" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Or,yytext);
             }



"," {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Comma,yytext);
             }

";" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Semi,yytext);
             }

"!" {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::Not,yytext);
             }

"\("  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::LPar,yytext);
             }

"\)"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::RPar,yytext);
             }

"\["  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::LBrk,yytext);
             }

"\]"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::RBrk,yytext);
             }

"\{"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::LBrc,yytext);
             }

"\}"  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::RBrc,yytext);
             }


{Ident}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
              lex_next(TokenType::ID,yytext);
             }


{IntConst}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif
             lex_next(TokenType::IntConst,yytext);
             }


.  {
             #ifdef DEBUG
              printf("fuck%s\n",yytext);
             #endif

      }


%%

int yywrap(void )
{
    return 1;
}

