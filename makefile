# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = chess

# Source files
SRCS = main.c board.c move.c test.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c board.h move.h test.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean