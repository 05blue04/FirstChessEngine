# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11 -g

# Raylib and system libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target executable
TARGET = chess

# Source files
SRCS = main.c board.c move.c gui.c test.c
OBJS = $(SRCS:.c=.o)

# Headers
HEADERS = board.h move.h gui.h test.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run