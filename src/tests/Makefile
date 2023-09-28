.PHONY: all clean interpolation parser

CC=g++
STANDART=-std=c++17
# CFLAGS=$(STANDART) -Wall -Wextra -Werror -pedantic
GTEST=-lgtest -lgtest_main -pthread
INTERPOLATION=../algorithms/interpolation/cubic_spline.cc ../algorithms/interpolation/newton_polynomial.cc
SRC=../common/data_struct.cc

all: interpolation

interpolation:
	$(CC) $(CFLAGS) $(SRC) $(INTERPOLATION) interpolation.cc -o interpolation $(GTEST)
	./interpolation

parser:
	$(CC) $(CFLAGS) $(SRC) parser.cc -o parser $(GTEST)
	./parser

clean:
	rm -rf parser interpolation
