%{
#include"Token.h"
%}


letter [A-Za-z_]
digit      [0-9]
Ident        {letter}({letter}|{digit})*

IntConst   {digit}+




%%


void   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

int   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

const   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

while  {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

if   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

else   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

return   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

break   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

continue   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\+'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'-'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\*'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'/'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'%'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'<'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'<='   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'>='   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'>'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'=='   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'!='   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'&&'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\|\|'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'='   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

','   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

';'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'!'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\('   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\)'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\['   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\]'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\{'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }

'\}'   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }


{Ident}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

             }


{IntConst}   {
             #ifdef DEBUG
              printf("%s\n",yytext);
             #endif

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