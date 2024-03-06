#include "s21_decimal.h"

void s21_help_other(long double float_to_int, long double diff,
                    s21_decimal *result) {
  if (float_to_int < 0.0) {
    s21_set_bit(result, 127, 1);
    float_to_int *= -1;
  }
  for (int i = 0; float_to_int >= 1 && i < 96; i++) {
    float_to_int = floor(float_to_int) / 2;
    diff = float_to_int - floor(float_to_int);
    if (diff > 0.0) {
      s21_set_bit(result, i, 1);
    } else {
      s21_set_bit(result, i, 0);
    }
  }
  s21_set_scale(result, 0);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] =
      ((s21_get_sign(*result) ^ 1) << 31) | (s21_get_scale(*result) << 16);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  float diff = 0;
  if (s21_get_scale(value)) {
    long double float_to_int = 0.0;
    s21_from_decimal_to_double(value, &float_to_int);
    s21_help_other(float_to_int, diff, result);
  } else {
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  long double float_round = 0.0;
  long double diff = 0;
  s21_from_decimal_to_double(value, &float_round);
  float_round = round(float_round);
  s21_help_other(float_round, diff, result);
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  s21_truncate(value, result);
  if (s21_get_sign(value) && s21_is_not_equal(*result, value)) {
    s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
  }
  return 0;
}
