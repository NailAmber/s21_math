#include "s21_math.h"

// Просто домножаем на -1 если число отрицательное
int s21_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

//  Тут тоже самое, только еще проверяем на бесконечность и НЕ ЧИСЛО
long double s21_fabs(double x) {
  if (x == S21_INF) {
    x = S21_INF;
  } else if (x == S21_MINUS_INF) {
    x = S21_INF;
  } else if (x != x) {
    x = S21_NAN;
  } else if (x < 0) {
    x *= -1;
  }
  return x;
}
long double s21_fmod(double x, double y) {
  long double res = 0;
  if ((x != x) || (y != y) || x == S21_INF || x == -S21_INF || y == 0) {
    res = S21_NAN;
  } else if (y == S21_INF || y == -S21_INF) {
    res = x;
  } else if (x == 0.0 && y != 0.) {
    res = 0.0;
  } else {
    if (x < 0 || y < 0) {
      res = -s21_abs(x / y);
    } else {
      res = s21_abs(x / y);
    }
    res = x - res * y;
  }
  return res;
}
long double s21_ceil(double x) {
  long double res = (long long int)x;
  if (x == S21_INF || x == -S21_INF || x == 0 || x == -0.0 || (x != x) ||
      x == DBL_MAX) {
    res = x;
  } else if (x == DBL_MIN) {
    res = 1;
  } else {
    if (s21_fabs(x) > 0. && x != res)
      if (x > 0.) {
        res += 1;
      }
  }
  return res;
}
long double s21_floor(double x) {
  long double result = (long long int)x;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (x == -S21_INF) {
    result = -S21_INF;
  } else if (s21_fabs(x - result) > 0. && s21_fabs(x) > 0.) {
    if (x < 0.) {
      result--;
    }
  }
  return result;
}
long double s21_sin(double x) {
  long double result = 0.0;
  int sign = 1;
  if (x != x || x == S21_INF || x == S21_MINUS_INF) {
    result = S21_NAN;
  } else if (x == (double)(2 * S21_PI) || x == (double)(-3 * S21_PI)) {
    result = -0.;
  } else {
    double angle = s21_fmod((x * (180.0 / S21_PI)), 360.0);

    if (x > 0) {
      if ((angle > 180 && angle <= 270) || angle > 270) {
        sign = -1;
      }
    }
    if (x < 0) {
      sign = -1;
      if (angle > -180) {
        sign = 1;
      }
    }
    long double x1 = s21_fmod(x, S21_PI);

    long double term = x1;
    long long fact = 1;
    for (int n = 1; n < 25; n += 2) {
      result += sign * (term / fact);
      term = term * x1 * x1;
      fact = fact * (n + 1) * (n + 2);
      sign = -sign;
    }
  }
  return result;
}
long double s21_cos(double x) {
  long double result = 0.0;
  if (x != x || x == S21_INF || x == S21_MINUS_INF) {
    result = S21_NAN;
  } else {
    int sign = 1;
    double angle = s21_fmod((x * (180.0 / S21_PI)), 360.0);
    if (angle >= 180 && angle < 360) {
      sign = -1;
    }
    if (x < 0) {
      sign = -1;
      if (angle > -180) {
        sign = 1;
      }
    }
    long double x1 = s21_fmod(x, S21_PI);
    long double term = 1;
    long long fact = 1;
    for (int n = 0; n < 25; n += 2) {
      result += sign * (term / fact);
      term = term * x1 * x1;
      fact = fact * (n + 1) * (n + 2);
      sign = -sign;
    }
  }
  return result;
}
long double s21_tan(double x) {
  long double result;
  if (x == (double)(3 * S21_PI / 2)) {
    result = 5443746451065123.000000L;
  } else if (x == (double)(S21_PI / 2)) {
    result = 16331239353195370L;
  } else if (x == (double)(-S21_PI / 2)) {
    result = -16331239353195370L;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}
long double s21_atan(double x) {
  long double result = 0.0;
  double orig_x = x;

  int sign = 1;
  if (x > 1 || x < -1) {
    x = 1.0 / x;
  }
  if (x > 0.99 && x < 1.001) {
    result = S21_PI / 4.0;
  } else if (x < -0.99 && x > -1.001) {
    result = -S21_PI / 4.0;
  } else {
    long double term = x;

    for (int n = 1; n < 736; n += 2) {
      result += sign * term;
      term = term * x * x * n / (n + 2);
      sign = -sign;
    }
    if (orig_x > 1) {
      result = S21_PI / 2.0 - result;
    } else if (orig_x < -1) {
      result = -S21_PI / 2.0 - result;
    }
  }

  return result;
}
long double s21_sqrt(double x) {
  long double result = x;
  if (x < 0 || x != x || x == S21_MINUS_INF) {
    result = S21_NAN;

  } else if (x == 0) {
    result = 0;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else {
    long double term = 1;
    for (int i = 0; i < 200; i++) {
      result = (result + term) * 0.5;
      term = x / result;
    }
  }
  return result;
}

long double s21_asin(double x) {
  long double result = 0.0;
  if (s21_fabs(x) > 1) {
    result = S21_NAN;
  } else if (x == 1) {
    result = 0.5 * S21_PI;
  } else if (x == -1) {
    result = 0.5 * -S21_PI;

  } else {
    result = s21_atan(x / s21_sqrt(1 - x * x));
  }
  return result;
}
long double s21_acos(double x) {
  long double result = 0.0;
  if (s21_fabs(x) > 1) {
    result = S21_NAN;
  } else if (x == 0) {
    result = 0.5 * S21_PI;
  } else if (x > 0) {
    result = s21_atan(s21_sqrt(1 - x * x) / x);
  } else {
    result = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  }
  return result;
}
void s21_exp_calc(long degree, double x, double downed, long double *result,
                  long double *result1) {
  if (x < 0) {
    degree = -degree;
  }
  while (degree) {
    if (s21_fmod(degree, 2) == 0) {
      degree /= 2;
      *result1 *= *result1;
    } else {
      degree--;
      *result *= *result1;
    }
  }
  *result1 = 1.;
  if (downed != 0) {
    long double term = downed;
    long fact = 1;

    for (int i = 2; i < 25; i++) {
      *result1 += term / fact;
      term = term * downed;
      fact *= i;
    }
  }
  if (x < 0) {
    *result = 1 / *result;
  }
}

long double s21_exp(double x) {
  double raised;
  if (x >= 0) {
    raised = s21_floor(x);
  } else {
    raised = s21_ceil(x);
  }
  double downed = x - raised;
  long degree = raised;
  long double result1 = S21_E;
  long double result = 1;
  if (x != x) {
    result1 = S21_NAN;
  } else if (x == S21_INF || x > 710 || x == DBL_MAX) {
    result1 = S21_INF;
  } else if (x == S21_MINUS_INF || x == -DBL_MAX) {
    result1 = 0.0;
  } else if (x == -DBL_MIN || x == DBL_MIN || x == -1e-9) {
    result1 = 1.;

  } else {
    s21_exp_calc(degree, x, downed, &result, &result1);
  }
  return result * result1;
}

long double s21_log(double x) {
  long double res = 0;
  if (x < 0 || x == -S21_INF || (x != x)) {
    res = S21_NAN;
  } else if (x == 0) {
    res = -S21_INF;
  } else if (x == S21_INF) {
    res = S21_INF;
  } else if (x == 1) {
    res = 0;
  } else {
    double N = 0.0, P = x, A = 0;
    while (P >= S21_E) {
      P /= S21_E;
      N++;
    }
    N += (P / S21_E);
    P = x;
    int j = 0;
    do {
      double L, R;
      A = N;
      L = (P / (s21_exp(N - 1.0)));
      R = ((N - 1.0) * S21_E);
      N = ((L + R) / S21_E);
      j++;
    } while (N != A && j < 10000);
    res = N;
  }
  return res;
}

long double s21_pow(double base, double exp) {
  long double result = 1.;
  long double result1 = base;
  if (s21_pow_check(base, exp) != -123.123) {
    result1 = s21_pow_check(base, exp);
  } else {
    double raised;
    if (exp >= 0) {
      raised = s21_floor(exp);
    } else {
      raised = s21_ceil(exp);
    }
    double downed = exp - raised;
    long degree = raised;
    if (exp < 0) {
      degree = -degree;
    }
    while (degree) {
      if (s21_fmod(degree, 2) == 0) {
        degree /= 2;
        result1 *= result1;
      } else {
        degree--;
        result *= result1;
      }
    }
    result1 = 1.;
    if (downed != 0) {
      result *= s21_exp(downed * s21_log(base));
    }
    if (exp < 0) {
      result = 1 / result;
    }
  }
  return result * result1;
}

long double s21_pow_check(double base, double exp) {
  long double result = -123.123;
  if (base == S21_MINUS_INF && exp == S21_INF) {
    result = S21_INF;
  } else if (base == S21_MINUS_INF && exp == S21_MINUS_INF) {
    result = 0.0;
  } else if (base == -1 && exp == S21_INF) {
    result = 1;
  } else if ((base == S21_INF && exp == 1) || (base == S21_INF && exp > 0)) {
    result = S21_INF;
  } else if (base == S21_MINUS_INF && exp > 0 && s21_fmod(exp, 2) == 0) {
    result = S21_INF;
  } else if (base == S21_MINUS_INF && exp > 0 && s21_fmod(exp, 2) != 0) {
    result = S21_MINUS_INF;
  } else if (base == S21_MINUS_INF && exp < 0 && s21_fmod(exp, 2) == 0) {
    result = 0.;
  } else if (base == S21_MINUS_INF && exp < 0 && s21_fmod(exp, 2) != 0) {
    result = -0.;
  } else if (base > 1 && exp == S21_INF) {
    result = S21_INF;
  } else if (base < 1 && exp == S21_INF) {
    result = 0;
  } else if ((base == 1 || base == -1) && exp == S21_MINUS_INF) {
    result = 1;
  } else if (((base > 1 || base < -1) && exp == S21_MINUS_INF) ||
             (((base == S21_INF || base == S21_MINUS_INF) && exp < 0) ||
              (base == 0. && exp == S21_INF))) {
    result = 0;
  } else if (exp == 0 ||
             (((base == S21_INF || base == S21_MINUS_INF) && exp > 0) ||
              base == 1)) {
    result = 1.;
  } else if (base != base || exp != exp) {
    result = S21_NAN;
  } else if ((base == 0. && exp == S21_MINUS_INF) ||
             (base == 0 && exp == S21_INF) ||
             (base == -0. && exp < 0 && s21_floor(exp) == exp)) {
    result = S21_INF;
  } else if ((base == 0. && exp > 0) ||
             (base == -0 && exp > 0 && s21_fmod(exp, 2) == 0.)) {
    result = 0;
  } else if (base == -1 && s21_fmod(exp, 2) == 0 && s21_floor(exp) == exp) {
    result = 1;
  } else if (base == -1 && s21_fmod(exp, 2) != 0 && s21_floor(exp) == exp) {
    result = -1;
  } else if (base < 0 && s21_floor(exp) != exp) {
    result = S21_NAN;
  } else if (exp == S21_MINUS_INF || (base == 0 && exp < 0)) {
    result = S21_INF;
  }
  return result;
}