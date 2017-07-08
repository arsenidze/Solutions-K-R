#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */

int getch(void);
void ungetch(int c);
int getch1(void);
void ungetch1(int c);

int main(void)
{
	int c;
	char s[MAXOP];
	int i = 0;
	c = getch1();
	ungetch1(EOF);
	ungetch1('t');
	putchar(getch1());
	putchar(getch1());

  	return 0;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int buff = -2;

int getch1(void) /* get a (possibly pushed back) character */
{
	if(buff == -2)
	{
		return getchar();
	}
	else 
	{
		int temp;
		temp = buff;
		buff = -2;
		return temp;
	}
}

void ungetch1(int c) /* push character back on input */
{
	if(buff != -2)
		printf("ungetch: too many characters\n");	
	else
		buff = c;
}

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

