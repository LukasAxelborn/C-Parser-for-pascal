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
#include "lexer.h"             /* when the lexer     is added   */
#include "symtab.h"            /* when the symtab    is added   */
/* #include "optab.h"       */ /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
static int lookahead = 0;
static int is_parse_ok = 1;


/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

static void infunktion(const char *x)
{
   if(DEBUG)
      printf("\n *** In  %s", x);
}

static void outfunktion(const char *x)
{
   if(DEBUG)
      printf("\n *** out %s", x);
}

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if (DEBUG)
      printf("\n *** In  match \t expected: %s found: %s",
             tok2lex(t), tok2lex(lookahead));
   if (lookahead == t)
      lookahead = get_token();
   else
   {
      is_parse_ok = 0;
      printf("\n *** Unexpected Token: expected: %s found: %s (in match)",
             tok2lex(t), tok2lex(lookahead));
   }
}

/**********************************************************************/
/* var_part functions                                                 */
/**********************************************************************/

static void type()
{
   infunktion(__func__);
   switch (lookahead)
   {
   case integer:
      match(integer);
      setv_type(integer);
      break;

   case real:
      match(real);
      setv_type(real);

      break;

   case boolean:
      match(boolean);
      setv_type(boolean);

      break;

   default:
      break;
   }
   outfunktion(__func__);
}
static void id_list()
{
   infunktion(__func__);

   addv_name(get_lexeme());

   match(id);
   if (lookahead == ',')
   {
      match(',');
      id_list();
   }
   outfunktion(__func__);
}

static void var_dec()
{
   infunktion(__func__);
   id_list();
   if (lookahead == ':')
   {
      match(':');
      type();
      match(';');
   }
   outfunktion(__func__);
}

static void var_dec_list()
{
   infunktion(__func__);
   var_dec();
   if (lookahead == id)
      var_dec_list();
   outfunktion(__func__);
}

/**********************************************************************/
/* stat_part functions                                                */
/**********************************************************************/

static void operand()
{
   infunktion(__func__);
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
   outfunktion(__func__);
}

static void term(); // funtion prototype for expr()

static void expr()
{
   infunktion(__func__);

   term();
   if (lookahead == '+')
   {
      match('+');
      expr();
   }
   outfunktion(__func__);
}

static void factor()
{
   infunktion(__func__);

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
   outfunktion(__func__);
}

static void term()
{
   infunktion(__func__);

   factor();
   if (lookahead == '*')
   {
      match('*');
      term();
   }
   outfunktion(__func__);
}

static void assign_stat()
{
   infunktion(__func__);

   match(id);
   match(assign);
   expr();
   outfunktion(__func__);
}

static void stat()
{
   infunktion(__func__);
   assign_stat();
   outfunktion(__func__);
}

static void stat_list()
{
   infunktion(__func__);

   stat();
   if (lookahead == ';')
   {
      match(';');
      stat_list();
   }
   outfunktion(__func__);
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

static void program_header()
{

   infunktion("program");
   if (DEBUG)
      printf("\n *** In  program_header");
   match(program);
   addp_name(get_lexeme());
   match(id);
   match('(');
   match(input);
   match(',');
   match(output);
   match(')');
   match(';');
   outfunktion(__func__);
   if (DEBUG)
      printf("\n");
}

static void var_part()
{
   if (DEBUG)
      printf("\n *** In  var_part");
   match(var);
   var_dec_list();
   outfunktion(__func__);
   if (DEBUG)
      printf("\n");
}

static void stat_part()
{
   if (DEBUG)
      printf("\n *** In  stat_part");
   match(begin);
   stat_list();
   match(end);
   match('.');
   outfunktion(__func__);
   if (DEBUG)
      printf("\n");
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG)
      printf("\n *** In  parser");
   lookahead = get_token(); // get the first token
   program_header();         // call the first grammar rule
   var_part();
   stat_part();

   p_symtab(); // skriver ut symbål tabelen 

   return is_parse_ok; // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
