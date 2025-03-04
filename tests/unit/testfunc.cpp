#include <ctype.h>
#include <gtest/gtest.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {

#define MAX_EXPR_LEN 1024
#define MAX_STACK_SIZE 512

char* strdup(const char*);

typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack* stack, double value);
double pop(Stack* stack);
double peek(Stack* stack);
int precedence(char op);
int is_operator(char c);
int validate_expression(const char* expr);
void to_rpn(const char* expr, char* output);
double evaluate_rpn(const char* rpn, int is_float);
}

TEST(CalculatorTest, StackPush)
{
    Stack nstack;
    nstack.top = -1;
    double val = 23.0;
    push(&nstack, val);
    EXPECT_FLOAT_EQ(nstack.data[nstack.top], val);
}

TEST(CalculatorTest, StackPop)
{
    Stack nstack;
    nstack.top = -1;
    double val1 = 23.0;
    double val2 = 32.0;
    push(&nstack, val1);
    push(&nstack, val2);
    EXPECT_FLOAT_EQ(pop(&nstack), val2);
    EXPECT_FLOAT_EQ(pop(&nstack), val1);
}

TEST(CalculatorTest, StackPeek)
{
    Stack nstack;
    nstack.top = -1;
    double val1 = 23.0;
    double val2 = 32.0;
    push(&nstack, val1);
    push(&nstack, val2);
    pop(&nstack);
    EXPECT_FLOAT_EQ(peek(&nstack), val1);
}

TEST(CalculatorTest, GetPrecedence)
{
    EXPECT_EQ(precedence('+'), 1);
    EXPECT_EQ(precedence('-'), 1);
    EXPECT_EQ(precedence('*'), 2);
    EXPECT_EQ(precedence('/'), 2);
    EXPECT_EQ(precedence('a'), 0);
}

TEST(CalculatorTest, OperatorCheck)
{
    EXPECT_EQ(is_operator('+'), 1);
    EXPECT_EQ(is_operator('-'), 1);
    EXPECT_EQ(is_operator('*'), 1);
    EXPECT_EQ(is_operator('/'), 1);
    EXPECT_EQ(is_operator('1'), 0);
    EXPECT_EQ(is_operator(' '), 0);
}

TEST(CalculatorTest, ValidateExpression)
{
    EXPECT_EQ(validate_expression("1"), 1);
    EXPECT_EQ(validate_expression("1+2"), 1);
    EXPECT_EQ(validate_expression("1 2"), 0);
    EXPECT_EQ(validate_expression("1 + 2"), 1);
    EXPECT_EQ(validate_expression("1 +"), 0);
    EXPECT_EQ(validate_expression("+ 2"), 0);
    EXPECT_EQ(validate_expression("12"), 1);
    EXPECT_EQ(validate_expression("(1 + 2)"), 1);
    EXPECT_EQ(validate_expression("(1 + 2"), 0);
    EXPECT_EQ(validate_expression("(    (  1     )+   ( 2   ))"), 1);
}

TEST(CalculatorTest, RpnConvert)
{
    char result[1024];
    to_rpn("1", result);
    EXPECT_EQ(result, result);
}

TEST(CalculatorTest, EvaluateRpn)
{
    EXPECT_FLOAT_EQ(evaluate_rpn("2 2 2 * +\0", 1), 6.0);
    EXPECT_FLOAT_EQ(evaluate_rpn("2 2 + 2 *\0", 1), 8.0);
}
