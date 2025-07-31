CC = gcc
CFLAGS = -Wall -Wextra -g

ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG=1
else
    CFLAGS += -DDEBUG=0
endif

# Target executable
TARGET = sword-shell

# Source and object files
SRC = shell.c shell_utils.c
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Build each object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(TARGET) $(OBJ)

# Build and run
run: all
	./$(TARGET)

# Full rebuild
rebuild: clean all