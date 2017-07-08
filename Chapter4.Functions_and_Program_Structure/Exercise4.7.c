#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#include <string.h>

#define MAXOP 100 /* max size of operand or operator */

int getch(void);
void ungetch(int c);
void ungets(const char s[]);

int main(void)
{
	int c;
	char s[MAXOP] = "abrikosi";
	ungets(s);
	while((c = getch()) != '\0')
	{
		putchar(c);	
	}
  	return 0;
}

void ungets(const char s[])
{
	for(int i = 0; i < strlen(s) + 1; i++)
	{
		ungetch(s[strlen(s) - i]);
	}
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

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

