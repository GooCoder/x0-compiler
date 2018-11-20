#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 100        // 文件名最大长度
#define MAX_SIZE_IDENT    20         // 标识符最大长度
#define MAX_SIZE_NUMBER   9          // 数字最大位数
#define TERMINAL_SYM_NUM  29         // 终结符数目
#define RESERVE_WORD_NUM  8          // 保留字数目

// 终结符
enum symbol
{
	nul, ident, mainsym, charsym, intsym, ifsym,
	elsesym, whilesym, readsym, writesym, plus, minus,
	times, slash, lparen, rparen, lbracket, rbracket, 
	lbrace, rbrace, semic, eql, great, less,
	greateql, lesseql, eqleql, neql, number
};

extern char fileName[MAX_SIZE_FILENAME + 1];     // 文件名
extern FILE* fin;                                // 输入文件
extern enum symbol sym;                          // getSym读取出的终结符
extern char ch;                                  // getCh读取出的字符
extern int num;                                  // 当前数字
extern char id[MAX_SIZE_IDENT + 1];              // 当前标识符
extern char* reserveWord[RESERVE_WORD_NUM];      // 保留字
extern enum symbol wsym[RESERVE_WORD_NUM];       // 保留字对应的符号值
extern enum symbol ssym[256];                    // 单字符的符号值
