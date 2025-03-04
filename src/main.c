#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_LEN 1024
#define MAX_STACK_SIZE 512

char * strdup(const char*);

typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack* stack, double value)
{
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->data[++stack->top] = value;
    }
}

double pop(Stack* stack)
{
    return stack->top >= 0 ? stack->data[stack->top--] : 0;
}

double peek(Stack* stack)
{
    return stack->top >= 0 ? stack->data[stack->top] : 0;
}

int precedence(char op)
{
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int validate_expression(const char* expr)
{
    int balance = 0;
    int last_was_operator = 1;
    int last_was_digit = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) {
            if (last_was_digit) {
                int j = i;
                while (isspace(expr[j])) {
                    j++;
                    if (expr[j] == '\0')
                        break;
                    if (isdigit(expr[j]))
                        return 0;
                }
            }
        } else if (expr[i] == '(') {
            balance++;
            last_was_operator = 1;
            last_was_digit = 0;
        } else if (expr[i] == ')') {
            balance--;
            if (balance < 0)
                return 0;
            last_was_operator = 0;
            last_was_digit = 0;
        } else if (is_operator(expr[i]) || (expr[i] == '\\' && (expr[i + 1] == '/' || expr[i + 1] == '-'))) {
            if (last_was_operator)
                return 0;
            last_was_operator = 1;
            last_was_digit = 0;
            if (expr[i] == '\\')
                i++;
        } else if (isdigit(expr[i])) {
            last_was_operator = 0;
            last_was_digit = 1;
        } else {
            return 0;
        }
    }
    return (balance == 0 && last_was_operator == 0);
}

void to_rpn(const char* expr, char* output)
{
    Stack opStack = { .top = -1 };
    char temp[MAX_EXPR_LEN] = "";
    int j = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i]))
            continue;

        if (isdigit(expr[i])) {
            while (isdigit(expr[i])) {
                temp[j++] = expr[i++];
            }
            temp[j++] = ' ';
            i--;
        } else if (expr[i] == '(') {
            push(&opStack, expr[i]);
        } else if (expr[i] == ')') {
            while (opStack.top >= 0 && peek(&opStack) != '(') {
                temp[j++] = (char)pop(&opStack);
                temp[j++] = ' ';
            }
            pop(&opStack);
        } else if (is_operator(expr[i]) || (expr[i] == '\\' && expr[i + 1] == '/')) {
            char op = (expr[i] == '\\') ? '/' : expr[i];
            if (expr[i] == '\\')
                i++;
            while (opStack.top >= 0 && precedence(peek(&opStack)) >= precedence(op)) {
                temp[j++] = (char)pop(&opStack);
                temp[j++] = ' ';
            }
            push(&opStack, op);
        }
    }
    while (opStack.top >= 0) {
        temp[j++] = (char)pop(&opStack);
        temp[j++] = ' ';
    }
    temp[j] = '\0';
    strcpy(output, temp);
}

double evaluate_rpn(const char* rpn, int is_float)
{
    Stack numStack = { .top = -1 };
    char* token = strtok(strdup(rpn), " ");

    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&numStack, atof(token));
        } else if (is_operator(token[0]) && strlen(token) == 1) {
            double b = pop(&numStack);
            double a = pop(&numStack);

            if (token[0] == '/' && fabs(b) < 1e-4) {
                fprintf(stderr, "Error: Division by zero or near-zero values is not allowed.\n");
                exit(EXIT_FAILURE);
            }
            switch (token[0]) {
            case '+':
                push(&numStack, a + b);
                break;
            case '-':
                push(&numStack, a - b);
                break;
            case '*':
                push(&numStack, a * b);
                break;
            case '/':
                push(&numStack, is_float ? (a / b) : trunc(a / b));
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    return pop(&numStack);
}

#ifndef GTEST
int main(int argc, char* argv[])
{
    int is_float = 0;
    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        is_float = 1;
    }

    char expr[MAX_EXPR_LEN];
    char rpn[MAX_EXPR_LEN];

    if (!fgets(expr, MAX_EXPR_LEN, stdin)) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    if (!validate_expression(expr)) {
        fprintf(stderr, "Error: Invalid expression syntax.\n");
        return EXIT_FAILURE;
    }

    to_rpn(expr, rpn);
    double result = evaluate_rpn(rpn, is_float);

    if (is_float) {
        printf("%.4f\n", result);
    } else {
        printf("%d\n", (int)result);
    }

    return 0;
}
#endif
