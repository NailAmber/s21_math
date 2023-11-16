#include "s21_math.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


int s21_abs(int x){
    if (x<0) {
        x *= -1;
    }
    return x;
}
long double s21_fabs(double x){
    if (x<0) {
        x *= -1;
    }
    return x;
    
}
long double s21_fmod(double x, double y){
    long double res;
    if ((x<0 && y > 0) || (y < 0 && x > 0)) {
        res = x - y * s21_ceil(x/y);
        
    }
    else{
        res = x - y * s21_floor(x/y);
    }
    return res;
}
long double s21_ceil(double x) {
    int flag = 0;
    if (x < 0)
        flag = 1;
    char buff [100];
    sprintf(buff, "%.0lf", x+0.4999999999);
    long double res;
    sscanf(buff, "%Lf", &res);
    if (res == 0 && flag)
        res *= -1;
    return res;
}
long double s21_floor(double x){
    char buff [100];
    sprintf(buff, "%.0lf", x-0.49999999999);
    long double res;
    sscanf(buff, "%Lf", &res);
    if (res == -0)
        res *= -1;
    return res;
}
long double s21_sin(double x){

    double angle = s21_fmod((x * (180.0 / S21_PI)), 360.0);
    int sign = 1;
    if (x > 0) {
        if ((angle > 180 && angle <= 270) || angle > 270) {
         sign = -1;
    }
    }
    if (x < 0) {
        sign = -1;
        if ((angle > -90 && angle <= -180) || angle > -180) {
         sign = 1;
    }
    }
    long double x1 = s21_fmod(x,  S21_PI);
    long double result = 0.0;
    long double term = x1;
   for ( int n=1; n<25; n += 2)
   {
      result += sign * term;
      term = term * x1 * x1 / ((n + 1) * (n + 2));
      sign = -sign;
   }
   return result;
}
long double s21_cos(double x){

    double angle = s21_fmod((x * (180.0 / S21_PI)), 360.0);
    int sign = 1;
    if ((angle > 180 && angle <= 270) || angle > 270) {
        sign = -1;
    }
    if (x < 0) {
        sign = -1;
        if ((angle > -90 && angle <= -180) || angle > -180) {
         sign = 1;
    }
    }
    long double x1 = s21_fmod(x, S21_PI);
    long double result = 0.0;
    long double term = 1;
   for ( int n=0; n<25; n += 2)
   {
      result += sign * term;
      term = term * x1 * x1 / ((n + 1) * (n + 2));
      sign = -sign;
   }
   return result;
}
long double s21_tan(double x){
    return s21_sin(x) / s21_cos(x);
}
long double s21_atan(double x){
    long double result = 0.0;
    double orig_x = x;
    
    
    int sign = 1;
    if (x > 1 || x < -1){
        x = 1.0/x;
    }
    if (x>0.99 && x <1.001){
        result = S21_PI / 4.0;
    }else if (x < -0.99 && x > -1.001) {
        result = -S21_PI / 4.0;
    }else
    {
    long double term = x;
    
    for (int n = 1; n < 736; n+=2){
        result += sign * term;
        term = term * x * x * n / (n+2);
        sign = -sign;
    }
    if (orig_x > 1) {
        result = S21_PI / 2.0 - result;
    }
    else if (orig_x < -1) {
        result = -S21_PI / 2.0 - result;
    }
    }
    return result;
}
long double s21_sqrt(double x){
    
    long double result = x;
    if (x < 0 || x != x || x == S21_MINUS_INF){
        result = S21_NAN;
    
    } else if (x == 0) {
        result = 0;
    } else if (x == S21_INF) {
        result = S21_INF;
    }
    else{
    long double term = 1;
    for (int i = 0; i < 20; i++) {
        result = (result + term) *0.5;
        term = x / result;
    }
    }
    return result;
}

long double s21_asin(double x){
    long double result = 0.0;
    if (s21_fabs(x) > 1){
        result = S21_NAN;
    }
    else if (x == 1) {
        result = 0.5 * S21_PI;
    }
    else if (x == -1) {
        result = 0.5 * -S21_PI;
    
    }
    else {
        result = s21_atan(x/s21_sqrt(1- x*x));
    }
    return result;
}
long double s21_acos(double x){
    long double result = 0.0;
    if (s21_fabs(x) > 1){
        result = S21_NAN;
    } else if (x == 0){
        result = 0.5 * S21_PI;
    }
    else if (x > 0){
        result = s21_atan(s21_sqrt(1 - x * x)/ x);
    }
    else {
        result =  S21_PI +s21_atan(s21_sqrt(1 - x * x)/x);
    }
    return result;
}

long double s21_exp(double x){
    double raised = s21_floor(x);
    double downed = x - raised;
    long degree = raised;

    long double result1 = S21_E;
    long double result = 1;

    if (x != x) {
        result1 = S21_NAN;
    }else if (x == S21_INF){
        result1 = S21_INF;
    } else if (x == S21_MINUS_INF){
        result1 = 0.0;
    } else
    {

    if (x < 0){
        degree = -degree;
    }

    while (degree) {
        if (s21_fmod(degree, 2) == 0){
            degree /= 2;
            result1 *= result1;
        }
        else {
        degree--;
        result *= result1;
        }
    
    }
    result1 = 1.;
    if (downed != 0) {
    //printf("downed = %lf\n", downed);
    //printf("raised = %lf\n", raised);
    
    
    long double term = downed;
    long fact = 1;

    for(int i = 2; i < 25; i++){
        result1 += term/ fact;
        term = term * downed;
        fact *= i;
    }
    }
    if (x<0) {
    result = 1 / result;
    }
    }
    return result * result1;
}

long double s21_log(double x){
    long double result = 0.0;
    if (x == S21_INF) {
        result = S21_INF;
    }else if (x == +0) {
        result = S21_MINUS_INF;
    } else if (x <= 0.0 || x != x) {
        result = S21_NAN;
    
    } else{
        //double n = s21_floor(x);
        //double x_new = x / s21_exp(n);
        for (int i = 0; i < 20; i++){
            result = result + 2 * ((x - s21_exp(result)) / (x + s21_exp(result)));
        }
    }
    return result;
}
long double s21_pow(double base, double exp){
    //printf("dgs");
     long double result = 1;
     long double result1 = base;
     //printf("dgs");
    if (s21_pow_check(base, exp) != -123.123){
        //printf("dgs");
        result1 = s21_pow_check(base, exp);
    }else{
    double raised = s21_floor(exp);
    double downed = exp - raised;
    long degree = raised;

    
    
    if (exp < 0){
        degree = -degree;
    }

    while (degree) {
        if (s21_fmod(degree, 2) == 0){
            degree /= 2;
            result1 *= result1;
        }
        else {
        degree--;
        result *= result1;
        }
    
    }
    result1 = 1.;
    if (downed != 0) {
    //printf("downed = %lf\n", downed);
    //printf("raised = %lf\n", raised);
    
    result *= s21_exp(downed * s21_log(base));
    }
    if (exp<0) {
    result = 1 / result;
    }
    }
    return result * result1;
}

long double s21_pow_check(double base, double exp){
    long double result = -123.123;
    //printf("%lf%lf",base,exp);
    if (base == -1 && exp == S21_INF) {
        result = 1;
    }else if (base == S21_INF && exp == 1) {
        result = S21_INF;
    }else if (base == S21_MINUS_INF && exp > 0 && s21_fmod(exp, 2) == 0) {
        result = S21_INF;
    }else if (base == S21_MINUS_INF && exp > 0 && s21_fmod(exp, 2) != 0) {
        result = S21_MINUS_INF;
    }else if (base == S21_MINUS_INF && exp < 0 && s21_fmod(exp, 2) == 0) {
        result = 0.;
    }else if (base == S21_MINUS_INF && exp < 0 && s21_fmod(exp, 2) != 0) {
        result = -0.;
    }else if (base > 1 && exp == S21_INF) {
        result = S21_INF;
    }else if (base < 1 && exp == S21_INF) {
        result = 0;
    } else if ((base == 1 || base == -1) && exp == S21_MINUS_INF){
        result = 1;
    } else if ((base > 1 || base < -1) && exp == S21_MINUS_INF) {
        result = 0;
    } else if (exp == 0) {
        result = 1.;
    } else if (base != base || exp != exp) {
        result = S21_NAN;
    } else if (((base == S21_INF || base == S21_MINUS_INF) && exp > 0) || base == 1) {
        result = 1.;
    } else if (((base == S21_INF || base == S21_MINUS_INF) && exp < 0) || (base == 0. && exp == S21_INF)) {
        result = 0.;
    } else if ((base == 0. && exp == S21_MINUS_INF) || (base == 0 && exp == S21_INF) || (base == -0. && exp < 0 && s21_floor(exp) == exp)  || ((base == S21_INF || base == S21_MINUS_INF) && (exp == S21_INF || exp == S21_MINUS_INF))){
        result = S21_INF;
    } else if ((base == 0. && exp > 0) || (base == -0 && exp > 0 && s21_fmod(exp, 2) == 0. && s21_floor(exp) == exp)){
        result = 0;
    } else if (base == -0. && exp > 0 && s21_fmod(exp, 2) != 0.){
        result = -0.;
    } else if (base == -1 && s21_fmod(exp, 2) == 0 && s21_floor(exp) == exp){
        result = 1;
    } else if (base == -1 && s21_fmod(exp, 2) != 0 && s21_floor(exp) == exp) {
        result = -1;
    } else if (base < 0 && s21_floor(exp) != exp){
        result = S21_NAN;
    } else if (exp == S21_MINUS_INF) {
        result = S21_INF;
    }


    return result;
}