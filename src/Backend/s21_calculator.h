#ifndef SRC_FRONTEND_BACKEND_S21_CALCULATOR_H_
#define SRC_FRONTEND_BACKEND_S21_CALCULATOR_H_
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 256
#define CHECK_FLAG_VALID 0
#define CHECK_FLAG_INVALID 1

#define ERROR_FLAG_OK 0
#define ERROR_FLAG_BRUH 1
#define ERROR_FLAG_INCORRECT 2

#define CORRECT 0
#define INCORRECT 1

int s21_checking_validity_string(const char *str);
void s21_validate_syntax_and_brackets(char *str, int *err);
void s21_check_symbol_rules(char *str, int *err);
void s21_find_symbol_in_array(char *array, char to_found, int *flag);
void s21_expression_and_function_validation(char *str, int *err);
void s21_skip_function_arguments(char symbol, char symbol_2, int *index);
void s21_check_operator_syntax(char *str, int *err);

struct stack {
  char *array;  // массив, использующийся для хранения символов. Тип данных char
                // * для того, чтобы динамически изменять размер массива.
  int top_index;  // индекс верхнего элемента. Принцип LIFO
};

struct stack_evaluation {
  double *array;  // массив, использующийся для хранения чисел.
  int top_index;
};

struct stack *create(int size);
struct stack_evaluation *create_evaluation(int size);

double s21_calculate_with_error(char *str, int *error_code, double x);

void s21_push_to_stack(struct stack *stck, char value);
void s21_push_to_evaluation_stack(struct stack_evaluation *stck_e,
                                  double value);
char s21_pop_from_stack(struct stack *stck);
double s21_pop_from_evaluation_stack(struct stack_evaluation *stck_e);
void s21_destroy_stack(struct stack *stck);
void s21_destroy_evaluation_stack(struct stack_evaluation *stck_e);
char s21_get_top_element(struct stack *stck);

void s21_transform_math_expression(char *input, char *output);
int s21_is_math_operator(char oper);
int s21_check_expression_validity(char *output);

int s21_get_operator_priority(char oper);
void s21_infix_to_postfix_conversion(char *valid_str, char *polish_str);

int s21_evaluate_expression_with_variable(const char *polish_str, double *res,
                                          double x);
int s21_perform_operation_on_numbers(const char *polish_str, int i,
                                     struct stack_evaluation *stck_e);

#endif  // SRC_FRONTEND_BACKEND_S21_CALCULATOR_H_