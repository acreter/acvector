CFLAGS := -O3 -Wall

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
