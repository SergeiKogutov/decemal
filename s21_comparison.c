#include "s21_decimal.h"

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_not_equal(dec1, dec2);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_greater(dec1, dec2) || s21_is_equal(dec1, dec2);
}
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_less(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_greater(dec1, dec2) ^ 1 && s21_is_equal(dec1, dec2) == 0;
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  return (s21_comparison(dec1, dec2) == 1) ? 1 : 0;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_comparison(dec1, dec2) == 0) ? 0 : 1;
}