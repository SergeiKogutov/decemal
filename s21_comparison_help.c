#include "s21_decimal.h"

int s21_comparison_bits(s21_decimal dec1, s21_decimal dec2) {
  int dec1_sum = 0;
  int dec2_sum = 0;
  int flag = 0;
  for (int i = 95; i >= 0 && !flag; --i) {
    dec1_sum = s21_get_bit(dec1, i);
    dec2_sum = s21_get_bit(dec2, i);
    if (dec1_sum > dec2_sum) {
      flag = 1;
    } else if (dec1_sum < dec2_sum) {
      flag = 2;
    }
  }
  return flag;
}

int s21_comparison_sing(int dec1, int dec2) {
  int flag = 0;
  if (dec1 > dec2) {
    flag = 1;
  } else if (dec1 < dec2) {
    flag = 2;
  } else if (dec1 == dec2) {
    flag = 0;
  }
  return flag;
}
void s21_comparison_reverse(int *flag) {
  if (*flag == 1) {
    *flag = 2;
  } else if (*flag == 2) {
    *flag = 1;
  }
}

int s21_comparison(s21_decimal dec1, s21_decimal dec2) {
  int dec1_scale = s21_get_scale(dec1);
  int dec2_scale = s21_get_scale(dec2);
  int diff_scale = dec1_scale - dec2_scale;
  s21_normalize(&dec1, &dec2);
  int dec1_sing = s21_get_sign(dec1);
  int dec2_sing = s21_get_sign(dec2);
  int flag = s21_comparison_sing(!dec1_sing, !dec2_sing);
  if (flag == 0 && diff_scale >= 0) {
    flag = s21_comparison_bits(dec1, dec2);
  } else if (flag == 0 && diff_scale < 0) {
    flag = s21_comparison_bits(dec2, dec1);
    s21_comparison_reverse(&flag);
  }
  if (dec1_sing && dec2_sing) {
    s21_comparison_reverse(&flag);
  }
  if (dec1.bits[0] == 0 && dec1.bits[1] == 0 && dec1.bits[2] == 0 &&
      dec2.bits[0] == 0 && dec2.bits[1] == 0 && dec2.bits[2] == 0) {
    flag = 0;
  }
  return flag;
}
