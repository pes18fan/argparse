SOURCE := demo.c argparse.c
TARGET := demo
CFLAGS := -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(SOURCE)
	gcc $(SOURCE) -o $(TARGET) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
