#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
struct Stack
{
    int top;
    char data[SIZE];
};
typedef struct Stack STACK
void push(STACK *s, char ch)
{
    s->data[++s->top] = ch;
}
char pop(STACK *s)
{
    return s->data[s->top--];
}
int main()
{
    STACK s;
    char infix[SIZE], prefix[SIZE];
    int i, j = 0;
    char ch;
    s.top = -1;
    printf("Enter infix expression: ");
    scanf("%s", infix);
    strrev(infix);
    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (isalnum(ch))
        {
            prefix[j++] = ch;
        }
        else if (ch == ')')
        {
            push(&s, ch);
        }
        else if (ch == '(')
        {
            while (s.top != -1 && s.stk[s.top] != ')')
                prefix[j++] = pop(&s);

            if (s.top != -1)
                pop(&s);
        }
        else
        {
            while (s.top != -1 &&
                   s.data[s.top] != ')' &&
                   ((ch != '^' && 
                     ((ch == '+' || ch == '-') &&
                      (s.data[s.top] == '*' || s.data[s.top] == '/')))
                    ||
                    ((ch == '*' || ch == '/') &&
                     s.data[s.top] == '^')))
            {
                prefix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }
    while (s.top != -1)
        prefix[j++] = pop(&s);
    prefix[j] = '\0';
    strrev(prefix);
    printf("Prefix expression: %s\n", prefix);
    return 0;
}
