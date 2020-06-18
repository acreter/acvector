CFLAGS := -O2 -Wall -std=c99 -pedantic -Wno-deprecated-declarations -D_POSIX_C_SOURCE=200809L

all: build/libacvector.a example

build/libacvector.a: src/acvector.o
	mkdir -p build/
	$(AR) rcs $@ $<

example: example.o build/libacvector.a
	$(CC) -o $@ $< -Lbuild/ -lacvector

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build/ src/*.o *.o example

.PHONY: all clean
