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

# Phony targets are commands, not files 
# allways run regardless of whether a file with that name exists
.PHONY: all clean run test

# Default target: build the main program
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Run main program (builds first if needed)
run: $(TARGET)
	./$(TARGET)

# Run unit tests (builds first if needed)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up all generated files
clean:
	rm -f $(TARGET) $(OBJ) $(TEST_TARGET) $(TEST_OBJ)

