CFLAGS := -g -O0 -Wall -Wextra -Winline

all: acvector

acvector: src/acvector.o
	mkdir -p build/
	$(AR) rcs build/lib$@.a $^

test: test/test.o acvector
	make -C actest
	$(CC) -o test/test -Lbuild/ -Lactest/build $< -lacvector -lactest
	test/test

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build/
	rm -f $(wildcard src/*.o)
	rm -f $(wildcard test/*.o)

.PHONY: all clean test
