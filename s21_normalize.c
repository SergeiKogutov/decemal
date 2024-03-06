#include "s21_decimal.h"

void s21_normalize_copy(s21_decimal *dec1, s21_decimal dec2) {
  for (int i = 127; i >= 0; i--) {
    s21_set_bit(dec1, i, s21_get_bit(dec2, i));
  }
}

void s21_normalize_scale(s21_decimal *dec1, int diff_scale, int dec1_scale) {
  s21_decimal res_dec_scale = {{0}};
  s21_decimal new_dec_scale = {{0}};
  s21_from_float_to_decimal(pow(10, diff_scale), &new_dec_scale);
  s21_mul(*dec1, new_dec_scale, &res_dec_scale);
  s21_set_scale(&res_dec_scale, dec1_scale + diff_scale);
  s21_normalize_copy(dec1, res_dec_scale);
}

void s21_normalize(s21_decimal *dec1, s21_decimal *dec2) {
  int diff_scale = s21_get_scale(*dec1) - s21_get_scale(*dec2);
  if (diff_scale > 0) {
    s21_normalize_scale(dec2, diff_scale, diff_scale);
  } else if (diff_scale < 0) {
    s21_normalize_scale(dec1, -diff_scale, diff_scale);
  }
}
