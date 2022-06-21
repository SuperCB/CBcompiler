%{
int chars=0;
int words=0;
int lines=0;

%}


%%

[a-zA-Z]+   {  words++;chars+=strlen(yytext); printf("%s\n",yytext);}

. {           chars++;printf("%s", yytext);}

%%

int yywrap(void )
{
    return 1;
}

int main()
{
   yylex();
}