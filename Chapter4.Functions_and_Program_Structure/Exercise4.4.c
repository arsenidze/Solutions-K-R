#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

void printtop(void);
void duplicatetop(void);
void swaptop2(void);			/*Swap the top two elemnts*/
void clearstck(void);			/*Clear the stack*/

int isinteger(double n);

/* reverse Polish calculator */

int main(void)
{
	int type;
  	double op1,op2;
  	char s[MAXOP];
	
	int flag = 0;

	while((type = getop(s)) != EOF)
	{
		switch(type)
	    {
	    	case NUMBER:
	        	push(atof(s));
	        	flag = 0;
	        	break;
	      	case '+':
	        	push(pop() + pop());
	        	flag = 0;
	        	break;
	      	case '*':
	        	push(pop() * pop());
	        	flag = 0;
		        break;
	 	    case '-':
	        	op2 = pop();
	        	push(pop() - op2);
	        	flag = 0;
	        	break;
	      	case '/':
	        	op2 = pop();
	        	if(op2 != 0.0)
	        		push(pop() / op2);
	        	else
	          		printf("error: zero divisor\n");
	          	flag = 0;
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
				flag = 0;
				break;
	      	case '\n':
	      		if(flag == 0)
	        		printf("\t%.8g\n", pop());
	        	flag = 0;
	        	break;
	        case 'p':
	        	printtop();
	        	flag = 1;
	        	break;
	        case 's':
	        	swaptop2();
	        	flag = 1;
	        	break;
	        case 'd':
	        	duplicatetop();
	        	flag = 1;
	        	break;
	        case 'c':
	        	clearstck();
	        	flag = 1;
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

void printtop(void)
{
	if(sp != 0)
	{
		printf("[top] = %g\n", val[sp - 1]);
	//	for(int i = 0; i < sp; i++)
	//		printf("->%g",val[i]);
	}
}

void duplicatetop(void)
{
	if(sp == 0)
	;
	else if(sp < MAXVAL)
	{
		val[sp] = val[sp - 1];
		sp++;
	}
	else
		printf("error: stack full, can't duplicate top %g\n", val[sp - 1]);
}

void swaptop2(void)
{
	if(sp < 2)
	;
	else
	{
		double temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	}
}

void clearstck(void)
{
	if(sp == 0)
	;
	else
	{
		for(; sp > 0; sp--)
			val[sp - 1] = 0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while((s[0] = c = getch()) == ' ' || c == '\t')
    ;
	
	if(!isdigit(c) && c != '.') 
  	{
  		s[1] = '\0';
		return c; /* not a number */
	}
  	i = 0;
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

