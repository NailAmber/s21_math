CFLAGS=-Wall -Wextra -Werror
TESTS=s21_math_test.h s21_math_test.c s21_cos_test.c s21_sin_test.c s21_tan_test.c s21_atan_test.c s21_asin_test.c s21_acos_test.c s21_ceil_test.c

all: clean s21_math s21_math.a
	
s21_math:	main.o s21_math.a
	gcc $(CFLAGS) main.o s21_math.a -o main -lm

main.o: main.c
	gcc -O -c $(CFLAGS) main.c

s21_math.a: 
	gcc $(CFLAGS) s21_math.c -O -c
	ar rcs s21_math.a s21_math.o

test: s21_math.a s21_math
	gcc --coverage $(CFLAGS) $(TESTS)  s21_math.a -lcheck -lm -o test 
	chmod +x test
	./test

gcov_report: clean test
	gcov test-s21_math_test.gcno
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage


clean:
	rm -rf main *.a *.o *gcno *.gcda s21_math_test *.gcov ./coverage *.info test