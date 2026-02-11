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

SRC_DIR  := src
BUILD_DIR := build

SRCS := barrel.cpp mystring.cpp rect.cpp text.cpp matrix.cpp
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))

vpath %.cpp $(SRC_DIR)
vpath %.hpp $(SRC_DIR)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS) $(SRC_DIR)/lab1.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRC_DIR)/lab1.cpp $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

LEAKS_OBJS := $(addprefix $(BUILD_DIR)/leaks_, $(SRCS:.cpp=.o))

build/leaks_%.o: %.cpp | $(BUILD_DIR)
	$(CXX) -Wall -Wextra -g -O0 -fsanitize=address -c $< -o $@

build/leaks.out: $(LEAKS_OBJS) $(SRC_DIR)/lab1.cpp | $(BUILD_DIR)
	$(CXX) -Wall -Wextra -g -O0 -fsanitize=address $(SRC_DIR)/lab1.cpp $(LEAKS_OBJS) -o $@

.PHONY: leaks
leaks: build/leaks.out
	./build/leaks.out < input.txt	

$(BUILD_DIR)/barrel.o: barrel.hpp
$(BUILD_DIR)/mystring.o: mystring.hpp
$(BUILD_DIR)/rect.o: rect.hpp
$(BUILD_DIR)/text.o: text.hpp mystring.hpp

clean:
	rm -rf $(BUILD_DIR)