/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
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
#include "keytoktab.h"         /* when the keytoktab is added   */
/* #include "lexer.h"       */ /* when the lexer     is added   */
/* #include "symtab.h"      */ /* when the symtab    is added   */
/* #include "optab.h"       */ /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int lookahead = 0;
static int is_parse_ok = 1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/* define tokens + keywords NB: remove this when keytoktab.h is added */
/**********************************************************************/
enum tvalues
{
   program = 257,
   id,
   input,
   output,
   var = 261,
   integer,
   begin,
   assign,
   number,
   end,
   real,
   boolean

};
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';', var, id, ',', id, ',', id, ':', integer, ';', begin, id, assign, id, '+', id, '*', number, end, '.',
                       '$'};

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
static int pget_token()
{
   static int i = 0;
   if (tokens[i] != '$')
      return tokens[i++];
   else
      return '$';
}

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if (DEBUG)
      printf("\n --------In match expected: %4d, found: %4d",
             t, lookahead);
   if (lookahead == t)
      lookahead = pget_token();
   else
   {
      is_parse_ok = 0;
      printf("\n *** Unexpected Token: expected: %4d found: %4d (in match)",
             t, lookahead);
   }
}

/**********************************************************************/
/* var_part functions                                                 */
/**********************************************************************/

static void type()
{
   switch (lookahead)
   {
   case integer:
      match(integer);
      break;

   case real:
      match(real);
      break;

   case boolean:
      match(boolean);
      break;

   default:
      break;
   }
}
static void id_list()
{
   match(id);
   if (lookahead == ',')
   {
      match(',');
      id_list();
   }
}

static void var_dec()
{
   id_list();
   if (lookahead == ':')
   {
      match(':');
      type();
      match(';');
   }
}

static void var_dec_list()
{
   var_dec();
   if (lookahead == id)
      var_dec_list();
}

/**********************************************************************/
/* stat_part functions                                                */
/**********************************************************************/

static void operand()
{
   switch (lookahead)
   {
   case id:
      match(id);
      break;

   case number:
      match(number);
      break;

   default:
      break;
   }
}

static void term(); // funtion prototype for expr()

static void expr()
{
   term();
   if (lookahead == '+')
   {
      match('+');
      expr();
   }
}

static void factor()
{
   if (lookahead == '(')
   {
      match('(');
      expr();
      match(')');
   }
   else
   {
      operand();
   }
}

static void term()
{
   factor();
   if (lookahead == '*')
   {
      match('*');
      term();
   }
}

static void assign_stat()
{
   match(id);
   match(assign);
   expr();
}

static void stat()
{
   assign_stat();
}

static void stat_list()
{
   stat();
   if (lookahead == ';')
   {
      match(';');
      stat_list();
   }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

static void program_header()
{
   if (DEBUG)
      printf("\n *** In  program_header");
   match(program);
   match(id);
   match('(');
   match(input);
   match(',');
   match(output);
   match(')');
   match(';');
}

static void var_part()
{
   if (DEBUG)
      printf("\n *** In  var_part");
   match(var);
   var_dec_list();
}

static void stat_part()
{
   if (DEBUG)
      printf("\n *** In  stat_part");
   match(begin);
   stat_list();
   match(end);
   match('.');
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG)
      printf("\n *** In  parser");
   lookahead = pget_token(); // get the first token
   program_header();         // call the first grammar rule
   var_part();
   stat_part();
   return is_parse_ok; // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/