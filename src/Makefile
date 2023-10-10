.PHONY: all clean test lint get_lint dvi dist

SRC := $(shell find . -name "*.cc")
HEADERS := $(shell find . -name "*.h")


all:
	cmake -S . -B build
	make -C build -j4
	./build/algorithmic_trading

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

clean:
	rm -rf build
	rm -rf CMakeLists.txt.user
	make -C tests clean
	rm -rf ../dist.tar
	rm -rf documentation