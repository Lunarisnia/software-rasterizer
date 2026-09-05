BUILD_DIR ?= build
BUILD_TYPE ?= Debug

.PHONY: all configure build test run debug-configure debug-build debug-run clean

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	cmake --build $(BUILD_DIR)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

run: build
	./$(BUILD_DIR)/examples/window/swr_window_example

debug-configure:
	cmake -S . -B build-asan \
		-DCMAKE_BUILD_TYPE=Debug \
		-DSWR_ENABLE_SANITIZERS=ON

debug-build: debug-configure
	cmake --build build-asan

debug-run: debug-build
	./build-asan/examples/window/swr_window_example

clean:
	rm -rf $(BUILD_DIR) build-asan
