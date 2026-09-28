#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
struct stack
{
    int top;
    char data[SIZE];
};
typedef struct stack STACK;
void push(STACK *s, char ch)
{
    s->data[++s->top] = ch;
}
char pop(STACK *s)
{
    return s->data[s->top--];
}
int precedence(char ch)
{
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}
void infixToPrefix(char infix[])
{
    STACK s;
    int i, j = 0;
    char prefix[SIZE];
    s.top = -1;
    strrev(infix);
    for (i = 0; infix[i] != '\0'; i++)
    {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }
    for (i = 0; infix[i] != '\0'; i++)
    {
        if (isalnum(infix[i]))
        {
            prefix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(&s, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (s.top != -1 && s.data[s.top] != '(')
            {
                prefix[j++] = pop(&s);
            }
            pop(&s);
        }
        else
        {
            while (s.top != -1 &&
                   s.data[s.top] != '(' &&
                   precedence(s.data[s.top]) > precedence(infix[i]))
            {
                prefix[j++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (s.top != -1)
    {
        prefix[j++] = pop(&s);
    }
    prefix[j] = '\0';
    strrev(prefix);
    printf("Prefix expression: %s\n", prefix);
}
int main()
{
    char infix[SIZE];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPrefix(infix);
    return 0;
}