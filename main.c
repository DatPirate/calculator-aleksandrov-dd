#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
 
#define MAX_EXPR_LEN 1024
#define MAX_STACK_SIZE 512
 
typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;
 
void push(Stack *stack, double value) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->data[++stack->top] = value;
    }
}
 
double pop(Stack *stack) {
    return stack->top >= 0 ? stack->data[stack->top--] : 0;
}
 
double peek(Stack *stack) {
    return stack->top >= 0 ? stack->data[stack->top] : 0;
}
 
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}
 
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
 
void to_rpn(const char *expr, char *output) {
    Stack opStack = { .top = -1 };
    char temp[MAX_EXPR_LEN] = "";
    int j = 0;
 
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;
 
        if (isdigit(expr[i])) {
            while (isdigit(expr[i]) || expr[i] == '.') {
                temp[j++] = expr[i++];
            }
            temp[j++] = ' ';
            i--;
        } else if (expr[i] == '(') {
            push(&opStack, expr[i]);
        } else if (expr[i] == ')') {
            while (opStack.top >= 0 && peek(&opStack) != '(') {
                temp[j++] = (char) pop(&opStack);
                temp[j++] = ' ';
            }
            pop(&opStack);
        } else if (is_operator(expr[i])) {
            while (opStack.top >= 0 && precedence(peek(&opStack)) >= precedence(expr[i])) {
                temp[j++] = (char) pop(&opStack);
                temp[j++] = ' ';
            }
            push(&opStack, expr[i]);
        }
    }
 
    while (opStack.top >= 0) {
        temp[j++] = (char) pop(&opStack);
        temp[j++] = ' ';
    }
    temp[j] = '\0';
    strcpy(output, temp);
}
 
int evaluate_rpn(const char *rpn) {
    Stack numStack = { .top = -1 };
    char *token = strtok(strdup(rpn), " ");
 
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&numStack, atof(token));
        } else if (is_operator(token[0]) && strlen(token) == 1) {
            double b = pop(&numStack);
            double a = pop(&numStack);
            switch (token[0]) {
                case '+': push(&numStack, a + b); break;
                case '-': push(&numStack, a - b); break;
                case '*': push(&numStack, a * b); break;
                case '/': push(&numStack, a / b); break;
            }
        }
        token = strtok(NULL, " ");
    }
    return (int)pop(&numStack);
}
 
int main() {
    char expr[MAX_EXPR_LEN];
    char rpn[MAX_EXPR_LEN];
 
    fgets(expr, MAX_EXPR_LEN, stdin);
 
    to_rpn(expr, rpn);
    printf("%d", evaluate_rpn(rpn));
 
    return 0;
}
