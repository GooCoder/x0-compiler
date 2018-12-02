#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 100        /* max length of file name */
#define MAX_SIZE_IDENT    20         /* max length of identifier */
#define MAX_SIZE_NUMBER   9          /* max digits of number */
#define MAX_SIZE_LINE     100		 /* max number of a line's character in input file */
#define MAX_SIZE_TABLE    100        /* max size of symbol table */
#define MAX_SIZE_CODE     1000       /* max number of intermidiate code */
#define MAX_SIZE_STACK    10000      /* max size of data stack */
#define MAX_SIZE_BREAK    1000       /* max number of 'break' statement */
#define MAX_SIZE_CONTINUE 1000       /* max number of 'continue' statement */
#define FCTCODE_NUM       15         /* number of function code */
#define TERMINAL_SYM_NUM  54         /* number of terminal symbol */
#define RESERVE_WORD_NUM  24         /* number of reserved word */

/* terminal symbol */
enum symbol
{
	nul, ident, mainsym, charsym, intsym, ifsym,
	elsesym, whilesym, readsym, writesym, plus, minus,
	times, slash, lparen, rparen, lbracket, rbracket, 
	lbrace, rbrace, semic, eql, great, less,
	greateql, lesseql, eqleql, neql, intnum, hashsym,
	andsym, orsym, forsym, modsym, oddsym, xorsym,
	incsym, decsym, notsym, brksym, ctnsym, exitsym,
	swtcsym, cassym, colonsym, defausym, dosym, reptsym,
	untlsym, bolsym, truesym, falsesym, doublenum, dblsym
};

/* the kind of object stored in the symbol table */
enum objectKind
{
	charVar, intVar, boolVar,
	charArray, intArray, boolArray,
	doubleVar, doubleArray
};

/* object stored in the symbol table */
struct tableObject
{
	char name[MAX_SIZE_IDENT + 1];
	enum objectKind kind;
	int offset;	/* offset relative to current activity record */
	int size;	/* how much space needed to be distribute */
};

/* function code */
enum fctCode
{
	lit, opr, lod, sto, cal,
	ini, jmp, jpc, stf, lof,
	adf, add, mis, mif, tad
};

/* intermidiate code */
struct instruction
{
	enum fctCode fct; /* function code */
	int lev_dif;	  /* the level difference between reference-level and declare-level */
	double offset;	  /* 'lod' instruction: 'offset' is the offset relative to the base address of current activity record.
						 'cal' instruction: 'offset' is the position where called function starts in the intermidiate code. */
};

/* object stored in data stack */
struct stackObject
{
	int dataType; /* data-type, 1: int, 2: double, 3: char, 4: bool */
	int intData;
	double dblData;
};

extern int continueList[MAX_SIZE_CONTINUE];      /* continue statement to be backfilled */
extern int iterCtnList;                          /* the iterator of continueList */
extern int breakList[MAX_SIZE_BREAK];            /* break statement to be backfilled */
extern int iterBreakList;                        /* the iterator of breakList */
extern char* fctCode_string[FCTCODE_NUM];        /* strings corresponding to function code */
extern struct instruction code[MAX_SIZE_CODE];   /* intermidiate code */
extern int iterCode;                             /* the iterator of code */
extern struct tableObject table[MAX_SIZE_TABLE]; /* symbol table */
extern int iterTable;                            /* the iterator of table */
extern char fileName[MAX_SIZE_FILENAME + 1];     /* file name */
extern FILE* fin;                                /* input file */
extern enum symbol sym;                          /* current terminal symbol read by getSym() */
extern char ch;                                  /* current character read by getCh() */
extern int posCh;								 /* counter using by getCh() */
extern char lineCache[MAX_SIZE_LINE];            /* line cache using by getCh() */
extern int chNum;								 /* counter using by line cache */
extern double floatNum;                          /* current floating number */
extern int intNum;                               /* current number */
extern char id[MAX_SIZE_IDENT + 1];              /* current identifier */
extern enum symbol wsym[RESERVE_WORD_NUM];       /* symbol-value corresponding to reserved word */
extern enum symbol ssym[256];                    /* symbol-value of single character */
extern char* reserveWord[RESERVE_WORD_NUM];      /* reserved word */

/* lexical analyzer */
void getSym ();

/* 
 * syntactical analyzer
 * tip: if no error occurs, sym should be the first symbol when a syntactical analyzer starts, and
 * sym should be the following symbol at the end of analysing.
 */
void declarationList (int* ptr_offset);
void declarationStat (int* ptr_offset);
void statementList ();
void statement ();
void type ();
void ifStat ();
void whileStat ();
void readStat ();
void writeStat ();
void compoundStat ();
void expressionStat ();
void variable (int* ptr_offset, int* ptr_isArray, int* ptr_IncOrDec, int* ptr_identType);
void simpleVariable (int* ptr_offset, int* ptr_isArray, int* ptr_identType);
void expression ();
void simpleValue ();
void term ();
void factor ();
void additiveExpr ();
void forStat ();
void valueExpr ();
void breakStat ();
void exitStat ();
void continueStat ();
void switchStat ();
void dowhileStat ();
void repeatStat ();
void enter (enum objectKind k, int offset, int size);		/* add a new entry to symbol table */
int findPosition (char* identName);							/* search the position of an identifier in symbol table */
void error (int error_code);								/* error handler */
void gen (enum fctCode fct, int lev_dif, double offset);    /* generate an intermidiate code */

/* interpret and execute intermidiate code */
void Interpret();