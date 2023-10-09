.PHONY: all clean algorithms parser

CC=g++
STANDART=-std=c++17
# CFLAGS=$(STANDART) -Wall -Wextra -Werror -pedantic
GTEST=-lgtest -lgtest_main -pthread
PARSER=../common/data_struct.cc
SRC=$(PARSER)\
	../algorithms/cubic_spline/cubic_spline.cc\
	../algorithms/newton_polynomial/newton_polynomial.cc\
	../algorithms/least_squares/least_squares.cc

all: parser algorithms

algorithms:
	$(CC) $(CFLAGS) $(SRC) algorithms/test.cc algorithms/run.cc -o algorithms_test $(GTEST)
	./algorithms_test

parser:
	$(CC) $(CFLAGS) $(PARSER) parser/test.cc -o parser_test $(GTEST)
	./parser_test

clean:
	rm -rf parser_test algorithms_test
