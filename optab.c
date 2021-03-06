// AV Lukas Axelborn

/**********************************************************************/
/* lab 1 DVG C01 - Operator Table OBJECT                              */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define NENTS 4

static int optab[][NENTS] = {
   {'+', integer, integer, integer},
   {'+', real,    real,    real},
   {'+', integer, real,    real},
   {'+', real,    integer, real},
   {'*', integer, integer, integer},
   {'*', real,    real,    real},
   {'*', integer, real,    real},
   {'*', real,    integer, real},
   {'$', undef,   undef,   undef}
   };

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* display the op tab                                                 */
/**********************************************************************/
void p_optab()
{
   printf("________________________________________________________\n");
   printf("THE OPERATOR TABLE\n");
   printf("________________________________________________________\n");
   printf("   operator        arg1       arg2     result\n");
   printf("________________________________________________________\n");

   for (int j = 0; optab[j][0] != '$'; j++)
   {
      printf("    %7s,\t%7s,   %7s,   %7s\n", tok2lex(optab[j][0]), tok2lex(optab[j][1]), tok2lex(optab[j][2]), tok2lex(optab[j][3]));
   }
   printf("\n________________________________________________________\n");

   
}

/**********************************************************************/
/* return the type of a binary expression op arg1 arg2                */
/**********************************************************************/
int get_otype(int op, int arg1, int arg2)
{  
   if (op == '+' || op == '*')
   {
      switch (arg1 + arg2)
      {
      case (integer+integer):
         return integer;
         break;
      
      case (real+real):
         return real;
         break;

      case (integer+real):
         return real;
         break;

      default:
         break;
      }
   }
   return nfound;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
