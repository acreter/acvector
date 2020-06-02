CFLAGS := -O3 -Wall

all: build/libacvector.a

build/libacvector.a: src/acvector.o
	mkdir -p build/
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build/
	rm -f src/*.o

.PHONY: all clean
