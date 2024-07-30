#include "s21_calculator.h"

int s21_checking_validity_string(const char *str) {
  int f_result = CORRECT;
  s21_validate_syntax_and_brackets((char *)str, &f_result);
  if (!f_result) {
    s21_check_symbol_rules((char *)str, &f_result);
  }
  if (!f_result) {
    s21_expression_and_function_validation((char *)str, &f_result);
  }
  if (!f_result) {
    s21_check_operator_syntax((char *)str, &f_result);
  }
  return f_result;
}

//выполняет проверку скобок и символов, окружающих их, и может обнаруживать
//ошибки в этом контексте.
void s21_check_symbol_rules(char *str, int *err) {
  int len = strlen(str);
  int flag, index = 0;
  char symbol;
  char before_staple[10] = "+-*/^nstg";
  char after_staple[7] = "+-*/^)";
  char indoor_staple[12] = "0123456789x";
  while (index < len && *err == CORRECT) {
    symbol = str[index];
    if (symbol == '(') {
      if (str[index + 1] == ')') {
        *err = INCORRECT;
      } else if (str[index + 2] == ')') {
        s21_find_symbol_in_array(indoor_staple, str[index + 1], &flag);
        if (flag == 0) *err = INCORRECT;
      }
      if (index != 0 && str[index - 1] != 'd') {
        s21_find_symbol_in_array(before_staple, str[index - 1], &flag);
        if (flag == 0) *err = INCORRECT;
      }
    } else if (symbol == ')' && *err == CORRECT && str[index + 1] != 'm') {
      if (index != 0) {
        s21_find_symbol_in_array(after_staple, str[index + 1], &flag);
        if (flag == 0) *err = INCORRECT;
      }
    }
    if (*err == CORRECT) index++;
  }
}

void s21_check_operator_syntax(char *str, int *err) {
  char after_operators[18] =
      "(0123456789csatlx";  // Допустимые символы после операторов
  char operators[6] = "+-*/^";  // Операторы
  char before_operators[13] =
      ")0123456789x";  // Допустимые символы перед операторами
  int len = strlen(str);
  int index = 0;
  int flag;
  while (index < len && *err == CORRECT) {  // Пока не достигнут конец строки и
                                            // результат проверки корректен
    s21_find_symbol_in_array(operators, str[index], &flag);
    if (flag == 1) {
      if (index + 1 < len) {
        s21_find_symbol_in_array(after_operators, str[index + 1], &flag);
        if (flag == 0) {
          *err = INCORRECT;
          printf("AFTER\n");
        }
      }
      if (index != 0 && *err == CORRECT) {
        s21_find_symbol_in_array(before_operators, str[index - 1], &flag);
        if (flag == 0) {
          *err = INCORRECT;
          printf("%c, BEFORE\n", str[index]);
          if ((str[index] == '-' || str[index] == '+') &&
              str[index - 1] == '(') {
            *err = CORRECT;
            printf("BEFORE, str = %c, before = %c\n", str[index],
                   str[index - 1]);
            index++;
          }
        } else {
          index++;
        }
      } else if (index == 0) {
        index++;
      }
    } else {
      index++;
    }
  }
}

// Функция для проверки, является ли переданный символ оператором.
int s21_is_math_operator(char oper) {
  int flag = 0;
  switch (oper) {
    case 's':
    case 'n':
    case 'o':
    case 't':
    case 'a':
    case 'q':
    case 'l':
    case 'g':
    case 'c':
      flag = 1;  // Устанавливаем флаг в 1, если символ является оператором.
      break;
  }
  return flag;
}

// Функция для проверки валидности строки, содержащей операторы, цифры и
// переменную 'x'.
int s21_check_expression_validity(char *output) {
  int flag = CHECK_FLAG_INVALID;
  int i = 0;
  while (output[i]) {
    if (output[0] == ')') {
      flag = CHECK_FLAG_INVALID;
    }
    if (isdigit(output[i]) || output[i] == 'x') {
      flag = CHECK_FLAG_VALID;
    }
    if ((s21_is_math_operator(output[i]) == 1) && output[i + 1] == '(' &&
        (output[i + 2] == '\0' || output[i + 2] == ')')) {
      flag = CHECK_FLAG_INVALID;
    }
    i++;
  }
  return flag;
}
