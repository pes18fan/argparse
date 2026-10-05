# Makefile to prepare the demo
SOURCE := demo.c argparse.c
TARGET := demo
CFLAGS := \
	-std=c99 \
	-Wall \
	-Wextra \
	-Wformat=2 \
	-Wimplicit-fallthrough \
	-Wshadow \
	-Wpointer-arith \
	-Wswitch-enum \
	-Wconversion \
	-Wparentheses \
	-Werror

all: $(TARGET)

$(TARGET): $(SOURCE)
	gcc $(SOURCE) -o $(TARGET) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
