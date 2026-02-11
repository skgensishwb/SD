CXX      := g++
CXXFLAGS := -Wall -Wextra

ifdef DEBUG
CXXFLAGS += -g -O0 -fsanitize=address
LDFLAGS  += -fsanitize=address
TARGET   := build/debug.out
else
CXXFLAGS += -O2 -DNDEBUG
TARGET   := build/ndebug.out
endif

SRC_DIR   := src
BUILD_DIR := build
TEST_DIR  := tests

SRCS := barrel.cpp mystring.cpp rect.cpp text.cpp matrix.cpp
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))

vpath %.cpp $(SRC_DIR)
vpath %.hpp $(SRC_DIR)

.PHONY: all clean run leaks test

all: $(TARGET)

$(TARGET): $(OBJS) $(SRC_DIR)/lab1.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRC_DIR)/lab1.cpp $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

LEAKS_FLAGS := -Wall -Wextra -g -O0 -fsanitize=address -DNDEBUG
LEAKS_OBJS  := $(addprefix $(BUILD_DIR)/leaks_, $(SRCS:.cpp=.o))

build/leaks_%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(LEAKS_FLAGS) -c $< -o $@

build/leaks.out: $(LEAKS_OBJS) $(SRC_DIR)/lab1.cpp | $(BUILD_DIR)
	$(CXX) $(LEAKS_FLAGS) -fsanitize=address $(SRC_DIR)/lab1.cpp $(LEAKS_OBJS) -o $@

leaks: build/leaks.out
	./build/leaks.out < input.txt

TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_BINS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.out, $(TEST_SRCS))

$(BUILD_DIR)/test_%.out: $(TEST_DIR)/test_%.cpp $(BUILD_DIR)/rect.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< $(BUILD_DIR)/rect.o -o $@

test: $(TEST_BINS)
	@echo "=== Запуск всех тестов ==="
	@for t in $(TEST_BINS); do \
		echo "--- Запуск $$t ---"; \
		./$$t || exit 1; \
	done
	@echo "=== Все тесты пройдены ==="

$(BUILD_DIR)/barrel.o: barrel.hpp
$(BUILD_DIR)/mystring.o: mystring.hpp
$(BUILD_DIR)/rect.o: rect.hpp
$(BUILD_DIR)/text.o: text.hpp mystring.hpp

clean:
	rm -rf $(BUILD_DIR)
