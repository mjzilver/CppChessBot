TARGET = CppChess

.PHONY: build run all clean valgrind callgrind callgrind-view build-debug run-debug debug

build:
	mkdir -p build
	cd build && cmake .. && make

run:
	cd build &&	./$(TARGET)

all: clean build run

clean:
	rm -rf build

build-debug:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

run-debug:
	cd build && gdb ./$(TARGET)

debug:
	make build-debug
	make run-debug

valgrind:
	cd build && valgrind --leak-check=full --error-limit=no ./$(TARGET) > valgrind_output.txt 2>&1

callgrind:
	cd build && valgrind --tool=callgrind ./$(TARGET)

callgrind-view:
	kcachegrind ./build/callgrind.out.*

