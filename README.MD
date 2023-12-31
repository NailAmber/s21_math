# s21_math

Hello. This is my math.h static library which i called s21_math.h

You can use it like you want.

# Overview of some "s21_math.h" functions
| No. | Function                                     | Description                                                  |
|-----|----------------------------------------------|--------------------------------------------------------------|
| 1   | int s21_abs(int x)                           | computes absolute value of an integer value                  |
| 2   | long double s21_acos(double x)               | computes arc cosine                                          |
| 3   | long double s21_asin(double x)               | computes arc sine                                            |
| 4   | long double s21_atan(double x)               | computes arc tangent                                         |
| 5   | long double s21_ceil(double x)               | returns the nearest integer not less than the given value    |
| 6   | long double s21_cos(double x)                | computes cosine                                              |
| 7   | long double s21_exp(double x)                | returns e raised to the given power                          |
| 8   | long double s21_fabs(double x)               | computes absolute value of a floating-point value            |
| 9   | long double s21_floor(double x)              | returns the nearest integer not greater than the given value |
| 10  | long double s21_fmod(double x, double y)     | remainder of the floating-point division operation           |
| 11  | long double s21_log(double x)                | computes natural logarithm                                   |
| 12  | long double s21_pow(double base, double exp) | raises a number to the given power                           |
| 13  | long double s21_sin(double x)                | computes sine                                                |
| 14  | long double s21_sqrt(double x)               | computes square root                                         |
| 15  | long double s21_tan(double x)                | computes tangent                                             |

# Building

for make the static library:
```sh
make s21_math.a
```

for test reporting:
```sh
make gcov_report
```

then -> in dir coverage -> index.html -> open in browser.

for cleaning dir from compiling:
```sh
make clean
```
# Standarts
Developed in C language of C11 standard using gcc compiler. Used the POSIX.1-2017 standard.
