#ifndef _FORMULA_PROCESSING_H_
#define _FORMULA_PROCESSING_H_

/*
This header lib allow you to processing mathematical expressions, such as
f(x, y) = x*x - SIN(y) and so on...
How to use this? For example, if you have function which depends
of two arguments "x" and "y": f=f(x,y). And you want find meaning of this
function at point (x0, y0). Let's think you have already typed your function in
Edit1 box on your form. Than you must write the following code:

//----- Code -----------------
 int Size;
 Size = Edit1->GetTextLen();     //Get length of string in Edit1
 Size++;                         //Add room for null character
 char *str = new char[Size];     //Creates str dynamic variable
 Edit1->GetTextBuf(str,Size);    //Puts Edit1->Text into str
 function f(str);
 delete str;
//----- End Of Code ----------

You must write exactly as described because (Edit1 -> Text) contain "AnsiString"
data, but Class "function" requires char[].

Than, you want calculate your function at (x0, y0). Write following code:

//----- Code -----------------
 double x0 = 1.1;
 double y0 = 1.4;
 double F_at_x0_y0 = f.get(x0, y0);
//----- End Of Code ----------

if you want to see result:

//----- Code -----------------
 Edit2 -> Text = FloatToStr(F_at_x0_y0);
//----- End Of Code ----------

"get" is a method of Class "function" which calculates meaning of function
at point (x, y)

SUPPORTED FUNCTIONS:
SIN(); COS; TG(); ABS(); EXP(); SQRT(); LN();

SUPPORTED OPERATIONS:
(, ), *, /, +, -;

Note! Operation ^(involution) is not supported and will
not support.
Use these functions and operations for determine your function. For example:
SIN(x) + COS(y)
or
EXP(x*x + y*y)

You can type "x" as well as "X", "y" as well as "Y".
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream.h>

#define NUMBER 0
#define OPERATION 1
#define ARGUMENTX 2
#define FUNCTION 3
#define END 4
#define ARGUMENTY 5
#define PI 3.1415926535897932384626433832

//---------------------------------------------------------------------------
inline void error(char *s)
{
 Application->MessageBox(s, "ERROR in expression or during calculations:", MB_ICONERROR);
 exit(1);
}
//---------------------------------------------------------------------------
class TokenString
{
 char *ptr;
 char str[200];

 public:
  TokenString(char* s)
  {strcpy(ptr=str, s);}
  void reset(void)
  {ptr=str;}
  void gettoken(void);
  int type;
  char t[200];
  double val;
};
//---------------------------------------------------------------------------
void TokenString::gettoken(void)
{
 while(isspace(*ptr))
 ptr++;
 if(!*ptr)
  {*t=0; type=END;}
 else if(strchr("+-*/()", *ptr))
  {
   t[0]=*ptr++;
   t[1]=0;
   type=OPERATION;
  }
 else if(toupper(*ptr)=='X')
  {
   t[0]=*ptr++;
   t[1]=0;
   type=ARGUMENTX;
  }
 else if(toupper(*ptr)=='Y')
  {
   t[0]=*ptr++;
   t[1]=0;
   type=ARGUMENTY;
  }
 else if(isdigit(*ptr))
  {
   int p=0;
   char *temp=t;
   while(isdigit(*ptr)||(*ptr=='.'&&!p))
   {
    if(*ptr=='.')
    p=1;
    *temp++=*ptr++;
   }
   *temp=0;
   val=atof(t);
   type=NUMBER;
  }
 else if(isalpha(*ptr))
  {
   char *temp=t;
   while(isalpha(*ptr)||isdigit(*ptr))
   *temp++=*ptr++;
   *temp=0;
   type=FUNCTION;
  }
 else
  {
   error("Bad symbol!");
  }
}
//---------------------------------------------------------------------------
class function : private TokenString
 {
  double x, y;
  void primitive(double&);
  void level1(double&);
  void level2(double&);
  void level3(double&);
  void level4(double&);
  void level5(double&);

 public:
  function(char *f):TokenString(f) {}
  double get(double, double);
 };
//---------------------------------------------------------------------------
double function :: get(double a, double b)
 {
  x=a;
  y=b;
  reset();
  gettoken();
  if(type==END)
  error("No function");
  double result;
  level1(result);
  return result;
 }
//---------------------------------------------------------------------------
void function :: level1(double &result)
 {
  double temp;
  char op;
  level2(result);
  while((op=*t)=='+'||op=='-')
   {
    gettoken();
    level2(temp);
    if(op=='+')
     result+=temp;
    else
     result-=temp;
   }
 }
//---------------------------------------------------------------------------
void function :: level2(double &result)
 {
  double temp;
  char op;
  level3(result);
  while((op=*t)=='*'||op=='/')
   {
    gettoken();
    level3(temp);
    if(op=='*')
     result*=temp;
    else
     result/=temp;
   }
 }
//---------------------------------------------------------------------------
void function :: level3(double &result)
 {
  int f=0;
  char str[200];
  if(type==FUNCTION)
   {
    f=1;
    strcpy(str, t);
    gettoken();
   }
   level4(result);
   if(f)
    {
     strupr(str);
     if(!strcmp("SIN", str))
      result=sin(result);
     else if(!strcmp("COS", str))
      result=cos(result);
     else if(!strcmp("TG", str))
      result=sin(result)/cos(result);
     else if(!strcmp("ABS", str))
      result=fabs(result);
     else if(!strcmp("EXP", str))
      result=exp(result);
     else if(!strcmp("SQRT", str))
      if(result >= 0)
      {
       result=sqrt(result);
      }else
       {
        error(" Your function < 0 and SQRT is not available. Program stopped.");
        exit(0);
       }
     else if(!strcmp("LN", str))
      if(result > 0)
      {
       result=log(result);
      }else
       {
        error(" WARNING!\n Your function contain argument X or Y <= 0, LN is undefined for it.\n");
       }
     else error("Unknown function");
    }
 }
//---------------------------------------------------------------------------
void function :: level4(double &result)
 {
  int sign=0;
  if(*t=='-')
  {
   sign=1;
   gettoken();
  }
  level5(result);
  if(sign)
   result =-result;
 }
//---------------------------------------------------------------------------
void function :: level5(double &result)
 {
  if(*t=='(')
  {
   gettoken();
   level1(result);
   if(*t!=')')
    error("No "")""");
   gettoken();
  }
  else
   primitive(result);
 }
//---------------------------------------------------------------------------
void function :: primitive(double &result)
 {
  switch(type)
  {
   case NUMBER:
    result=val;
    gettoken();
    break;
   case ARGUMENTX:
    result=x;
    gettoken();
    break;
   case ARGUMENTY:
    result=y;
    gettoken();
    break;

   default:
    error("Number or X or Y needed");
  }
 }
#endif
