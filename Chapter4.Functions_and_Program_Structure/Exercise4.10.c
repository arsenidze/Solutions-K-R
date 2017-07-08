#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#include <math.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define FUNCTION 1
#define MAXLINE 1000

int getline(char s[], int lim);
int getop(char []);
void push(double);
double pop(void);

void printtop(void);
void duplicatetop(void);
void swaptop2(void);			/*Swap the top two elemnts*/
void clearstck(void);			/*Clear the stack*/

int isinteger(double n);

void applyfunction(const char[]);
/* reverse Polish calculator */

char line[MAXLINE];
int k = 0;

int main(void)
{
	int type;
  	double op1,op2;
  	char s[MAXLINE];
	int flag = 0;
	while(getline(line, MAXLINE) > 0)
	{
		k = 0;
		while((type = getop(s)) != '\0')
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
				case FUNCTION:
					applyfunction(s);
					break;
		      	case '\n':
		      		if(flag == 0)
		        		printf("\t%.8g\n", pop());
		        	flag = 0;
		        	break;
		        case '!':
		        	printtop();
		        	flag = 1;
		        	break;
		        case '@':
		        	swaptop2();
		        	flag = 1;
		        	break;
		        case '#':
		        	duplicatetop();
		        	flag = 1;
		        	break;
		        case '$':
		        	clearstck();
		        	flag = 1;
		        	break;
		      	default:
		        	printf("error: unknown command %s\n", s);
		        	break;
		    }
	  	}
  	}
	return 0;
}

void applyfunction(const char s[])
{
	double op2;
   
   if(     !strcmp(s, "sin"))
      push(sin(pop()));
   else if(!strcmp(s, "cos"))
      push(cos(pop()));
   else if(!strcmp(s, "exp"))
      push(exp(pop()));
   else if(!strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   else
      printf("%s is not a supported function.\n", s);
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

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	i = 0;
	while((s[i] = c = line[k++]) == ' ' || c == '\t')
    ;
	
	if(isalpha(c))
	{
		while(isalpha(s[++i] = c = line[k++]))
			;
		s[i] = '\0';
		if(c != EOF)
		{
			k--;
		}
		return FUNCTION;
	}
	
	if(!isdigit(c) && c != '.' && c != '-')
	{
		return c;
	}
	
	if(c == '-')
	{
		if(!isdigit(s[++i] = c = line[k++]) && c != '.')
		{
			k--;
			return '-';
		}
	}
	
	if(isdigit(c))
		while(isdigit(s[++i] = c = line[k++]))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = line[k++]))
			;
	
  	s[i] = '\0';
  	if(c != EOF)
    	k--;
  	return NUMBER;
}

int getline(char s[], int lim)
{
	int i = 0;
	int c;
	while(i < lim - 1 && (c = getchar()) != '\n' && c != EOF)
	{
		s[i++] = c;
	}
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	
	return i;	
}

