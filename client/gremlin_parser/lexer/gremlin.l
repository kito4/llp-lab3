%option noyywrap
%option nounistd

%{
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "parser.h"
%}

STRING_LITERAL \"([^\\\"]|\\.)*\"
INTEGER_LITERAL -?[0-9]+
FLOAT_LITERAL [0-9]*([0-9]\.?)[0-9]*

%%
"("[[:space:]\n]*               {return L_PAR;}
[[:space:]\n]*")"               {return R_PAR;}
[[:space:]\n]*","[[:space:]\n]* {return COMMA;}

";"               {return SEMICOLON;}
"."               {return DOT;}
"create()"        {return CREATE_F;}
"drop()"          {return DROP_F;}
"properties()"    {return PROPERTIES_F;}
"Int()"           {return INT32_F;}
"Int64()"         {return INT64_F;}
"Double()"        {return DOUBLE_F;}
"Bool()"          {return BOOL_F;}
"String()"        {return STRING_F;}
"vertexLabel"     {return VERTEX_LABEL;}
"edgeLabel"       {return EDGE_LABEL;}
"schema"          {return SCHEMA;}
"g"               {return GRAPH;}
"V()"             {return V_F;}
"has"             {return HAS;}
"hasLabel"        {return HAS_LABEL;}
"out"             {return OUT;}
"in"              {return IN;}
"filter"          {return FILTER;}
"values()"        {return VALUES_F;}
"or"              {return OR;}
"containing"      {return CONTAINING;}
"neq"             {return NEQ;}
"gt"              {return GT;}
"lt"              {return LT;}
"gte"             {return GTE;}
"lte"             {return LTE;}
"addEdge"         {return ADD_EDGE;}
"addVertex"       {return ADD_VERTEX;}
"outE"            {return OUT_E;}
"inE"             {return IN_E;}
"property"        {return PROPERTY;}

{STRING_LITERAL}  { 
  yylval.as_string = malloc(sizeof(char) * (strlen(yytext) - 1));
  strncpy(yylval.as_string, (char*)yytext + 1, strlen(yytext) - 2);
  yylval.as_string[strlen(yytext) - 2] = '\0';
  return STRING_LIT;
}
{INTEGER_LITERAL} {
  yylval.as_int = atoi(yytext);
  return INTEGER_LIT;
}
{FLOAT_LITERAL} {
  yylval.as_double = atof(yytext);
  return DOUBLE_LIT;
}
"\n"              ;
.                 { return *yytext; }
%%