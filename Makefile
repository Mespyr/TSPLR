SRC_DIRS=src src/window
SRC_FILES=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
HEADERS=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.hpp))

format: $(SRC_FILES) $(HEADERS)
	clang-format -i $(SRC_FILES) $(HEADERS) -style=file

build: $(SRC_FILES) $(HEADERS)
	cmake --build build/ -j$(nproc)
