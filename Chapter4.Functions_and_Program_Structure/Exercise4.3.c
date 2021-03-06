#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

int isinteger(double n);

/* reverse Polish calculator */

int main(void)
{
  int type;
  double op1,op2;
  char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type)
	    {
	    	case NUMBER:
	        	push(atof(s));
	        	break;
	      	case '+':
	        	push(pop() + pop());
	        	break;
	      	case '*':
	        	push(pop() * pop());
		        break;
	 	    case '-':
	        	op2 = pop();
	        	push(pop() - op2);
	        	break;
	      	case '/':
	        	op2 = pop();
	        	if(op2 != 0.0)
	        		push(pop() / op2);
	        	else
	          		printf("error: zero divisor\n");
	        	break;
			case '%':
				op2 = pop();
				if(op2 == 0.0)
				{
					printf("error: division by zero\n");
				}
				else if(isinteger(op1 = pop()) && isinteger(op2))
				{
					push((int)op1 % (int)op2);
				}
				else
				{
					printf("error: binary opertaion %% only for integers\n");
				}
				break;
	      	case '\n':
	        	printf("\t%.8g\n", pop());
	        	break;
	      	default:
	        	printf("error: unknown command %s\n", s);
	        	break;
	    }
  }

  return 0;
}

int isinteger(double n)
{
	return (int)n == n;
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if(sp > 0)
    return val[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	i = 0;
	while((s[i] = c = getch()) == ' ' || c == '\t')			/* skip spaces/tabs */
    ;
	
	if(!isdigit(c) && c != '.' && c != '-')					/* retrun c if c letter expect '-' or '.' */
	{
		return c;
	}
	
	if(c == '-')
	{
		if(!isdigit(s[++i] = c = getch()) && c != '.')		/* if not digit or '.' after '-' */
		{
			ungetch(c);
			return '-';
		}
	}
	
  	if(isdigit(c)) /* collect integer part */
    	while(isdigit(s[++i] = c = getch()))
      	;
  	if(c == '.')
    	while(isdigit(s[++i] = c = getch()))
      	;
  	s[i] = '\0';
  	if(c != EOF)
    	ungetch(c);
  	return NUMBER;
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

