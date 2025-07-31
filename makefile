CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = sword-shell

# Source file
SRC = shell.c shell_utils.c

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)

# build and then Run the program
run: $(TARGET)
	./$(TARGET)

# Full rebuild
rebuild: clean all