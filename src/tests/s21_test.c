#include <check.h>

#include "../Backend/s21_calculator.h"

START_TEST(test_calc_1) {
  char input[255] = "5+7*2/(2-6)^3";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 4.78125);
}
END_TEST

START_TEST(test_calc_2) {
  char input[255] = "2+5+7+9*3*2^5";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 878);
}
END_TEST

START_TEST(test_calc_3) {
  char input[255] = "123.456+5*4^3";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 443.456);
}
END_TEST

START_TEST(test_calc_4) {
  char input[255] = "(8+2*5)/(1+3*2-4)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 6);
}
END_TEST

START_TEST(test_calc_5) {
  char input[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 10);
}
END_TEST

START_TEST(test_calc_6) {
  char input[255] = "cos(1*2)-1";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, -1.41614683655, 1e-06);
}
END_TEST

START_TEST(test_calc_7) {
  char input[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, -1.83907152908, 1e-06);
}
END_TEST

START_TEST(test_calc_8) {
  char input[255] = "sin(cos(5))";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, 0.27987335076, 1e-06);
}
END_TEST

START_TEST(test_calc_9) {
  char input[255] = "2.33mod1";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, 0.33, 1e-06);
}
END_TEST

START_TEST(test_calc_10) {
  double x = 10;
  char input[255] = "3+4*2/1-5+2^2";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_11) {
  double x = 10;
  char input[255] = "3+4*2/1-5+2^2";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_12) {
  double x = 0.0003;
  char input[255] = "asin(2*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 0.0006, 1e-06);
}
END_TEST

START_TEST(test_calc_13) {
  double x = 0.0019;
  char input[255] = "acos(2*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 1.567, 1e-03);
}
END_TEST

START_TEST(test_calc_14) {
  double x = 0.0019;
  char input[255] = "atan(2*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 0.00379998, 1e-06);
}
END_TEST

START_TEST(test_calc_15) {
  double x = 0.004;
  char input[255] = "tan(2*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 0.00800017, 1e-06);
}
END_TEST

START_TEST(test_calc_16) {
  double x = 25;
  char input[255] = "sqrt(2*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 7.07107, 1e-05);
}
END_TEST

START_TEST(test_calc_17) {
  double x = 2;
  char input[255] = "ln(10*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 2.99573, 1e-05);
}
END_TEST

START_TEST(test_calc_18) {
  double x = 2;
  char input[255] = "log(10*x)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, x);
  ck_assert_double_eq_tol(res, 1.30103, 1e-05);
}
END_TEST

START_TEST(test_calc_19) {
  char input[255] = "()";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, 0, 1e-06);
}
END_TEST

START_TEST(test_calc_20) {
  char input[255] = "3-(-3)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq_tol(res, 6, 1e-06);
}
END_TEST

START_TEST(test_calc_21) {
  char input[255] = "-5-(-3)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, -2);
}
END_TEST

START_TEST(test_calc_22) {
  char input[255] = "(4+2)*(8-3)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 30);
}
END_TEST

START_TEST(test_calc_23) {
  char input[255] = "5/0";
  int error = 0;
  s21_calculate_with_error(input, &error, 0.0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_24) {
  char input[255] = "mod5";
  int error = 0;
  s21_calculate_with_error(input, &error, 0.0);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(test_calc_25) {
  char input[255] = "^2";
  int error = 0;
  s21_calculate_with_error(input, &error, 0.0);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(test_calc_26) {
  char input[255] = "-3/(-3)";
  double res;
  int error = 0;
  res = s21_calculate_with_error(input, &error, 0.0);
  ck_assert_double_eq(res, 1);
}
END_TEST

START_TEST(test_calc_27) {
  char input[255] = ")77321321(sin(5))";
  int error = 0;
  s21_calculate_with_error(input, &error, 0.0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_string_1) {
  const char *str = "5+7*2/(2-6)^3";
  double res;
  // int error = 0;
  res = s21_checking_validity_string(str);
  ck_assert_double_eq(res, 0);
}
END_TEST

START_TEST(test_string_2) {  // 21_checking_validity_string(const char *str)
  const char *str = "5+7*2/2-6)^3";
  double res;
  // int error = 0;
  res = s21_checking_validity_string(str);
  ck_assert_double_eq(res, 1);
}
END_TEST

START_TEST(test_string_3) {
  char input[255] = ")77321321(sin(5))";
  int error = 0;
  s21_expression_and_function_validation(input, &error);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_string_4) {
  char input[255] = "m";
  int error = 0;
  s21_expression_and_function_validation(input, &error);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_string_5) {
  char input[255] = "-";
  int error = 0;
  s21_check_operator_syntax(input, &error);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_string_6) {
  char input[255] = "+)0123456789csatlx";
  int error = 0;
  s21_check_operator_syntax(input, &error);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_string_7) {
  char input[255] = "тт+";
  int error = 0;
  s21_check_operator_syntax(input, &error);
  ck_assert_int_eq(error, 1);
}
END_TEST

int main() {
  Suite *suite = suite_create("result: ");
  TCase *tcase_core = tcase_create("result: ");
  SRunner *suite_runner = srunner_create(suite);
  int res;
  suite_add_tcase(suite, tcase_core);

  tcase_add_test(tcase_core, test_calc_1);
  tcase_add_test(tcase_core, test_calc_2);
  tcase_add_test(tcase_core, test_calc_3);
  tcase_add_test(tcase_core, test_calc_4);
  tcase_add_test(tcase_core, test_calc_5);
  tcase_add_test(tcase_core, test_calc_6);
  tcase_add_test(tcase_core, test_calc_7);
  tcase_add_test(tcase_core, test_calc_8);
  tcase_add_test(tcase_core, test_calc_9);
  tcase_add_test(tcase_core, test_calc_10);
  tcase_add_test(tcase_core, test_calc_11);
  tcase_add_test(tcase_core, test_calc_12);
  tcase_add_test(tcase_core, test_calc_13);
  tcase_add_test(tcase_core, test_calc_14);
  tcase_add_test(tcase_core, test_calc_15);
  tcase_add_test(tcase_core, test_calc_15);
  tcase_add_test(tcase_core, test_calc_16);
  tcase_add_test(tcase_core, test_calc_17);
  tcase_add_test(tcase_core, test_calc_18);
  tcase_add_test(tcase_core, test_calc_19);
  tcase_add_test(tcase_core, test_calc_20);
  tcase_add_test(tcase_core, test_calc_21);
  tcase_add_test(tcase_core, test_calc_22);
  tcase_add_test(tcase_core, test_calc_23);
  tcase_add_test(tcase_core, test_calc_24);
  tcase_add_test(tcase_core, test_calc_25);
  tcase_add_test(tcase_core, test_calc_26);
  tcase_add_test(tcase_core, test_calc_27);
  tcase_add_test(tcase_core, test_string_1);
  tcase_add_test(tcase_core, test_string_2);
  tcase_add_test(tcase_core, test_string_3);
  tcase_add_test(tcase_core, test_string_4);
  tcase_add_test(tcase_core, test_string_5);
  tcase_add_test(tcase_core, test_string_6);
  tcase_add_test(tcase_core, test_string_7);

  srunner_run_all(suite_runner, CK_VERBOSE);
  res = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return res == 0 ? 0 : 1;
}
