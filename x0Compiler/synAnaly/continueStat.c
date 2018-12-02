#include "../global.h"

/*
 * continueStat syntactical analyzer
 */
void continueStat ()
{
	if (sym == ctnsym)
	{
		getSym ();

		if (sym == semic)
		{
			getSym ();
			gen (jmp, 0, 0);
			continueList[iterCtnList++] = iterCode - 1;
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else /* the lack of 'continue' */
	{
		error (36);
	}
}