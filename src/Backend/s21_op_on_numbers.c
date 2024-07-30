#include "s21_calculator.h"

// выполнить операции, указанные в строке polish_str, используя числа, которые
// хранятся в структуре stack_evaluation.
int s21_perform_operation_on_numbers(const char *polish_str, int i,
                                     struct stack_evaluation *stck_e) {
  int flag = ERROR_FLAG_OK;
  if (polish_str[i] == '+') {
    s21_push_to_evaluation_stack(stck_e,
                                 s21_pop_from_evaluation_stack(stck_e) +
                                     s21_pop_from_evaluation_stack(stck_e));
  }
  if (polish_str[i] == '*') {
    s21_push_to_evaluation_stack(stck_e,
                                 s21_pop_from_evaluation_stack(stck_e) *
                                     s21_pop_from_evaluation_stack(stck_e));
  }
  if (polish_str[i] == '-') {
    double subtrahend = s21_pop_from_evaluation_stack(stck_e);
    s21_push_to_evaluation_stack(
        stck_e, s21_pop_from_evaluation_stack(stck_e) - subtrahend);
  }
  if (polish_str[i] == '/') {
    double dividend = s21_pop_from_evaluation_stack(stck_e);
    if (dividend != 0) {
      s21_push_to_evaluation_stack(
          stck_e, s21_pop_from_evaluation_stack(stck_e) / dividend);
    } else {
      flag = ERROR_FLAG_BRUH;
    }
  }
  if (polish_str[i] == 's') {
    s21_push_to_evaluation_stack(stck_e,
                                 sin(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'n') {
    s21_push_to_evaluation_stack(stck_e,
                                 asin(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'c') {
    s21_push_to_evaluation_stack(stck_e,
                                 cos(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'o') {
    s21_push_to_evaluation_stack(stck_e,
                                 acos(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 't') {
    s21_push_to_evaluation_stack(stck_e,
                                 tan(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'a') {
    s21_push_to_evaluation_stack(stck_e,
                                 atan(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'm') {
    double dividend = s21_pop_from_evaluation_stack(stck_e);
    if (stck_e->top_index == 0) {
      flag = ERROR_FLAG_INCORRECT;
    } else {
      s21_push_to_evaluation_stack(
          stck_e, fmodl(s21_pop_from_evaluation_stack(stck_e), dividend));
    }
  }
  if (polish_str[i] == '^') {
    double powed = s21_pop_from_evaluation_stack(stck_e);
    if (stck_e->top_index == 0) {
      flag = ERROR_FLAG_INCORRECT;
    } else {
      s21_push_to_evaluation_stack(
          stck_e, pow(s21_pop_from_evaluation_stack(stck_e), powed));
    }
  }
  if (polish_str[i] == 'q') {
    s21_push_to_evaluation_stack(stck_e,
                                 sqrt(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'l') {
    s21_push_to_evaluation_stack(stck_e,
                                 log(s21_pop_from_evaluation_stack(stck_e)));
  }
  if (polish_str[i] == 'g') {
    s21_push_to_evaluation_stack(stck_e,
                                 log10(s21_pop_from_evaluation_stack(stck_e)));
  }
  return flag;
}