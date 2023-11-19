CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = main.c file_operations.c text_operations.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = goattool

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
