
#include <check.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "../s21_decimal.h"

#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_2 196608

Suite *suite_is_less(void);
Suite *suite_is_less_or_equal(void);
Suite *suite_is_greater(void);
Suite *suite_is_greater_or_equal(void);
Suite *suite_is_equal(void);
Suite *suite_is_not_equal(void);
Suite *suite_truncate(void);
Suite *suite_negate(void);
Suite *suite_round(void);
Suite *suite_floor(void);
Suite *suite_add(void);
Suite *suite_div(void);
Suite *suite_mul(void);
Suite *suite_sub(void);
Suite *suite_float_to_decimal(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_int_to_decimal(void);
void run_test(void);
void run_testcase(Suite *testcase);