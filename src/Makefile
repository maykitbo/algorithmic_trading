.PHONY: all clean

all:
	cmake -S . -B build
	make -C build -j4
	./build/algorithmic_trading

clean:
	rm -rf build
	rm -rf CMakeLists.txt.user