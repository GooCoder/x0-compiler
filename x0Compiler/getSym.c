#include "global.h"

/*
 * 从输入文件中读取一个字符
 */
void getCh ()
{
	if (feof (fin)) // 文件已到末尾
	{
		return;
	}
	fscanf (fin, "%c", &ch);
}

/*
 * 词法分析，读取一个终结符
 */
void getSym ()
{
	int i, j, k;

	while (ch == ' ' || ch == 10 || ch == 9)	/* 过滤空格、换行和制表符 */
	{
		getCh ();
	}

	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))	/* 当前的单词是标识符或是保留字 */
	{
		char temp[MAX_SIZE_IDENT + 1];	/* temp保存着读取的标识符/保留字的名字 */
		k = 0;
		do 
		{
			if (k < MAX_SIZE_IDENT)
			{
				temp[k++] = ch;
			}
			else
			{
				printf ("标识符长度太长\n");
				exit (0);
			}
			getCh ();
		} while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));
		temp[k] = 0;

		strcpy (id, temp);	/* 将标识符/保留字的名字拷贝到id里面 */
		
		/* 搜索当前单词是否为保留字，使用二分法查找 */
		i = 0;
		j = RESERVE_WORD_NUM - 1;
		do
		{
			k = (i + j) / 2;
			if (strcmp (id, reserveWord[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp (id, reserveWord[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j);

		if (i - 1 > j)	/* 当前的单词是保留字 */
		{
			sym = wsym[k];
		}
		else  /* 当前的单词是标识符 */
		{
			sym = ident;
		}
	}
	else
	{
		if (ch >= '0' && ch <= '9')	/* 当前的单词是数字 */
		{
			k = 0;
			num = 0;
			sym = number;

			/* 获取数字的值 */
			do 
			{
				num = 10 * num + ch - '0';
				k++;
				if (k > MAX_SIZE_NUMBER)	/* 数字位数太多 */
				{
					printf ("数字位数太多\n");
					exit (0);
				}
				getCh ();
			} while (ch >= '0' && ch <= '9');
		}
		else
		{
			if (ch == '=')		/* 检测=或==符号 */
			{
				getCh ();
				if (ch == '=')
				{
					sym = eqleql;
					getCh ();
				}
				else
				{
					sym = eql;
				}
			}
			else
			{
				if (ch == '<')	/* 检测小于或小于等于符号 */
				{
					getCh ();
					if (ch == '=')
					{
						sym = lesseql;
						getCh ();
					}
					else
					{
						sym = less;
					}
				}
				else
				{
					if (ch == '>')	/* 检测大于或大于等于符号 */
					{
						getCh ();
						if (ch == '=')
						{
							sym = greateql;
							getCh ();
						}
						else
						{
							sym = great;
						}
					}
					else
					{
						if (ch == '!')	/* 检测不等于符号 */
						{
							getCh ();
							if (ch == '=')
							{
								sym = neql;
								getCh ();
							}
							else
							{
								sym = nul;	/* 不能识别的符号 */
							}
						}
						else
						{
							sym = ssym[ch];	/* 当符号不满足上述条件时，全部按照单字符符号处理 */
							getCh ();
						}
					}
				}
			}
		}
	}
}

#define DEBUG 0
#if DEBUG == 1

void test_getSym ()
{
	
	int i = 1;
	while (!feof(fin))
	{
		printf ("读取的第%d个终结符是: ", i++);
		getSym ();
		switch (sym)
		{
		case 0:
			printf ("nul");
		case 1:
			printf ("%s", id);
			break;
		case 2:
			printf ("main");
			break;
		case 3:
			printf ("char");
			break;
		case 4:
			printf ("int");
			break;
		case 5:
			printf ("if");
			break;
		case 6:
			printf ("else");
			break;
		case 7:
			printf ("while");
			break;
		case 8:
			printf ("read");
			break;
		case 9:
			printf ("write");
			break;
		case 10:
			printf ("+");
			break;
		case 11:
			printf ("-");
			break;
		case 12:
			printf ("*");
			break;
		case 13:
			printf ("/");
			break;
		case 14:
			printf ("(");
			break;
		case 15:
			printf (")");
			break;
		case 16:
			printf ("[");
			break;
		case 17:
			printf ("]");
			break;
		case 18:
			printf ("{");
			break;
		case 19:
			printf ("}");
			break;
		case 20:
			printf (";");
			break;
		case 21:
			printf ("=");
			break;
		case 22:
			printf (">");
			break;
		case 23:
			printf ("<");
			break;
		case 24:
			printf (">=");
			break;
		case 25:
			printf ("<=");
			break;
		case 26:
			printf ("==");
			break;
		case 27:
			printf ("!=");
			break;
		case 28:
			printf ("%d", num);
			break;
		}
		printf ("\n");
	}
}

#endif