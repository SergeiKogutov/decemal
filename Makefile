CC=gcc
STDFLAGS=-Wall -Werror -Wextra -std=c11 
TST_CFLAGS:= -g $(STDFLAGS)
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose 

TARGET=s21_decimal.a

SRC=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o, ${SRC})

PREF_TEST_SRC=./unit_tests/
TEST_SRC=$(wildcard $(PREF_TEST_SRC)/s21_*.c)

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: $(TARGET) test

$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	make clean_obj

test: $(TARGET) 
ifeq ($(OS), Darwin)
	${CC} $(STDFLAGS) ${TEST_SRC} $< -o unit_test $(LIBS)
else
	${CC} $(STDFLAGS) ${TEST_SRC} $< -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test 0

gcov_report: clean_test
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
else
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clang:
	clang-format -n *.c *.h ./unit_tests/*.c --verbose
	clang-format -i *.c *.h ./unit_tests/*.c --verbose
	clang-format -n *.c *.h ./unit_tests/*.h --verbose
	clang-format -i *.c *.h ./unit_tests/*.h --verbose
	clang-format -n *.c *.h --verbose
	clang-format -i *.c *.h --verbose

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf test.dSYM

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf unit_test
	rm -rf RESULT_VALGRIND.txt
