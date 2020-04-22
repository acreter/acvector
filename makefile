CFLAGS := -O3 -Wall

all: acvector

acvector: src/acvector.o
	mkdir -p build/
	$(AR) rcs build/lib$@.a $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build/
	rm -f $(wildcard src/*.o)

.PHONY: all clean
