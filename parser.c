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
#include "optab.h"             /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
static int lookahead = 0;


/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

static void infunktion(const char *x)
{
   if(DEBUG)
      printf(" *** In  %s\n", x);
}

static void outfunktion(const char *x)
{
   if(DEBUG)
      printf(" *** out %s\n", x);
}

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static int match(int t)
{
   if (DEBUG)
      printf(" *** In  match \t expected: %s found: %s\n", tok2lex(t), get_lexeme());
   

   if (lookahead == t)
      lookahead = get_token();
   else
   {
      //printf("SYNTAX:   %s expected found\t%s\n", tok2lex(t),  get_lexeme());
      return 0; // 0 för den hittade inte 
   }
   return 1; // 1 för den hittade 
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
      printf("SYNTAX:   Type name expected found\t%s\n", get_lexeme());
      break;
   }
   outfunktion(__func__);
}
static void id_list()
{
   infunktion(__func__);
   
   if (lookahead == id)
   {
      if(!find_name(get_lexeme())){
         addv_name(get_lexeme());
      }
      else{
         printf("SEMANTIC: ID already declared:\t%s\n", get_lexeme());
      }
      match(id);
         

   }else{
      printf("SYNTAX:   Symbol expected ID found\t%s\n", get_lexeme());
   }
   

   if (lookahead == ',')
   {
      match(',');
      id_list();
   }else{
     // printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(','),  get_lexeme());
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
      match(';') ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(';'),  get_lexeme());
   }
   else{
     printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(':'),  get_lexeme());
     type();
     match(';')  ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(';'),  get_lexeme());
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
      find_name(get_lexeme()) ? 1 : printf("SEMANTIC: ID NOT declared: %s\n", get_lexeme());
      match(id);
      break;

   case number:
      match(number);
      break;

   default:
      printf("SYNTAX:   Operand Expected\n");
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
      if (lookahead == id)
      {
         if(!find_name(get_lexeme())){
            printf("SEMANTIC: ID NOT declared:\t%s\n", get_lexeme());
         }
               
         match(id);
      }else{
         printf("SYNTAX:   ID expected found\t%s\n", get_lexeme());
      }        
      match(assign)  ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(assign), get_lexeme());
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

   //infunktion("program");
   if (DEBUG)
      printf(" *** In  program_header\n");
   match(program)    ?  0 :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(program),  get_lexeme());


   if (lookahead == id)
   {
      addp_name(get_lexeme());
      match(id);
   }else{
      printf("SYNTAX:   expected ID found\t%s\n", get_lexeme());
      addp_name("???");
   }

   match('(')        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex('('),  get_lexeme());
   match(input)      ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(input),  get_lexeme());
   match(',')        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(','),  get_lexeme());
   match(output)     ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(output),  get_lexeme());
   match(')')        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(')'),  get_lexeme());
   match(';')        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(';'),  get_lexeme());
   outfunktion(__func__);
   if (DEBUG)
      printf("\n");
}

static void var_part()
{
   if (DEBUG)
      printf(" *** In  var_part\n");
   match(var)         ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(var),  get_lexeme());;
   var_dec_list();
   outfunktion(__func__);
   if (DEBUG)
      printf("\n");
}

static void stat_part()
{
   if (DEBUG)
      printf("\n *** In  stat_part\n");
   match(begin)      ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(begin),  get_lexeme());
   stat_list();
   match(end)        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex(end),  get_lexeme());
   match('.')        ?  1  :   printf("SYNTAX:   Symbol expected %s found\t%s\n", tok2lex('.'),  get_lexeme());
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
      printf(" *** In  parser\n");
   lookahead = get_token(); // get the first token

   if (lookahead != '$')
   {
      program_header();         // call the first grammar rule
      var_part();
      stat_part();
   }else{
      printf("SYNTAX:   Input file is empty\n");
   }
   

   if (lookahead != '$')
   {
      printf("SYNTAX:   Extra symbols after end of parse!\n          ");
      for (lookahead = lookahead; lookahead != '$' ; lookahead = get_token())
      {
         printf("%s ", get_lexeme());
      }
      printf("\n");
   }
   

   printf("________________________________________________________\n");

   p_symtab(); // skriver ut symbål tabelen 
   
   return 1; 
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
