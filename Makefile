CFLAGS=-Wall -Wextra -Werror -std=gnu11
TESTS=s21_math_test.h s21_math_test.c
POSIX=-D_POSIX_C_SOURCE=200809L
COVER=--coverage

all: clean s21_math 
	
s21_math: main.o s21_math.a
	gcc $(CFLAGS) $(POSIX) main.o s21_math.a -lm -o main $(COVER)

main.o:
	gcc -c $(CFLAGS) $(POSIX) main.c

s21_math.a: 
	gcc $(CFLAGS) $(POSIX) s21_math.c -c $(COVER)
	ar rcs s21_math.a s21_math.o

s21_math_test.o:
	gcc $(CFLAGS) $(POSIX) $(TESTS) -lcheck -c $(COVER)

test: clean s21_math.a s21_math_test.o
	gcc $(COVER) $(CFLAGS) $(POSIX) s21_math_test.o  s21_math.a -lcheck -lm -o test 
	chmod +x test
	./test

gcov_report: clean test
	gcov *.gcno
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage


clean:
	rm -rf main *.a *.o *gcno *.gcda s21_math_test *.gcov ./coverage *.info test *.gch

	