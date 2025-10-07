TARGET = CppChess
BUILD_DIR = build
SRC_DIR = src
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)

.PHONY: all
all: clean build run

# ------
# Build
# ------
.PHONY: build
build: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && $(MAKE)

$(BUILD_DIR)/Makefile: CMakeLists.txt
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

.PHONY: run
run:
	cd $(BUILD_DIR) && ./$(TARGET)

.PHONY: run-console
run-console:
	cd $(BUILD_DIR) && ./$(TARGET) -nogui

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# ---------
# Formatting
# ---------

.PHONY: format
format:
	clang-format -i $(CPP_FILES)

.PHONY: tidy
tidy:
	clang-tidy $(CPP_FILES) -- -std=c++17

# ---------
# Debugging
# ---------
.PHONY: build-debug
build-debug: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && $(MAKE)

.PHONY: run-debug
run-debug:
	cd $(BUILD_DIR) && gdb ./$(TARGET)

.PHONY: debug
debug: build-debug run-debug

.PHONY: valgrind
valgrind:
	cd $(BUILD_DIR) && valgrind --leak-check=full --error-limit=no ./$(TARGET) > valgrind_output.txt 2>&1

.PHONY: callgrind
callgrind:
	cd $(BUILD_DIR) && valgrind --tool=callgrind ./$(TARGET)

.PHONY: callgrind-view
callgrind-view:
	kcachegrind ./$(BUILD_DIR)/callgrind.out.*
