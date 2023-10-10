.PHONY: all clean test lint get_lint dvi dist install uninstall run

SRC := $(shell find . -name "*.cc")
HEADERS := $(shell find . -name "*.h")

APP_NAME = algorithmic_trading

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	OPEN = ./build/$(APP_NAME)
endif
ifeq ($(OS), Darwin)
	OPEN = open build/$(APP_NAME).app
endif


all: install run

install:
	cmake -S . -B build
	make -C build

uninstall:
	rm -rf build

run:
	./build/$(APP_NAME)

test:
	make -C tests all

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) $(HEADERS) && echo "Clang-format passed"

get_lint:
	@clang-format --style=Google -i $(SRC) $(HEADERS) && echo "Formatted"

dvi:
	mkdir -p documentation
	@doxygen Doxyfile && mv html documentation && mv latex documentation
	@open documentation/html/index.html

dist:
	tar czf ../dist.tar *

clean: uninstall
	rm -rf CMakeLists.txt.user
	make -C tests clean
	rm -rf ../dist.tar
	rm -rf documentation