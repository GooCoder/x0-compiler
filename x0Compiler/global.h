#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 100        // 文件名最大长度
#define MAX_SIZE_IDENT    20         // 标识符最大长度
#define MAX_SIZE_NUMBER   9          // 数字最大位数
#define MAX_SIZE_LINE     100		 // 输入文件一行最大的字符数
#define MAX_SIZE_TABLE    100        // 符号表的最大大小
#define TERMINAL_SYM_NUM  30         // 终结符数目
#define RESERVE_WORD_NUM  8          // 保留字数目

// 终结符
enum symbol
{
	nul, ident, mainsym, charsym, intsym, ifsym,
	elsesym, whilesym, readsym, writesym, plus, minus,
	times, slash, lparen, rparen, lbracket, rbracket, 
	lbrace, rbrace, semic, eql, great, less,
	greateql, lesseql, eqleql, neql, number, hashsym
};

// 符号表存储的对象的种类
enum objectKind
{
	charVar, intVar, charArray, intArray
};

// 符号表存储的对象
struct tableObject
{
	char name[MAX_SIZE_IDENT + 1];
	enum objectKind kind;
};

extern struct tableObject table[MAX_SIZE_TABLE]; // 符号表
extern int iterTable;                            // 符号表的迭代器
extern char fileName[MAX_SIZE_FILENAME + 1];     // 文件名
extern FILE* fin;                                // 输入文件
extern enum symbol sym;                          // getSym读取出的终结符
extern char ch;                                  // getCh读取出的字符
extern int posCh;								 // getCh使用的计数器, 表示当前字符在行缓冲区中的位置
extern char lineCache[MAX_SIZE_LINE];            // getCh使用的行缓冲区
extern int chNum;								 // 行缓冲区使用的计数器, 表示当前行缓冲区有多少字符
extern int num;                                  // 当前数字
extern char id[MAX_SIZE_IDENT + 1];              // 当前标识符
extern char* reserveWord[RESERVE_WORD_NUM];      // 保留字
extern enum symbol wsym[RESERVE_WORD_NUM];       // 保留字对应的符号值
extern enum symbol ssym[256];                    // 单字符的符号值

/* 词法分析程序 */
void getSym ();

/* 
 * 语法分析程序
 * ps: 如果语法没问题，语法分析程序开始的时候sym应为当前模块的第一个符号，
 * 程序结束的时候sym应为当前模块结束后的下一个符号
 */
void declaration_list ();
void declaration_stat ();
void statement_list ();
void statement ();
void type ();
void if_stat ();
void while_stat ();
void read_stat ();
void write_stat ();
void compound_stat ();
void expression_stat ();
void var ();
void expression ();
void simple_expr ();
void term ();
void factor ();
void additive_expr ();
void enter (enum objectKind k);	    /* 在符号表中加入一项 */
int findPosition (char* identName);	/* 在符号表中查找并返回identName的位置 */
void error (int error_code);        /* 错误分析子程序,编译出现问题时调用 */
