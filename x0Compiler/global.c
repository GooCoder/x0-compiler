#include "global.h"

char fileName[MAX_SIZE_FILENAME + 1];     // 文件名
FILE* fin;                                // 输入文件
enum symbol sym;                          // getSym读取出的终结符
char ch = ' ';                            // getCh读取出的字符
int num;                                  // 当前数字
char id[MAX_SIZE_IDENT + 1];              // 当前标识符

// 保留字
char* reserveWord[RESERVE_WORD_NUM] = {"char", "else", "if",
									   "int", "main", "read",
									   "while", "write"};
// 保留字对应的符号值
enum symbol wsym[RESERVE_WORD_NUM] = {charsym, elsesym, ifsym,
									  intsym, mainsym, readsym,
									  whilesym, writesym};
// 单字符的符号值
enum symbol ssym[256] = {['+'] = plus, ['-'] = minus, ['*'] = times,
						 ['/'] = slash, ['('] = lparen, [')'] = rparen,
						 ['['] = lbracket, [']'] = rbracket, ['{'] = lbrace,
						 ['}'] = rbrace, [';'] = semic};