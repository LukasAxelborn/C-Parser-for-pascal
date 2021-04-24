// AV Lukas Axelborn - 0003218773

/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/

#define BUFSIZE 1024
#define LEXSIZE 30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int pbuf = 0; /* current index program buffer  */
static int plex = 0; /* current index lexeme  buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog()
{
   memset (lexbuf, '\0', sizeof(lexbuf));

   int c, index;
   for (index = 0; ((c = getchar()) != EOF) && (index < BUFSIZE); index++)
   {
      if (c != '.')
      {
         buffer[index] = c;
      }
      else
      {
         buffer[index] = c;

         if (index + 3 < BUFSIZE)
         {
            buffer[index + 1] = '\n';
            buffer[index + 2] = '$';
			buffer[index + 3] = '\0';

         }
         break;
      }
   }
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/

static void pbuffer()
{
   printf("________________________________________________________\n");
   printf(" THE PROGRAM TEXT\n");
   printf("________________________________________________________\n");

   fwrite(buffer, strlen(buffer), 1, stdout);
		   
   printf("\n________________________________________________________\n");
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{
	memset (lexbuf, '\0', sizeof(lexbuf));
	plex = 0;
	int goback = 0;
	for(int i = 0; i < LEXSIZE; i++){

		if(goback){
			i=0;
			goback = 0;
		}

		if(isalnum(buffer[pbuf])){

			lexbuf[i] = buffer[pbuf];
			pbuf++;
			plex++;
			
		}
		else if(ispunct(buffer[pbuf]) && (plex == 0)){
			lexbuf[i] = buffer[pbuf];
			pbuf++;
			if(buffer[pbuf] == '='){
				lexbuf[i+1] = buffer[pbuf];
				pbuf++;
			}
			break;
		}
		else if(ispunct(buffer[pbuf]) &&(plex > 0)){
			break;
		}
		else if(isspace(buffer[pbuf]) && (i == 0)){
			/*while(isspace(buffer[pbuf])){
				pbuf++;

			}*/
			//go back to i=0
			pbuf++; // om en katarstråf händer gå till backa till while loopen			
			goback = 1;
		}
		else{
			pbuf++;
			break;
		} 
	}
}
/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token()
{
   if (pbuf == 0)
   {
      get_prog();
      pbuffer();
   }

   get_char();
   return lex2tok(lexbuf);
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char *get_lexeme()
{
   return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
