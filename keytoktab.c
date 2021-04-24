// AV Lukas Axelborn - 0003218773
/**********************************************************************/
/* lab 1 DVG C01 - Driver OBJECT                                      */
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
/**********************************************************************/
/* type definitions                                                   */
/**********************************************************************/
typedef struct tab
{
	char *text;
	int token;
} tab;

/**********************************************************************/
/* data objects (tables)                                              */
/**********************************************************************/
static tab tokentab[] = {
	{"id", id},
	{"number", number},
	{":=", assign},
	{"undef", undef},
	{"predef", predef},
	{"tempty", tempty},
	{"error", error},
	{"type", typ},
	{"$", '$'},
	{"(", '('},
	{")", ')'},
	{"*", '*'},
	{"+", '+'},
	{",", ','},
	{"-", '-'},
	{".", '.'},
	{"/", '/'},
	{":", ':'},
	{";", ';'},
	{"=", '='},
	{"TERROR", nfound}};

static tab keywordtab[] = {
	{"program", program},
	{"input", input},
	{"output", output},
	{"var", var},
	{"begin", begin},
	{"end", end},
	{"boolean", boolean},
	{"integer", integer},
	{"real", real},
	{"KERROR", nfound}};

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Display the tables                                                 */
/**********************************************************************/
void p_toktab()
{
	printf("________________________________________________________\n");
	printf("THE PROGRAM KEYWORDS\n");
	printf("________________________________________________________\n");

	for (int i = 0; keywordtab[i].token != nfound; i++)
	{
		printf("%10s %d\n", keywordtab[i].text, keywordtab[i].token);
	}

	printf("________________________________________________________\n");
	printf("THE PROGRAM TOKENS\n");
	printf("________________________________________________________\n");

	for (int i = 0; tokentab[i].token != nfound; i++)
	{
		printf("%10s %d\n", tokentab[i].text, tokentab[i].token);
	}
}

/**********************************************************************/
/* lex2tok - convert a lexeme to a token                              */
/**********************************************************************/
toktyp lex2tok(char *fplex)
{
	for (int i = 0; tokentab[i].token != nfound; i++)
	{
		if (strcmp(fplex, tokentab[i].text) == 0)
		{
			return tokentab[i].token;
		}
	}

	for (int i = 0; keywordtab[i].token != nfound; i++)
	{
		if (strcmp(fplex, keywordtab[i].text) == 0)
		{
			return keywordtab[i].token;
		}
	}

	if (isdigit(fplex[0]))
	{
		return number;
	}
	
	return 258; // om inget stoppar denna retur måste det vara ett id
}

/**********************************************************************/
/* key2tok - convert a keyword to a token                             */
/**********************************************************************/
toktyp key2tok(char *fplex)
{
	for (int i = 0; i <= 9; i++)
	{
		if (strcmp(fplex, keywordtab[i].text) == 0)
		{
			return keywordtab[i].token;
		}
	}
	return 258;
}

/**********************************************************************/
/* tok2lex - convert a token to a lexeme                              */
/**********************************************************************/
char *tok2lex(toktyp ftok)
{
	if (ftok < tend)
	{ 
		for (int i = 0; tokentab[i].token != nfound; i++)
		{
			if (tokentab[i].token == ftok)// i är för stort funderar på att ta bort if-satsen
			{
				return tokentab[i].text;
			}
		}
	}
	else
	{ 
		return keywordtab[ftok % (kstart + 1)].text;
	}
	return 0;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
