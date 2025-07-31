CC = gcc
CFLAGS = -Wall -Wextra -g

ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG=1
else
    CFLAGS += -DDEBUG=0
endif

# Target executable
TARGET = sword-shell
SRC = shell.c shell_utils.c
OBJ = $(SRC:.c=.o)

TEST_TARGET = run_tests
TEST_SRC = test.c shell_utils.c
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean run test rebuild

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


# Run main program
run: $(TARGET)
	./$(TARGET)

# Build and run unit tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Clean all
clean:
	rm -f $(TARGET) $(OBJ) $(TEST_TARGET) $(TEST_OBJ)

# Full rebuild
rebuild: clean all
