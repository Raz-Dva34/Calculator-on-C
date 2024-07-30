#include "s21_calculator.h"

void s21_validate_syntax_and_brackets(char *str, int *err) {
  int len = strlen(str);
  int index = 0;
  int op_staples = 0, cl_staples = 0;
  int def_symbol = 0;
  char undef_sym[33] = "0123456789*+-/()^cosintaqrlgmdx.";
  char supp[7] = "+-*/^.";
  int old_s, new_s, flag;
  s21_find_symbol_in_array(supp, str[index], &old_s);
  while (index < len && *err == CORRECT) {
    def_symbol = 0, new_s = 0;
    if (index == 0 && str[index] != '-' && str[index] != '+') {
      s21_find_symbol_in_array(supp, str[index], &flag);
      if (flag == 1) *err = INCORRECT;
    }
    s21_find_symbol_in_array(undef_sym, str[index], &def_symbol);
    s21_find_symbol_in_array(supp, str[index + 1], &new_s);
    if (def_symbol != 1) {
      *err = INCORRECT;
    } else if (new_s * old_s == 1) {
      *err = INCORRECT;
    } else {
      old_s = new_s;
    }
    if (*err == CORRECT) {
      if (str[index] == '(') op_staples++;
      if (str[index] == ')') cl_staples++;
    }
    index++;
  }
  if (*err == CORRECT) {
    *err = (op_staples == cl_staples) ? CORRECT : INCORRECT;
  }
}

void s21_find_symbol_in_array(char *array, char to_found, int *flag) {
  char *ptr = strchr(array, to_found);  // Поиск символа в массиве
  if (ptr != NULL) {
    *flag = 1;
    ptr = NULL;
  } else {
    *flag = 0;
  }
}

void s21_expression_and_function_validation(char *str, int *err) {
  int len = strlen(str);  // Получаем длину строки
  char supp[7] = "+-*/^(";  // Допустимые символы перед функцией
  char after[13] = "(0123456789x";  // Допустимые символы после функции
  char before[13] =
      ")0123456789x";  // Допустимые символы перед закрывающей скобкой
  char expres_s[13] = "cosintlgqram";  // Символы, представляющие функции
  int flag;
  int index = 0;
  char symbol, symbol_2;
  while (index < len && *err == CORRECT) {  // Пока не достигнут конец строки и
                                            // результат проверки корректен
    symbol = str[index];
    symbol_2 = str[index + 1];
    s21_find_symbol_in_array(
        expres_s, symbol,
        &flag);  // Проверяем, является ли текущий символ функцией
    if (flag == 1) {
      if (index == 0 && str[index] == 'm') *err = INCORRECT;
      if (index != 0) {
        if (str[index] == 'm') {
          s21_find_symbol_in_array(before, str[index - 1], &flag);
          if (flag == 1) {
            if (index + 1 < len) {
              s21_find_symbol_in_array(after, str[index + 3], &flag);
            }
            if (flag == 0) {
              *err = INCORRECT;
            } else {
              s21_skip_function_arguments(symbol, symbol_2, &index);
            }
          } else {
            *err = INCORRECT;
          }
        } else {
          s21_find_symbol_in_array(supp, str[index - 1], &flag);
          if (flag == 0) {
            *err = INCORRECT;
          } else {
            s21_skip_function_arguments(symbol, symbol_2, &index);
          }
        }
      } else {
        s21_skip_function_arguments(symbol, symbol_2, &index);
      }
    } else {
      index++;
    }
  }
}

// Функция используется для увеличения значения индекса *index,
void s21_skip_function_arguments(char symbol, char symbol_2, int *index) {
  if (symbol == 'c' || symbol == 't' || (symbol == 'l' && symbol_2 == 'o') ||
      (symbol == 's' && symbol_2 == 'i'))
    *index += 4;
  else if (symbol == 'a' || (symbol == 's' && symbol_2 == 'q'))
    *index += 5;
  else if (symbol == 'l' && symbol_2 == 'o')
    *index += 3;
  else if (symbol == 'l' && symbol_2 == 'n')
    *index += 2;
  else if (symbol == 'm')
    *index += 3;
  else
    *index += 1;
}

// Функция для помещения символа в стек.
void s21_push_to_stack(struct stack *stck, char value) {
  stck->array[stck->top_index] = value;
  stck->top_index++;
}

// Функция для помещения числа с плавающей запятой (double) в структуру стека
// вычислений.
void s21_push_to_evaluation_stack(struct stack_evaluation *stck_e,
                                  double value) {
  stck_e->array[stck_e->top_index] = value;
  stck_e->top_index++;
}

// Функция для извлечения символа из структуры стека символов.
char s21_pop_from_stack(struct stack *stck) {
  char value = '0';
  if (stck->top_index != 0) {
    value = stck->array[stck->top_index - 1];
    stck->top_index--;
  }
  return value;
}

// Функция для извлечения числа из структуры стека чисел (для вычислений).
double s21_pop_from_evaluation_stack(struct stack_evaluation *stck_e) {
  double value = 0.0;
  if (stck_e->top_index != 0) {
    value = stck_e->array[stck_e->top_index - 1];
    stck_e->top_index--;
  }
  return value;
}

// Функция для удаления структуры стека и освобождения памяти.
void s21_destroy_stack(struct stack *stck) {
  if (stck != NULL) {
    if (stck->array != NULL) {
      free(stck->array);
      stck->top_index = 0;
    }
    free(stck);
  }
}

// Функция для удаления структуры стека оценки и освобождения памяти.
void s21_destroy_evaluation_stack(struct stack_evaluation *stck_e) {
  if (stck_e != NULL) {
    if (stck_e->array != NULL) {
      free(stck_e->array);
      stck_e->top_index = 0;
    }
    free(stck_e);
  }
}

// Функция для получения значения элемента на вершине стека без его извлечения.
char s21_get_top_element(struct stack *stck) {
  char flag = '0';
  if (stck->top_index != 0) {
    flag = stck->array[stck->top_index - 1];
  }
  return flag;
}

// Функция для определения приоритета операторов и символов в выражении.
int s21_get_operator_priority(char oper) {
  int priora = 1;
  if (isdigit(oper) || oper == 46) priora = 0;
  // Скобки имеют приоритет 1.
  if (oper == '(' || oper == ')') priora = 1;
  // Сложение и вычитание имеют приоритет 2.
  if (oper == '+' || oper == '-') priora = 2;
  // Умножение, деление и mod имеют приоритет 3.
  if (oper == '*' || oper == '/' || oper == 'm') priora = 3;
  // Функции и операции (cos, sin, tan, log, sqrt и т.д.) имеют приоритет 4.
  if (s21_is_math_operator(oper) || oper == '^') priora = 4;
  return priora;
}

// Функция для преобразования инфиксного выражения в обратную польскую запись
// (ОПН).
void s21_infix_to_postfix_conversion(char *valid_str, char *polish_str) {
  struct stack *stck = create(NMAX);  // Создаем стек для операторов.
  int k = 0;  // Индекс для записи символов в polish_str.
  int i = 0;  // Индекс для чтения символов из valid_str.
  while (valid_str[i] != '\0') {
    if (s21_get_operator_priority(valid_str[i]) == 0) {
      polish_str[k++] = valid_str[i];
      if (s21_get_operator_priority(valid_str[i + 1]) != 0) {
        polish_str[k++] = ' ';
      }
    } else if (valid_str[i] == '(') {
      s21_push_to_stack(stck, valid_str[i]);
    } else if (valid_str[i] == ')') {
      while (s21_get_top_element(stck) != '(') {
        polish_str[k++] = s21_pop_from_stack(stck);
      }
      s21_pop_from_stack(stck);
    } else if (valid_str[i] == 'x') {
      polish_str[k++] = valid_str[i];
    } else if ((s21_get_operator_priority(valid_str[i]) >= 2) &&
               (s21_get_operator_priority(valid_str[i]) <= 4)) {
      if (s21_get_operator_priority(s21_get_top_element(stck)) >=
          s21_get_operator_priority(valid_str[i])) {
        while (s21_get_operator_priority(s21_get_top_element(stck)) >=
               s21_get_operator_priority(valid_str[i])) {
          polish_str[k++] = s21_pop_from_stack(stck);
        }
        s21_push_to_stack(stck, valid_str[i]);
      } else if (s21_get_operator_priority(s21_get_top_element(stck)) <
                 s21_get_operator_priority(valid_str[i])) {
        s21_push_to_stack(stck,
                          valid_str[i]);  // Помещаем текущий оператор в стек.
      }
    }
    i++;
  }
  while (stck->top_index != 0) {
    polish_str[k++] = s21_pop_from_stack(stck);
  }
  s21_destroy_stack(stck);
}

// Функция для создания и инициализации структуры стека.
struct stack *create(int size) {
  struct stack *stck =
      malloc(sizeof(struct stack));  // Выделяем память под структуру стека.
  if (stck) {  // Проверяем, удалось ли выделить память для структуры.
    stck->array = malloc(
        size * sizeof(char));  // Выделяем память под массив элементов стека.
    if (stck->array) {
      stck->top_index = 0;
    } else {
      free(stck);
      stck = NULL;
    }
  }
  return stck;
}

// Функция для создания и инициализации структуры стека вычислений.
struct stack_evaluation *create_evaluation(int size) {
  struct stack_evaluation *stck_e = malloc(sizeof(struct stack_evaluation));
  if (stck_e) {
    stck_e->array = malloc(size * sizeof(double));
    if (stck_e->array) {
      stck_e->top_index = 0;
    } else {
      free(stck_e);
      stck_e = NULL;
    }
  }
  return stck_e;
}

// Функция для вычисления результата математического выражения.
double s21_calculate_with_error(char *str, int *error_code, double x) {
  char valid_str[NMAX] = {0};
  s21_transform_math_expression(str, valid_str);
  double res = 0.0;
  *error_code = s21_check_expression_validity(valid_str);
  if (*error_code == 0) {
    char polish_str[NMAX] = {0};
    s21_infix_to_postfix_conversion(valid_str, polish_str);
    *error_code = s21_evaluate_expression_with_variable(polish_str, &res, x);
  }
  return res;
}

// Функция для валидации и преобразования входной строки с математическим
// выражением.
void s21_transform_math_expression(char *input, char *output) {
  int k = 0;
  for (int i = 0; i < (int)strlen(input); i++) {
    if (strncmp(&input[i], "sin", 3) == 0) {
      output[k++] = 's';  // Заменяем "sin" на "s".
      i += 2;
    } else if (strncmp(&input[i], "asin", 4) == 0) {
      output[k++] = 'n';  // Заменяем "asin" на "n".
      i += 3;
    } else if (strncmp(&input[i], "cos", 3) == 0) {
      output[k++] = 'c';  // Заменяем "cos" на "c".
      i += 2;
    } else if (strncmp(&input[i], "acos", 4) == 0) {
      output[k++] = 'o';  // Заменяем "acos" на "o".
      i += 3;
    } else if (strncmp(&input[i], "tan", 3) == 0) {
      output[k++] = 't';  // Заменяем "tan" на "t".
      i += 2;
    } else if (strncmp(&input[i], "atan", 4) == 0) {
      output[k++] = 'a';  // Заменяем "atan" на "a".
      i += 3;
    } else if (strncmp(&input[i], "mod", 3) == 0) {
      output[k++] = 'm';  // Заменяем "mod" на "m".
      i += 2;
    } else if (strncmp(&input[i], "sqrt", 4) == 0) {
      output[k++] = 'q';  // Заменяем "sqrt" на "q".
      i += 3;
    } else if (strncmp(&input[i], "ln", 2) == 0) {
      output[k++] = 'l';  // Заменяем "ln" на "l".
      i++;
    } else if (strncmp(&input[i], "log", 3) == 0) {
      output[k++] = 'g';  // Заменяем "log" на "g".
      i += 2;
    } else if (i == 0 && input[i] == '-') {
      output[k++] = '0';
      output[k++] = '-';
    } else if (input[i] == '(' && input[i + 1] == '-') {
      output[k++] = '(';
      output[k++] = '0';
    } else if ((isdigit(input[i])) &&
               (input[i + 1] == '(' || input[i + 1] == 'n' ||
                input[i + 1] == 'a' || input[i + 1] == 'c' ||
                input[i + 1] == 's' || input[i + 1] == 't' ||
                input[i + 1] == 'm' || input[i + 1] == 'o' ||
                input[i + 1] == 'l')) {
      output[k++] = input[i];
      output[k++] = '*';
    } else {
      output[k++] = input[i];
    }
  }
}

int s21_evaluate_expression_with_variable(const char *polish_str, double *res,
                                          double x) {
  int flag = 0;
  struct stack_evaluation *stck_e = create_evaluation(NMAX);
  int i = 0;
  while (polish_str[i]) {
    if (isdigit(polish_str[i]) != 0 || polish_str[i] == 46) {
      char nums[NMAX] = {0};
      int k = 0;
      while (polish_str[i] != ' ') {
        nums[k++] = polish_str[i++];
      }
      s21_push_to_evaluation_stack(stck_e, atof(nums));
    } else if (polish_str[i] == 'x') {
      s21_push_to_evaluation_stack(stck_e, x);
    } else if (!((polish_str[i] == '-' || polish_str[i] == '*' ||
                  polish_str[i] == '/') &&
                 stck_e->top_index == 1) &&
               flag == 0) {
      flag = s21_perform_operation_on_numbers(polish_str, i, stck_e);
    }
    i++;
  }
  *res = s21_pop_from_evaluation_stack(stck_e);
  s21_destroy_evaluation_stack(stck_e);
  return flag;
}
