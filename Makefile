CC = gcc

CFLAGS = -Wall -Wextra -std=c99

TARGET = findLite

SRC = findlite.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)