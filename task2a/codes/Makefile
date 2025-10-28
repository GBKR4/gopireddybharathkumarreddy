# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Target executable name
TARGET = social_media

# Source files
SRCS = platform.c post.c comment.c reply.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = platform.h post.h comment.h reply.h

# Default target
all: $(TARGET)

# Create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Clean everything including executable
distclean: clean
	rm -f $(TARGET)

# Rebuild everything
rebuild: distclean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug the program
debug: $(TARGET)
	gdb ./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove object files"
	@echo "  distclean - Remove all generated files"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  run       - Build and run the program"
	@echo "  debug     - Build and debug with gdb"

# Phony targets (not actual files)
.PHONY: all clean distclean rebuild run debug help