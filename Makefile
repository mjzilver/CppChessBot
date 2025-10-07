TARGET = CppChess
BUILD_DIR = build
SRC_DIR = src
CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
H_FILES := $(shell find $(SRC_DIR) -type f -name '*.h')

.PHONY: all
all: run

# ------
# Build
# ------

$(BUILD_DIR)/Makefile: CMakeLists.txt $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && $(MAKE)

.PHONY: run
run: build
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
	clang-format -i $(CPP_FILES) $(H_FILES)

.PHONY: tidy
tidy:
	cd $(BUILD_DIR) && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	clang-tidy $(CPP_FILES) $(H_FILES) --fix -p $(BUILD_DIR) -- -x c++

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
